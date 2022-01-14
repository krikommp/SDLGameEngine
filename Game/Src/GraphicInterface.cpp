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
    Buffer = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WindowInfo.Width, WindowInfo.Height);
    if (Buffer == nullptr) return false;
    return true;
}

bool SoftWareRHI::ClearColor(const FColor &Color) {
    uint32* Dst;
    uint32 Row = 0;
    uint32 Col = 0;
    for (Row = 0; Row < WindowInfo.Height; ++Row) {
        Dst = (uint32*)((uint8 *)Pixels + Row * Pitch);
        for (Col = 0; Col < WindowInfo.Width; ++Col) {
            *Dst++ = ConvertColorToHEX(Color);
        }
    }
    // std::cout << Row << "  " << Col << std::endl;
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

bool SoftWareRHI::BeginRHI() {
    return SDL_LockTexture(Buffer, nullptr, &Pixels, &Pitch) >= 0;
}

void SoftWareRHI::EndRHI() {
    SDL_UnlockTexture(Buffer);
    Pixels = nullptr;
    Pitch = 0;
}
