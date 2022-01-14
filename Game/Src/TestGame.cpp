//
// Created by chenyifei on 2022/1/10.

#include "GraphicInterface.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static bool bExit = false;

int main(int argc, char *argv[]) {
    SWindowInfo Info{.Width = WINDOW_WIDTH, .Height = WINDOW_HEIGHT, .Title = "GameWindow"};
    SoftWareRHI RHI(Info);
    RHI.InitRHI();

    {
        while (!bExit) {
            SDL_Event Event;
            while (SDL_PollEvent(&Event)) {
                switch (Event.type) {
                    case SDL_KEYDOWN:
                        if (Event.key.keysym.sym == SDLK_SPACE) {
                            bExit = true;
                        }
                        break;
                    case SDL_QUIT:
                        bExit = true;
                        break;
                }
            }

            RHI.ClearColor();
            RHI.Render();
        }
    }

    return EXIT_SUCCESS;
}