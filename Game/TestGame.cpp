//
// Created by chenyifei on 2022/1/10.

#include "TestGame.h"

constexpr int Width = 200;
constexpr int Height = 100;

using namespace std;
int main(int argc, char** args) {
    PPMObject PPM("Image.ppm", Width, Height);

    for (int j = Height-1; j >= 0; --j) {
        for (int i = 0; i < Width; ++i) {
            auto r = double(i) / Width;
            auto g = double(j) / Height;
            auto b = 0.2;
            PPM.SetPixel(i, j, FColor(r, g, b));
        }
    }

    PPM.Render();
    return 0;
}