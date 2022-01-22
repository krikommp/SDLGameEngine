//
// Created by chenyifei on 2022/1/14.
//

#include "GraphicInterface.h"

SoftWareRHI::~SoftWareRHI() {
    delete[] ZBuffer;
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

bool SoftWareRHI::InitRHI(const SWindowInfo &InWindowInfo) {
    WindowInfo = InWindowInfo;
    SDL_Init(SDL_INIT_VIDEO);
    Pixels = nullptr;
    Pitch = 0;

    Window = SDL_CreateWindow(WindowInfo.Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowInfo.Width, WindowInfo.Height, SDL_WINDOW_RESIZABLE);
    if (Window == nullptr) return false;
    Renderer = SDL_CreateRenderer(Window, -1,  SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == nullptr) return false;
    Buffer = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WindowInfo.PixelWidth, WindowInfo.PixelHeight);
    if (Buffer == nullptr) return false;
    ZBuffer = (int*) malloc(WindowInfo.PixelWidth * WindowInfo.PixelHeight * sizeof(int));
    if (ZBuffer == nullptr) return false;
    return true;
}

bool SoftWareRHI::ClearColor(const FColor &Color) {
    uint32* Dst;
    uint32 Row = 0;
    uint32 Col = 0;
    for (Row = 0; Row < WindowInfo.PixelHeight; ++Row) {
        Dst = (uint32*)((uint8 *)Pixels + Row * Pitch);
        for (Col = 0; Col < WindowInfo.PixelWidth; ++Col) {
            *Dst++ = ConvertColorToHEX(Color);
        }
    }
    return true;
}

void SoftWareRHI::SetPixel(uint32 X, uint32 Y, const FColor &Color) {
    if (!CheckPixelInScope(*this, X, Y)) return;
    uint32* Dst = (uint32*)((uint8*)Pixels + (WindowInfo.PixelHeight - Y) * Pitch);
    *(Dst + X) = ConvertColorToHEX(Color);
}

bool SoftWareRHI::Render() {
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, Buffer, nullptr, nullptr);
    SDL_RenderPresent(Renderer);
    return true;
}

void SoftWareRHI::SetTitleText(float FPS) {
    char NewTitle[1024];
    sprintf(NewTitle ,"%s - FPS: %3.2f", WindowInfo.Title, FPS);
    SDL_SetWindowTitle(Window, NewTitle);
}

void DrawLine(SoftWareRHI& RHI, const FVector2i& A, const FVector2i& B, const FColor& Color)
{
    DrawLine(RHI, A[0], A[1], B[0], B[1], Color);
}

void DrawLine(SoftWareRHI& RHI, int AX, int AY, int BX, int BY, const FColor& Color)
{
    int DX = abs(BX - AX), SX = AX < BX ? 1 : -1;
    int DY = -abs(BY - AY), SY = AY < BY ? 1 : -1;
    int Err = DX + DY, E2;  // E = dx + (-dy) = dx - dy 这是初始的 E1
    for(;;)
    {
        if (CheckPixelInScope(RHI, AX, AY)) {
            RHI.SetPixel(AX, AY, Color);
        }
        if (AX == BX && AY == BY) break;
        E2 = 2 * Err;      // Exy + Ex = Exy + Exy + dy = 2Exy - (-dy) > 0     Exy + Ey = 2Exy - dx < 0
        if (E2 >= DY) { Err += DY; AX += SX; }  // 这里因为 dy 是负值 所以写成 2Exy - dy > 0 => 2Exy > dy
        if (E2 <= DX) { Err += DX; AY += SY; }
    }
}

void DrawEllipse(SoftWareRHI& RHI, int MX, int MY, int A, int B, const FColor& Color) {
    long X = -A, Y = 0;
    long E2 = B, DX = (1 + 2 * X) * E2 * E2;
    long DY = X * X, Err = DX + DY;
    do {
        if (CheckPixelInScope(RHI, MX - X, MY + Y)) RHI.SetPixel(MX - X, MY + Y, Color);
        if (CheckPixelInScope(RHI, MX + X, MY + Y)) RHI.SetPixel(MX + X, MY + Y, Color);
        if (CheckPixelInScope(RHI, MX + X, MY - Y)) RHI.SetPixel(MX + X, MY - Y, Color);
        if (CheckPixelInScope(RHI, MX - X, MY - Y)) RHI.SetPixel(MX - X, MY - Y, Color);
        E2 = 2 * Err;
        if (E2 >= DX) {
            X++;
            Err += DX += 2 * (long)B * B;
        }
        if (E2 <= DY) {
            Y++;
            Err += DY += 2 * (long) A * A;
        }
    }while(X <= 0);

    while (Y++ < B) {
        RHI.SetPixel(MX, MY + Y, Color);
        RHI.SetPixel(MX, MY - Y, Color);
    }
}

void DrawTriangleTwo(SoftWareRHI &RHI, FVector2i &T0, FVector2i &T1,  FVector2i &T2, const FColor& Color) {
    // 首先从上到下，从左到右绘制三角形
    // 从上到下依次是： T0 < T1 < T2
    if (T0.Y > T1.Y) Swap(T0, T1);
    if (T0.Y > T2.Y) Swap(T0, T2);
    if (T1.Y > T2.Y) Swap(T1, T2);

    int TotalHeight = T2.Y - T0.Y;
    if (TotalHeight == 0) return;
    for (int Y = T0.Y; Y <= T1.Y; ++Y) {
        int SegmentHeight = T1.Y - T0.Y + 1;
        if (SegmentHeight == 0) break;
        float Alpha = float(Y - T0.Y) / float(TotalHeight);
        float Beta = float(Y - T0.Y) / float(SegmentHeight);
        FVector2i A = T0 + (T2 - T0) * Alpha;
        FVector2i B = T0 + (T1 - T0) * Beta;
        if (A.X > B.X) Swap(A, B);
        for (int J = A.X; J <= B.X; ++J) {
            RHI.SetPixel(J, Y, Color);
        }
    }
    for (int Y = T1.Y; Y <= T2.Y; ++Y) {
        int SegmentHeight = T2.Y - T1.Y + 1;
        if (SegmentHeight == 0) break;
        float Alpha = float(Y - T0.Y) / float(TotalHeight);
        float Beta = float(Y - T1.Y) / float(SegmentHeight);
        FVector2i A = T0 + (T2 - T0) * Alpha;
        FVector2i B = T1 + (T2 - T1) * Beta;
        if (A.X > B.X) Swap(A, B);
        for (int J = A.X; J <= B.X; ++J) {
            RHI.SetPixel(J, Y, Color);
        }
    }
}
FVector3f Barycentric(FVector2i* Pts, FVector2i P) {
    // 下面的 cross 相当于求 [u, v, 1]
    FVector3f u = Cross(FVector3f(Pts[2][0]-Pts[0][0], Pts[1][0]-Pts[0][0], Pts[0][0]-P[0]), FVector3f(Pts[2][1]-Pts[0][1], Pts[1][1]-Pts[0][1], Pts[0][1]-P[1]));
    // 注意最后一个并不是 1，所以要进行齐次操作
    // U.Z 的值需要不为0，因为需要做齐次除法
    // 并且由于这个三角形中每个像素位置都是定点
    // 通过 std::abs() 来判断，所有小于 1 的都是 0
    if (std::abs(u[2])<1) return FVector3f(-1,1,1);
    // [u, v, 1] = [U.X / U.Z, U.Y / U.Z, U.Z / U.Z]
    // P = [(1 - u, v)A + uB + vC]
    return FVector3f(1.f-(u.X+u.Y)/u.Z, u.Y/u.Z, u.X/u.Z);
}

void DrawTriangle(SoftWareRHI &RHI, FVector2i* Pts, const FColor &Color) {
    // 首先计算出这个三角形的 包围盒
    FVector2i AABBmin(RHI.GetPixelWidth() - 1, RHI.GetPixelHeight() - 1);
    FVector2i AABBmax(0, 0);
    FVector2i Clamp(RHI.GetPixelWidth() - 1, RHI.GetPixelHeight() - 1);
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            AABBmin[j] = std::max(0,        std::min(AABBmin[j], Pts[i][j]));
            AABBmax[j] = std::min(Clamp[j], std::max(AABBmax[j], Pts[i][j]));
        }
    }
    // 接着遍历这个包围盒中的所有像素点
    // 通过转换到三角形重心坐标系来判断这个点是否在三角形中
    FVector2i P;
    for (P.X = AABBmin.X; P.X <= AABBmax.X; ++P.X) {
        for (P.Y = AABBmin.Y; P.Y <= AABBmax.Y; ++P.Y) {
            FVector3f ScreenBC = Barycentric(Pts, P);
            // 上面的公式算出来的是点 P 在三角形中的 重心坐标
            if (ScreenBC.X<0 || ScreenBC.Y<0 || ScreenBC.Z<0) continue;
            RHI.SetPixel(P.X, P.Y, Color);
        }
    }
}

bool SoftWareRHI::BeginRHI() {
    return SDL_LockTexture(Buffer, nullptr, &Pixels, &Pitch) >= 0;
}

void SoftWareRHI::EndRHI() {
    SDL_UnlockTexture(Buffer);
    Pixels = nullptr;
    Pitch = 0;
}
