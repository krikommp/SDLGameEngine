//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"

void MyAppEngine::OnStart() {
    SetWidth(1280);
    SetHeight(720);

    SetClearColor(Color::Sky);

    SetTitle("MyAppEngine");
}

void MyAppEngine::OnUpdate() {
    static float K = float(Height) / float(Width);
    for(uint32 X = 0; X < Width; ++X) {
        SetPixel(X, K * X, Color::Black);
    }
    for(uint32 X = 0; X < Width; ++X) {
        SetPixel(Width - X, K * X, Color::Red);
    }
}

void MyAppEngine::OnExit() {
}


