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
        for (int i = 0; i < model.GetFaces(); ++i) {
            std::vector<int> Face = model.GetFace(i);
            FVector2i screen_coords[3];
            for (int j=0; j<3; j++) {
                FVector3f world_coords = model.GetVert(Face[j]);
                screen_coords[j] = FVector2i(int(float(world_coords.X + 1.) * float(GetPixelWidth() / 2.)), int(float(world_coords.Y + 1.) * float(GetPixelHeight() / 2.)));
            }
            DrawTriangle(RHI, screen_coords[0], screen_coords[1], screen_coords[2], FColor(rand() % 255, rand() % 255, rand() % 255, 255));
        }
    }

    void DrawTriangleApp::OnExit() {

    }
}


