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
    for (uint32 i = 0; i < WindowInfo.PixelHeight * WindowInfo.PixelWidth; ++i) ZBuffer[i] = - std::numeric_limits<int>::max();
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
            *Dst++ = Color.DWColor();
        }
    }
    for (uint32 i = 0; i < WindowInfo.PixelHeight * WindowInfo.PixelWidth; ++i) ZBuffer[i] = - std::numeric_limits<int>::max();
    return true;
}

void SoftWareRHI::SetPixel(uint32 X, uint32 Y, const FColor &Color) {
    if (!CheckPixelInScope(*this, X, Y)) return;
    uint32* Dst = (uint32*)((uint8*)Pixels + (WindowInfo.PixelHeight - Y) * Pitch);
    *(Dst + X) = Color.DWColor();
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
    int Err = DX + DY, E2;  // E = dx + (-dy) = dx - dy ??????????????? E1
    for(;;)
    {
        if (CheckPixelInScope(RHI, AX, AY)) {
            RHI.SetPixel(AX, AY, Color);
        }
        if (AX == BX && AY == BY) break;
        E2 = 2 * Err;      // Exy + Ex = Exy + Exy + dy = 2Exy - (-dy) > 0     Exy + Ey = 2Exy - dx < 0
        if (E2 >= DY) { Err += DY; AX += SX; }  // ???????????? dy ????????? ???????????? 2Exy - dy > 0 => 2Exy > dy
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
    // ????????????????????????????????????????????????
    // ???????????????????????? T0 < T1 < T2
    if (T0.Y > T1.Y) std::swap(T0, T1);
    if (T0.Y > T2.Y) std::swap(T0, T2);
    if (T1.Y > T2.Y) std::swap(T1, T2);

    int TotalHeight = T2.Y - T0.Y;
    if (TotalHeight == 0) return;
    for (int Y = T0.Y; Y <= T1.Y; ++Y) {
        int SegmentHeight = T1.Y - T0.Y + 1;
        if (SegmentHeight == 0) break;
        float Alpha = float(Y - T0.Y) / float(TotalHeight);
        float Beta = float(Y - T0.Y) / float(SegmentHeight);
        FVector2i A = T0 + (T2 - T0) * Alpha;
        FVector2i B = T0 + (T1 - T0) * Beta;
        if (A.X > B.X) std::swap(A, B);
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
        if (A.X > B.X) std::swap(A, B);
        for (int J = A.X; J <= B.X; ++J) {
            RHI.SetPixel(J, Y, Color);
        }
    }
}
FVector3f Barycentric(FVector3i* Pts, FVector3i P) {
    FVector3f u = FVector3f(float(Pts[2][0])-float(Pts[0][0]), float(Pts[1][0])-float(Pts[0][0]), float(Pts[0][0])-float(P[0])) ^ FVector3f(float(Pts[2][1])-float(Pts[0][1]), float(Pts[1][1])-float(Pts[0][1]), float(Pts[0][1])-float(P[1]));
    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u[2])<1) return FVector3f(-1,1,1);
    return FVector3f(1.f-(u.X+u.Y)/u.Z, u.Y/u.Z, u.X/u.Z);
}

void DrawTriangle(SoftWareRHI& RHI, FVector3i* Pts, const FVector2i& uv0, const FVector2i& uv1, const FVector2i& uv2, float Intensity) {
    FVector2i AABBmin(RHI.GetPixelWidth() - 1, RHI.GetPixelHeight() - 1);
    FVector2i AABBmax(0, 0);
    FVector2i Clamp(RHI.GetPixelWidth() - 1, RHI.GetPixelHeight() - 1);
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            AABBmin[j] = std::max(0,        std::min(AABBmin[j], Pts[i][j]));
            AABBmax[j] = std::min(Clamp[j], std::max(AABBmax[j], Pts[i][j]));
        }
    }
    FVector3i P;
    FVector2i uv;
    for (P.X = AABBmin.X; P.X <= AABBmax.X; ++P.X) {
        for (P.Y = AABBmin.Y; P.Y <= AABBmax.Y; ++P.Y) {
            FVector3f ScreenBC = Barycentric(Pts, P);
            if (ScreenBC.X<0 || ScreenBC.Y<0 || ScreenBC.Z<0) continue;
            uv = uv0 * ScreenBC.X + uv1 * ScreenBC.Y + uv2 * ScreenBC.Z;
            P.Z = 0;
            for (int i = 0; i < 3; ++i) P.Z += Pts[i][2] * int(ScreenBC[i]);
            if (RHI.ZBuffer[int(P.X + P.Y * RHI.GetPixelWidth())] < P.Z) {
                RHI.ZBuffer[int(P.X + P.Y * RHI.GetPixelWidth())] = P.Z;
                FColor Color = RHI.RenderModel.Diffuse(uv);
                RHI.SetPixel(P.X, P.Y, Color * Intensity);
            }
        }
    }
}

void
DrawTriangle(SoftWareRHI &RHI, FVector3i t0, FVector3i t1, FVector3i t2, FVector2i uv0, FVector2i uv1, FVector2i uv2,
             float Intensity) {
    if (t0.Y==t1.Y && t0.Y==t2.Y) return;
    if (t0.Y>t1.Y) { std::swap(t0, t1); std::swap(uv0, uv1); }
    if (t0.Y>t2.Y) { std::swap(t0, t2); std::swap(uv0, uv2); }
    if (t1.Y>t2.Y) { std::swap(t1, t2); std::swap(uv1, uv2); }

    int TotalHeight = t2.Y - t0.Y;
    for (int i = 0; i < TotalHeight; ++i) {
        bool SecondHalf = i > t1.Y - t0.Y || t1.Y == t0.Y;
        int SegmentHeight = SecondHalf ? t2.Y - t1.Y : t1.Y - t0.Y;
        float alpha = (float)i / TotalHeight;
        float beta = (float)(i - (SecondHalf ? t1.Y - t0.Y : 0)) / SegmentHeight;
        FVector3i A = t0 + VectorCast(VectorCast(t2 - t0) * alpha);
        FVector3i B = SecondHalf ? t1 + VectorCast(VectorCast(t2 - t1) * beta) : t0 + VectorCast(VectorCast(t1 - t0) * beta);
        FVector2i uvA = uv0 + (uv2 - uv0) * alpha;
        FVector2i uvB = SecondHalf ? uv1 + (uv2 - uv1) * beta : uv0 + (uv1 - uv0) * beta;
        if (A.X > B.X) { std::swap(A, B); std::swap(uvA, uvB);  }
        for (int j = A.X; j <= B.X; ++j) {
            float phi = B.X == A.X ? 1. : float(j - A.X) / (float)(B.X - A.X);
            FVector3i P = VectorCast(VectorCast(A) + VectorCast(B - A) * phi);
            FVector2i uvP = uvA + (uvB - uvA) * phi;
            int idx = P.X + P.Y * RHI.GetPixelWidth();
            if (RHI.ZBuffer[idx] < P.Z) {
                RHI.ZBuffer[idx] = P.Z;
                FColor Color = RHI.RenderModel.Diffuse(uvP);
                RHI.SetPixel(P.X, P.Y,  Color * Intensity);
            }
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

bool SoftWareRHI::SetModel(const Model& InModel) {
    RenderModel = InModel;
    return true;
}
