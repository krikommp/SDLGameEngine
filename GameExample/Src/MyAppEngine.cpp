//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
#include "Model.h"

static Model model(RootPath + "/Asserts/african_head.obj");
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
        SetWidthAndHeight(FVector2i(400, 400));
        SetPixelSize(1);
        SetClearColor(Color::Sky);
        SetTitle("Chapter02 - DrawTriangle");
        RHI.SetModel(model);
    }

    void DrawTriangleApp::OnUpdate() {
        for (int i = 0; i < model.GetFaces(); ++i) {
            std::vector<int> Face = model.GetFace(i);
            FVector3i ScreenCoords[3];
            FVector3f WorldCoords[3];
            for (int j=0; j<3; j++) {
                // FVector3f world_coords = model.GetVert(Face[j]);
                // screen_coords[j] = FVector2i(int(float(world_coords.X + 1.) * float(GetPixelWidth() / 2.) * 0.05) + 200, int(float(world_coords.Y + 1.) * float(GetPixelHeight() / 2.) * 0.05) + 50);
                FVector3f V = model.GetVert(Face[j]);
                ScreenCoords[j] = FVector3i(int(float(V.X + 1.) * float(GetPixelWidth() / 2.)), int(float(V.Y + 1.) * float(GetPixelHeight() / 2.)), int(float(V.Z + 1.0f) * float(200 / 2.f)));
                WorldCoords[j] = V;
            }
            FVector3f N = (WorldCoords[2] - WorldCoords[0]) ^ (WorldCoords[1] - WorldCoords[0]);
            N.Normalize();
            float Intensity = N * FVector3f(0, 0, -1);
            if (Intensity > 0) {
                FVector2i uvs[3];
                for (int k = 0; k < 3; ++k) {
                    uvs[k] = model.GetUV(i, k);
                }
                // DrawTriangleTwo(RHI, ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], FColor(Intensity * 255, Intensity * 255, Intensity * 255, 255));
                DrawTriangle(RHI, ScreenCoords, uvs[0], uvs[1], uvs[2], FColor(uint8(Intensity * 255), uint8(Intensity * 255), uint8(Intensity * 255), 255));
            }
        }
    }

    void DrawTriangleApp::OnExit() {

    }
}

namespace Chapter03 {
    Model CubeModel(RootPath + "/Asserts/cube.obj");

    constexpr int gWidth = 400;
    constexpr int gHeight = 400;
    constexpr int gDepth = 255;

    FVector3f m2v(Matrix m) {
        return FVector3f(m[0][0]/m[3][0], m[1][0]/m[3][0], m[2][0]/m[3][0]);
    }

    Matrix v2m(FVector3f v) {
        Matrix m(4, 1);
        m[0][0] = v.X;
        m[1][0] = v.Y;
        m[2][0] = v.Z;
        m[3][0] = 1.f;
        return m;
    }

    Matrix viewport(int x, int y, int w, int h) {
        Matrix m = Matrix::Identity(4);
        m[0][3] = x+w/2.f;
        m[1][3] = y+h/2.f;
        m[2][3] = gDepth/2.f;

        m[0][0] = w/2.f;
        m[1][1] = h/2.f;
        m[2][2] = gDepth/2.f;
        return m;
    }

    Matrix translation(FVector3f v) {
        Matrix Tr = Matrix::Identity(4);
        Tr[0][3] = v.X;
        Tr[1][3] = v.Y;
        Tr[2][3] = v.Z;
        return Tr;
    }

    Matrix zoom(float factor) {
        Matrix Z = Matrix::Identity(4);
        Z[0][0] = Z[1][1] = Z[2][2] = factor;
        return Z;
    }

    Matrix rotation_x(float cosangle, float sinangle) {
        Matrix R = Matrix::Identity(4);
        R[1][1] = R[2][2] = cosangle;
        R[1][2] = -sinangle;
        R[2][1] =  sinangle;
        return R;
    }

    Matrix rotation_y(float cosangle, float sinangle) {
        Matrix R = Matrix::Identity(4);
        R[0][0] = R[2][2] = cosangle;
        R[0][2] =  sinangle;
        R[2][0] = -sinangle;
        return R;
    }

    Matrix rotation_z(float cosangle, float sinangle) {
        Matrix R = Matrix::Identity(4);
        R[0][0] = R[1][1] = cosangle;
        R[0][1] = -sinangle;
        R[1][0] =  sinangle;
        return R;
    }

    void PerspectiveProjectionApp::OnStart() {
        SetWidthAndHeight(FVector2i(gWidth, gHeight));
        SetPixelSize(1);
        SetClearColor(Color::Sky);
        SetTitle("Chapter03 - Perspective_Projection");
    }

    void PerspectiveProjectionApp::OnUpdate() {
        Matrix VP = viewport(gWidth/4, gWidth/4, gWidth/2, gHeight/2);

        { // draw the axes
            FVector3f x(1.f, 0.f, 0.f), y(0.f, 1.f, 0.f), o(0.f, 0.f, 0.f);
            o = m2v(VP*v2m(o));
            x = m2v(VP*v2m(x));
            y = m2v(VP*v2m(y));
            DrawLine(RHI, o.X, o.Y, x.X, x.Y, Color::Red);
            DrawLine(RHI, o.X, o.Y, y.X, y.Y, Color::Green);
        }

        for (int i = 0; i < CubeModel.GetFaces(); ++i) {
            std::vector<int> face = CubeModel.GetFace(i);
            for (int j = 0; j < (int)face.size(); ++j) {
                FVector3f wp0 = model.GetVert(face[j]);
                FVector3f wp1 = model.GetVert(face[(j + 1) % face.size()]);
                {
                    FVector3f sp0 = m2v(VP*v2m(wp0));
                    FVector3f sp1 = m2v(VP*v2m(wp1));

                    DrawLine(RHI, sp0.X, sp0.Y, sp1.X, sp1.Y, Color::White);
                }
                {
                    Matrix T = zoom(1.5);
//                  Matrix T = Matrix::identity(4);
//                  T[0][1] = 0.333;
//                Matrix T = translation(Vec3f(.33, .5, 0))*rotation_z(cos(10.*M_PI/180.), sin(10.*M_PI/180.));
                    FVector3f sp0 = m2v(VP*T*v2m(wp0));
                    FVector3f sp1 = m2v(VP*T*v2m(wp1));

                    DrawLine(RHI, sp0.X, sp0.Y, sp1.X, sp1.Y, Color::Black);
                }
            }
            break;
        }
    }

    void PerspectiveProjectionApp::OnExit() {

    }
}


