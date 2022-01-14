//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"

void MyAppEngine::OnStart() {
    SetWidth(600);
    SetHeight(600);

    SetClearColor(FColor(173, 246, 230, 255));

    SetTitle("MyAppEngine");
}

void MyAppEngine::OnUpdate() {
    for(uint32 X = 0; X < Width; ++X) {
        for (uint32 Y = 0; Y < Height; ++Y) {
            SetPixel(X, X, Color::Red);
        }
    }
    for(uint32 X = 0; X < Width; ++X) {
        for (uint32 Y = 0; Y < Height; ++Y) {
            SetPixel(Width - X, X, Color::Green);
        }
    }
}

void MyAppEngine::OnExit() {
}


