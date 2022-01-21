//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
#include "Model.h"

static Model model("./Asserts/Lowpoly_tree_sample.obj");
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
            FVector2i  ScreenCoords[3];
            FVector3f WorldCoords[3];
            for (int j=0; j<3; j++) {
                // FVector3f world_coords = model.GetVert(Face[j]);
                // screen_coords[j] = FVector2i(int(float(world_coords.X + 1.) * float(GetPixelWidth() / 2.) * 0.05) + 200, int(float(world_coords.Y + 1.) * float(GetPixelHeight() / 2.) * 0.05) + 50);
                FVector3f V = model.GetVert(Face[j]);
                ScreenCoords[j] = FVector2i(int(float(V.X + 1.) * float(GetPixelWidth() / 2.) * 0.05) + 200, int(float(V.Y + 1.) * float(GetPixelHeight() / 2.) * 0.05) + 50);
                WorldCoords[j] = V;
            }
            FVector3f N = (WorldCoords[2] - WorldCoords[0]) ^ (WorldCoords[1] - WorldCoords[0]);
            N.Normalize();
            float Intensity = N * FVector3f(0, 0, -1);
            if (Intensity > 0) {
                // DrawTriangleTwo(RHI, ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], FColor(Intensity * 255, Intensity * 255, Intensity * 255, 255));
                DrawTriangle(RHI, ScreenCoords, FColor(uint8(Intensity * 255), uint8(Intensity * 255), uint8(Intensity * 255), 255));
            }
        }
    }

    void DrawTriangleApp::OnExit() {

    }
}


