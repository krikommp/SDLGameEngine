//
// Created by chenyifei on 2022/1/14.
//

#include "MyAppEngine.h"
#include "Model.h"
#include "ThreadPool.h"

namespace Chapter01 {
	Model model(RootPath + "/Asserts/african_head.obj");
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
	Model model(RootPath + "/Asserts/african_head.obj");
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
                DrawTriangle(RHI, ScreenCoords, uvs[0], uvs[1], uvs[2], Intensity);
            }
        }
    }

    void DrawTriangleApp::OnExit() {

    }
}

namespace Chapter03 {
	Model model(RootPath + "/Asserts/LineCube.obj");
    Model HeadModel(RootPath + "/Asserts/african_head.obj");
    Model CubeModel(RootPath + "/Asserts/Cube.obj");

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

    Matrix Lookup(const FVector3f&  Eye, const FVector3f& Center, const FVector3f& Up) {
        FVector3f Z = (Eye - Center).Normalize();
        FVector3f X = Cross(Up, Z).Normalize();
        FVector3f Y = Cross(Z, X).Normalize();
        Matrix Res = Matrix::Identity(4);
        for (int i = 0; i < 3; ++i) {
            Res[0][i] = X[i];
            Res[1][i] = Y[i];
            Res[2][i] = Z[i];
            Res[i][3] = -Center[i];
        }
        return Res;
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

        for (int i = 0; i < model.GetFaces(); ++i) {
            std::vector<int> face = model.GetFace(i);
            for (int j = 0; j < (int)face.size(); ++j) {
                FVector3f wp0 = model.GetVert(face[j]);
                FVector3f wp1 = model.GetVert(face[(j + 1) % face.size()]);
                {
                    FVector3f sp0 = m2v(VP*v2m(wp0));
                    FVector3f sp1 = m2v(VP*v2m(wp1));

                    DrawLine(RHI, sp0.X, sp0.Y, sp1.X, sp1.Y, Color::White);
                }
                {
                    Matrix T = Matrix::Identity(4);
                    T[3][0] = - (1.f / 5.f);
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
#define THREAD_NUM 16
    FVector3f Camera(0, 0, 3);
    FVector3f LightDir(0, 0, -1);
    FVector3f EyeDir(1, 0, 3);
    FVector3f CenterDir(0, 0, 0);

    ThreadPool Pool(THREAD_NUM);
    void PerspectiveModelApp::OnStart() {
        SetWidthAndHeight(FVector2i(gWidth, gHeight));
        SetPixelSize(1);
        SetClearColor(Color::Sky);
        SetTitle("Chapter03");
        RHI.SetModel(CubeModel);
    }


    float t = 0.0f;
    Matrix ModelView = Lookup(EyeDir, CenterDir, FVector3f(0, 1, 0));
    Matrix Projection = Matrix::Identity(4);
    Matrix Viewport = viewport(gWidth / 8, gHeight / 8, gWidth * 3 / 4, gHeight * 3 / 4);
    void PerspectiveModelApp::OnUpdate() {
        Matrix T = translation(FVector3f (0, 0, 0))*rotation_y(cos(t * 10.*M_PI/180.), sin(t * 10.*M_PI/180.));
        Projection[3][2] = -1.f / Camera.Z;
        auto F = [=](int Start, int End) {
            for (int i = Start; i < End; ++i) {
                std::vector<int> Faces = CubeModel.GetFace(i);
                FVector3i ScreenCoords[3];
                FVector3f WorldCoords[3];
                for (int j = 0; j < 3; ++j) {
                    FVector3f Vert = CubeModel.GetVert(Faces[j]);
                    ScreenCoords[j] = VectorCast<3, int>(
                            m2v(Viewport * Projection * ModelView * T * v2m(Vert)));
                    WorldCoords[j] = Vert;
                }
                FVector3f Normal = VectorCast(
                        (ScreenCoords[2] - ScreenCoords[0]) ^ (ScreenCoords[1] - ScreenCoords[0]));
                Normal.Normalize();
                float Intensity = Normal * LightDir;
                if (Intensity > 0) {
                    FVector2i uvs[3];
                    for (int k = 0; k < 3; ++k) {
                        uvs[k] = CubeModel.GetUV(i, k);
                    }
                    // DrawTriangle(RHI, ScreenCoords, uvs[0], uvs[1], uvs[2], Intensity);
                    DrawTriangle(this->RHI, ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], uvs[0], uvs[1], uvs[2],
                                 Intensity);
                }
            }
            return 0;
        };
        
        int TotalFace = CubeModel.GetFaces();
        int Count = TotalFace / THREAD_NUM;
        int Leave = TotalFace % THREAD_NUM;
        int Start = 0;
        std::vector<std::future<int>> Threads;
        for (int Group = 0; Group < THREAD_NUM; ++Group) {
            int End = Start + Count;
            Threads.push_back(Pool.enqueue(F, Start, End));
            Start = End;
        }
        if (Leave > 0) {
            Threads.push_back(Pool.enqueue(F, Start, Start + Leave));
        }
        for (auto& iter : Threads) {
            iter.get();
        }
        t += Timer.fElapsedTime;
    }

    void PerspectiveModelApp::OnExit() {
    }
}


