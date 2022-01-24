//
// Created by chenyifei on 2022/1/19.
//

#ifndef SDLGAMEENGINE_MODEL_H
#define SDLGAMEENGINE_MODEL_H

#include <GraphicMath.h>
#include "tgaimage.h"

#include <vector>

class Model {
public:
    Model(const char* FileName);
    ~Model();

public:
    int GetVerts();

    int GetFaces();

    FVector3f GetVert(int Index);

    std::vector<int> GetFace(int Index);

    FVector2i GetUV(int InFace, int  InVert);

private:
    void LoadTexture(const char* FileName, const char* Suffix, TGAImage& Img);

private:
    std::vector<FVector3f> Verts;
    std::vector<std::vector<FVector3i>> Faces;
    std::vector<FVector2f> Uvs;
    std::vector<FVector3f> Normals;

    TGAImage DiffuseMap;
};
#endif //SDLGAMEENGINE_MODEL_H
