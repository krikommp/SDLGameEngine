//
// Created by chenyifei on 2022/1/13.
//

#ifndef SDLGAMEENGINE_GRAPHICMATH_H
#define SDLGAMEENGINE_GRAPHICMATH_H

#include "SortWarePCH.h"

template <typename T, size_t N>
class FPoint{
    template<typename ...Args, typename Function> void UnPack(Function Lambda, T Value, Args... Values)
    {
        Lambda(Value);
        if constexpr(sizeof...(Values) > 0) {
            UnPack(Lambda, Values...);
        }
    };
private:
public:
    FPoint() {
        for(unsigned int Index = 0; Index < N; ++Index) {
            Coords[Index] = 0;
        }
    }
    explicit FPoint(T InCoords[N]) {
        for(unsigned int Index = 0; Index < N; ++Index) {
            Coords[Index] = InCoords[Index];
        }
    }

    template<typename ...Args>
    explicit FPoint(Args... InArgs) {
        static_assert(sizeof...(InArgs) == N);
        unsigned int Index = 0;
        UnPack([&](auto Value){
            Coords[Index] = Value;
            ++Index;
        }, InArgs...);
    }

public:
    T& operator[] (size_t Index) {
        assert(Index < N && "Invalid Index");
        return Coords[Index];
    }

    T operator[] (size_t Index) const {
        assert(Index < N && "Invalid Index");
        return Coords[Index];
    }

private:
    T Coords[N];
};

using FVector3f = FPoint<float, 3>;
using FColor = FPoint<uint8, 4>;
using FPoint3f = FVector3f;

static uint32 ConvertColorToHEX(const FColor& Color) {
    // R G B A
    uint32 FormatColor = (Color[0] << 24) | (Color[1] << 16) | (Color[2] << 8) | (Color[3]);
    return FormatColor;
}

#endif //SDLGAMEENGINE_GRAPHICMATH_H
