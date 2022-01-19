//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"

#include "Model.h"

std::vector<FVector2i> Points;

static Model model("./Asserts/Face.obj");

void MyAppEngine::OnStart() {
    SetWidthAndHeight(FVector2i(480, 240));
    SetPixelSize(1);
    SetClearColor(Color::Sky);
    SetTitle("MyAppEngine");
}

float t = 0.0f;
void MyAppEngine::OnUpdate() {
    t += Timer.fElapsedTime;
//    if (Controller.GetMouse(MouseType::MOUSE_LEFT).bPressed) {
//        Points.push_back(Controller.GetMousePosition());
//    }
//    if (Controller.GetMouse(MouseType::MOUSE_RIGHT).bPressed) {
//        Points.clear();
//    }
//    uint32 Index = 0;
//    while ((Index + 1) < Points.size()) {
//        DrawLine(RHI, Points[Index] / int(GetPixelSize()), Points[Index + 1] / int(GetPixelSize()), Color::Red);
//        Index++;
//    }
//    if (!Points.empty()) {
//        DrawLine(RHI, Points[Index] / int(GetPixelSize()), Controller.GetMousePosition() / int(GetPixelSize()), Color::Red);
//    }
//
//    DrawEllipse(RHI, int(GetPixelWidth()) / 2, int(GetPixelHeight()) / 2, int(50 * abs(cos(t) + 2)), int(50 * abs(cos(t) + 2)), Color::Red);

    for (int i = 0; i < model.GetFaces(); ++i) {
        std::vector<int> Face = model.GetFace(i);
        for (int j = 0; j < 3; ++j) {
            FVector3f V0 = model.GetVert(Face[j]);
            FVector3f V1 = model.GetVert(Face[(j + 1) % 3]);
            int X0 = int(float(V0.X + 1) * float(GetPixelWidth()) / 2);
            int Y0 = int(float(V0.Y + 1) * float(GetPixelHeight()) / 2);
            int X1 = int(float(V1.X + 1) * float(GetPixelWidth()) / 2);
            int Y1 = int(float(V1.Y + 1) * float(GetPixelHeight()) / 2);
            DrawLine(RHI, X0, Y0, X1, Y1, Color::White);
        }
    }
}

void MyAppEngine::OnExit() {
}


