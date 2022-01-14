//
// Created by chenyifei on 2022/1/10.

#include "GraphicInterface.h"

#define WINDOW_WIDTH 600 / 4
#define WINDOW_HEIGHT 600 / 4

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

            {
                RHIRendererRALL RHIScope(&RHI);
                RHI.ClearColor(FColor(173, 216, 230, 255));

                for (uint32 X = 0; X < WINDOW_WIDTH; ++X) {
                    RHI.SetPixel(X, X, FColor(255, 0, 0, 255));
                }
                for (uint32 X = 0; X < WINDOW_WIDTH; ++X) {
                    RHI.SetPixel(WINDOW_WIDTH - X, X, FColor(255, 0, 0, 255));
                }

                RHI.Render();
            }
        }
    }

    return EXIT_SUCCESS;
}