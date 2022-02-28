//
// Created by chenyifei on 2022/1/19.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Model.h"

Model::Model() {
    MainTex = nullptr;
}

Model::Model(const char *FileName) {
    MainTex = nullptr;
    std::ifstream In;
    In.open(FileName, std::ifstream::in);
    if (In.fail()) return;
    Init(In);
    LoadTexture(FileName, "_diffuse.tga");
}

Model::Model(const std::string_view& FileName)
{
    MainTex = nullptr;
    std::ifstream In;
    In.open(FileName.data(), std::ifstream::in);
    if (In.fail()) return;
    Init(In);
    LoadTexture(FileName.data(), "_diffuse.tga");
}

Model::~Model() {
    if (MainTex == nullptr) {
        std::cerr << "null texture, skip" << std::endl;
    }else if (MainTex->GetHeight() < 0 || MainTex->GetHeight() < 0) {
        std::cerr << "error texture" << std::endl;
    }else if (MainTex != nullptr) {
        std::cerr << "delete not null texture" << std::endl;
        delete MainTex;
        MainTex = nullptr;
    }
}

int Model::GetVerts() {
    return (int)Verts.size();
}

int Model::GetFaces() {
    return (int)Faces.size();
}

FVector3f Model::GetVert(int Index) {
    return Verts[Index];
}

std::vector<int> Model::GetFace(int Index) {
    std::vector<int> Face;
    for (int i = 0; i < (int)Faces[Index].size(); ++i) {
        Face.push_back(Faces[Index][i][0]);
    }
    return Face;
}

FVector2i Model::GetUV(int InFace, int  InVert) {
    int idx = Faces[InFace][InVert][1];
    return FVector2i(int(Uvs[idx].X * int(MainTex->GetWidth())), int(Uvs[idx].Y * int(MainTex->GetHeight())));
}

void Model::LoadTexture(const char *FileName, const char *Suffix) {
    std::string TexFile(FileName);
    size_t Dot = TexFile.find_last_of(".");
    if (Dot != std::string::npos) {
        TexFile = TexFile.substr(0, Dot) + std::string(Suffix);
        MainTex = FTextureFactory::LoadTexture(TexFile.c_str(), ETextureResourceType::TGA);
        if (MainTex == nullptr) {
            std::cerr << "Load Texture Failed" << std::endl;
        }
    }
}

void Model::Init(std::ifstream& In)
{
    std::string Line;
    while (!In.eof()) {
        std::getline(In, Line);
        std::istringstream  Iss(Line.c_str());
        char Trash;
        if (!Line.compare(0, 2, "v ")) {
            Iss >> Trash;
            FVector3f V;
            for (int i = 0; i < 3; ++i) Iss >> V.Coords[i];
            Verts.push_back(V);
        }
        else if (!Line.compare(0, 3, "vn ")) {
            Iss >> Trash >> Trash;
            FVector3f n;
            for (int i = 0; i < 3; ++i) Iss >> n[i];
            Normals.push_back(n);
        }
        else if (!Line.compare(0, 3, "vt ")) {
            Iss >> Trash >> Trash;
            FVector2f uv;
            for (int i = 0; i < 2; ++i) Iss >> uv.Coords[i];
            Uvs.push_back({ uv.X, 1 - uv.Y });
        }
        else if (!Line.compare(0, 2, "f ")) {
            std::vector<FVector3i> f;
            FVector3i Tmp;
            Iss >> Trash;
            while (Iss >> Tmp[0] >> Trash >> Tmp[1] >> Trash >> Tmp[2]) {
                for (int i = 0; i < 3; ++i) Tmp[i]--;
                f.push_back(Tmp);
            }
            Faces.push_back(f);
        }
    }
    std::cerr << "# v# " << Verts.size() << " f# " << Faces.size() << " vt# " << Uvs.size() << " vn# " << Normals.size() << std::endl;
}

FColor Model::Diffuse(const FVector2i &InUV) {
    return MainTex->Sampler(InUV.U, InUV.V);
}
