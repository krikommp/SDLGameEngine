//
// Created by chenyifei on 2022/1/10.
//

#ifndef SDLGAMEENGINE_TESTGAME_H
#define SDLGAMEENGINE_TESTGAME_H

#include "SortWarePCH.h"

class PPMObject{
public:
    explicit PPMObject(const char* FileName, uint32 InWidth, uint32 InHeight) : Width(InWidth), Height(InHeight) {
        Surface.open(FileName, std::fstream::out);
        Buffer = new FColor*[Width];
        for(uint32 Index = 0; Index < Width; ++Index) {
            Buffer[Index] = new FColor[Height];
        }
    }

    PPMObject(const PPMObject& Other) = delete;

    ~PPMObject() {
        Surface.close();
        for(uint32 Index = 0; Index < Width; Index++)
        {
            delete []Buffer[Index];
            Buffer[Index] = nullptr;
        }
        delete []Buffer;
    }

public:
    void SetPixel(uint32 X, uint32 Y, const FColor& Color) const {
        Buffer[X][Y] = Color;
    }

    void Render() {
        Surface.seekg(0);
        Surface << "P3\n" << Width <<' '<< Height <<"\n255\n";
        for (uint32 X = 0; X < Width; ++X) {
            for (uint32 Y = 0; Y < Height; ++Y) {
                FColor Color = Buffer[X][Y];
                uint32 R = static_cast<int>(255.999 * Color[0]);
                uint32 G = static_cast<int>(255.999 * Color[1]);
                uint32 B = static_cast<int>(255.999 * Color[2]);
                Surface << R << ' ' << G << ' ' << B << '\n';
            }
        }
    }

public:
    uint32 Width;
    uint32 Height;

    FColor** Buffer;
    std::fstream Surface;
};
#endif //SDLGAMEENGINE_TESTGAME_H
