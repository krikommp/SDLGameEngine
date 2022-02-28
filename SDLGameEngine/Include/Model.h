//
// Created by chenyifei on 2022/1/19.
//

#ifndef SDLGAMEENGINE_MODEL_H
#define SDLGAMEENGINE_MODEL_H

#include <GraphicMath.h>
#include <Texture.h>

#include <vector>
#include <string>

class Model {
public:
    Model();
    Model(const char* FileName);
    Model(const std::string_view& FileName);
    ~Model();
public:

    int GetVerts();

    int GetFaces();

    FVector3f GetVert(int Index);

    std::vector<int> GetFace(int Index);

    FVector2i GetUV(int InFace, int  InVert);

    FColor Diffuse(const FVector2i& InUV);
private:
    void LoadTexture(const char* FileName, const char* Suffix);

private:
    void Init(std::ifstream& In);

private:
    std::vector<FVector3f> Verts;
    std::vector<std::vector<FVector3i>> Faces;
    std::vector<FVector2f> Uvs;
    std::vector<FVector3f> Normals;

    IRenderTexture* MainTex;
};
#endif //SDLGAMEENGINE_MODEL_H
