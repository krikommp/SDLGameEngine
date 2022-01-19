//
// Created by chenyifei on 2022/1/14.
//

#include "GraphicInterface.h"

SoftWareRHI::~SoftWareRHI() {
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
    uint32* Dst = (uint32*)((uint8*)Pixels + Y * Pitch);
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

void DrawTriangle(SoftWareRHI &RHI, const FVector2i &A, const FVector2i &B, const FVector2i &C, const FColor& Color) {
    DrawLine(RHI, A, B, Color);
    DrawLine(RHI, A, C, Color);
    DrawLine(RHI, B, C, Color);
}

bool SoftWareRHI::BeginRHI() {
    return SDL_LockTexture(Buffer, nullptr, &Pixels, &Pitch) >= 0;
}

void SoftWareRHI::EndRHI() {
    SDL_UnlockTexture(Buffer);
    Pixels = nullptr;
    Pitch = 0;
}
