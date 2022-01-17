//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
std::vector<FVector2i> Points;

void MyAppEngine::OnStart() {
    SetWidthAndHeight(FVector2i(480, 240));
    SetPixelSize(4);
    SetClearColor(Color::Sky);
    SetTitle("MyAppEngine");
}
constexpr int Num = 1000;
void MyAppEngine::OnUpdate() {
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
    DrawLine(RHI, FVector2i(GetPixelWidth() / 2, GetPixelHeight() / 2), Controller.GetMousePosition() / int(GetPixelSize()), Color::Red);
}

void MyAppEngine::OnExit() {
}


