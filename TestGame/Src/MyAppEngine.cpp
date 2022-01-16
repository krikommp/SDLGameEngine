//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"

#include <random>

void MyAppEngine::OnStart() {
    SetWidth(1280);
    SetHeight(720);

    SetClearColor(Color::Sky);

    SetTitle("MyAppEngine");

    srand(0);
}
constexpr int Num = 1000;
void MyAppEngine::OnUpdate() {
    std::vector<FVector2i> Points;
	for (int i = 0; i < Num; i++)
    {
        FVector2i P(rand() % 1280, rand() % 720);
        Points.push_back(P);
    }
    int i = 0;
    while (i < Num)
    {
        DrawLine(RHI, Points[i], Points[i + 1], FColor(rand() % 255, rand() % 255, rand() % 255, 255));
        i += 2;
    }
}

void MyAppEngine::OnExit() {
}


