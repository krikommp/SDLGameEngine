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

    FVector2i I(12, 13);
    std::cout << I << std::endl;

    srand(0);
}

void MyAppEngine::OnUpdate() {
    std::vector<FVector2i> Points;
	for (int i = 0; i < 100; i++)
    {
        FVector2i P(rand() % 1280, rand() % 720);
        Points.push_back(P);
    }
    int i = 0;
    while (i < 100)
    {
        DrawLine(RHI, Points[i], Points[i + 1], FColor(rand() % 255, rand() % 255, rand() % 255, 255));
        i += 2;
    }
}

void MyAppEngine::OnExit() {
}


