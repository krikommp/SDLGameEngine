//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
#include "Model.h"

static Model model("./Asserts/Face.obj");
namespace Chapter01 {
    void WireframeApp::OnStart() {
        SetWidthAndHeight(FVector2i(480, 240));
        SetPixelSize(1);
        SetClearColor(Color::Sky);
        SetTitle("MyAppEngine");
    }

    void WireframeApp::OnUpdate() {
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

    void WireframeApp::OnExit() {
    }
}

namespace Chapter02 {
    void DrawTriangleApp::OnStart() {
        SetWidthAndHeight(FVector2i(480, 240));
        SetPixelSize(1);
        SetClearColor(Color::Sky);
        SetTitle("Chapter02 - DrawTriangle");
    }

    void DrawTriangleApp::OnUpdate() {
        FVector2i t0[3] = {FVector2i(10, 70), FVector2i(50, 160), FVector2i(70, 80) };
        FVector2i t1[3] = {FVector2i(180, 50),  FVector2i(150, 1),   FVector2i(70, 180)};
        FVector2i t2[3] = {FVector2i(180, 150), FVector2i(120, 160), FVector2i(130, 180)};

        DrawTriangle(RHI, t0[0], t0[1], t0[2], Color::Red);
        DrawTriangle(RHI, t1[0], t1[1], t1[2], Color::White);
        DrawTriangle(RHI, t2[0], t2[1], t2[2], Color::Green);
    }

    void DrawTriangleApp::OnExit() {

    }
}


