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
//    std::vector<FVector2i> Points;
//	for (int i = 0; i < Num; i++)
//    {
//        FVector2i P(rand() % Width, rand() % Height);
//        Points.push_back(P);
//    }
//    int i = 0;
//    while (i < Num)
//    {
//        DrawLine(RHI, Points[i], Points[i + 1], FColor(rand() % 255, rand() % 255, rand() % 255, 255));
//        i += 2;
//    }
    // DrawLine(RHI, FVector2i(GetPixelWidth() / 2, GetPixelHeight() / 2), Controller.GetMousePosition() / int(GetPixelSize()), Color::Red);
}

void MyAppEngine::OnExit() {
}


