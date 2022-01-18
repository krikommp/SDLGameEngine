//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
std::vector<FVector2i> Points;

void MyAppEngine::OnStart() {
    SetWidthAndHeight(FVector2i(480, 240));
    SetPixelSize(1);
    SetClearColor(Color::Sky);
    SetTitle("MyAppEngine");
}

void MyAppEngine::OnUpdate() {
    if (Controller.GetMouse(MouseType::MOUSE_LEFT).bPressed) {
        Points.push_back(Controller.GetMousePosition());
    }
    if (Controller.GetMouse(MouseType::MOUSE_RIGHT).bPressed) {
        Points.clear();
    }
    uint32 Index = 0;
    while ((Index + 1) < Points.size()) {
        DrawLine(RHI, Points[Index] / int(GetPixelSize()), Points[Index + 1] / int(GetPixelSize()), Color::Red);
        Index++;
    }
    if (Points.size() > 0) {
        DrawLine(RHI, Points[Index] / int(GetPixelSize()), Controller.GetMousePosition() / int(GetPixelSize()), Color::Red);
    }

    DrawEllipse(RHI, 100, 100, 50, 50, Color::Red);
}

void MyAppEngine::OnExit() {
}


