//
// Created by chenyifei on 2022/1/19.
//

#ifndef SDLGAMEENGINE_MODEL_H
#define SDLGAMEENGINE_MODEL_H

#include <GraphicMath.h>

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
private:
    std::vector<FVector3f> Verts;
    std::vector<std::vector<int>> Faces;
};

#endif //SDLGAMEENGINE_MODEL_H
