//
// Created by chenyifei on 2022/1/19.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Model.h"


Model::Model(const char *FileName) {
    std::ifstream In;
    In.open(FileName, std::ifstream::in);
    if (In.fail()) return;
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
        }else if (!Line.compare(0, 2, "f ")) {
            std::vector<int> F;
            int iTrash, Idx;
            Iss >> Trash;
            while (Iss >> Idx >> Trash >> iTrash >> Trash >> iTrash) {
                Idx--;
                F.push_back(Idx);
            }
            Faces.push_back(F);
        }
    }
    std::cerr << "# v# " << Verts.size() << " f# "  << Faces.size() << std::endl;
}

Model::~Model() {

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
    return Faces[Index];
}
