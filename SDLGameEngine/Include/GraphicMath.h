//
// Created by chenyifei on 2022/1/13.
//

#ifndef SDLGAMEENGINE_GRAPHICMATH_H
#define SDLGAMEENGINE_GRAPHICMATH_H

#include "SoftWarePCH.h"
#include <cmath>

template<typename T>
concept VectorType = std::is_integral<T>::value || std::is_floating_point<T>::value;

template <VectorType T, size_t N>
class FPoint{
    template<VectorType ...Args, typename Function> void UnPack(Function Lambda, T Value, Args... Values)
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

    template<VectorType ...Args>
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

template <VectorType T>
class FPoint<T, 2>{
public:
    FPoint() { Coords[0] = Coords[1] = 0; }
    FPoint(T InX, T InY) { Coords[0] = InX; Coords[1] = InY; }

public:
    FORCEINLINE FPoint<T, 2> operator +(const FPoint<T, 2>& InV) const { return FPoint<T, 2>(U + InV.U, V + InV.V); }
    FORCEINLINE FPoint<T, 2> operator -(const FPoint<T, 2>& InV) const { return FPoint<T, 2>(U - InV.U, V - InV.V); }
    FORCEINLINE FPoint<T, 2> operator *(float InF) const { return FPoint<T, 2>(static_cast<T>(U * InF), static_cast<T>(V * InF)); }
    FORCEINLINE T& operator[] (size_t Index) { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }
    FORCEINLINE T operator[] (size_t Index) const { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }
public:
    union {
        struct {T U, V;};
        struct {T X, Y;};
        T Coords[2];
    };
};

template <VectorType T>
class FPoint<T, 3> {
public:
    FPoint() { Coords[0] = Coords[1] = Coords[2] = 0; }
    FPoint(T InX, T InY, T InZ) { Coords[0] = InX; Coords[1] = InY; Coords[2] = InZ; }

public:

    FORCEINLINE FPoint<T, 3> operator ^(const FPoint<T, 3>& V) const { return FPoint<T, 3>(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FORCEINLINE FPoint<T, 3> operator +(const FPoint<T, 3>& V) const { return FPoint<T, 3>(X + V.X, Y + V.Y, Z + V.Z); }
    FORCEINLINE FPoint<T, 3> operator -(const FPoint<T, 3>& V) const { return FPoint<T, 3>(X - V.X, Y - V.Y, Z - V.Z); }
    FORCEINLINE FPoint<T, 3> operator *(float V) const { return FPoint<T, 3>(X * V, Y * V, Z * V); }
    FORCEINLINE FPoint<T, 3> operator +(float V) const { return FPoint<T, 3>(X + V, Y + V, Z + V); }
    FORCEINLINE FPoint<T, 3> operator -(float V) const { return FPoint<T, 3>(X - V, Y - V, Z - V); }
    FORCEINLINE T operator *(const FPoint<T, 3>& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FORCEINLINE float Norm() const { return std::sqrt(X * X + Y * Y + Z * Z); }
    FORCEINLINE FPoint<T, 3>& Normalize(T L = 1) { *this = (*this) * (L / Norm()); return *this; }

    FORCEINLINE T& operator[] (size_t Index) { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }

    FORCEINLINE T operator[] (size_t Index) const { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }

public:
    union {
        T Coords[3];
        struct {T X, Y, Z;};
        struct {T iVert, iUV, iNorm;};
    };
};

template <VectorType T, size_t N>
FPoint<T, N> operator/(const FPoint<T, N>& InPoint, T Value) {
    FPoint<T, N> Res;
    for (uint32 Index = 0; Index < N; ++Index) {
        Res[Index] = InPoint[Index] / Value;
    }
    return Res;
}

template <VectorType T, size_t N>
std::ostream& operator<<(std::ostream& Out, const FPoint<T, N>& Value)
{
    Out << "(";
    for (uint32 i = 0;i < N - 1; ++i)
    {
        Out << Value[i] << ", ";
    }
    Out << Value[N - 1];
    Out << ")";
    return Out;
}

template <VectorType T, size_t N>
FORCEINLINE void Swap(FPoint<T, N>& Left, FPoint<T, N>& Right) {
    FPoint<T, N> Tmp;
    for (uint32 Index = 0; Index < N; ++Index) {
        Tmp[Index] = Left[Index];
        Left[Index] = Right[Index];
        Right[Index] = Tmp[Index];
    }
}

template <size_t N>
FORCEINLINE FPoint<float, N> VectorCast(const FPoint<int, N>& InVec) {
    FPoint<float, N> Res;
    for (uint32 i = 0; i < N; ++i) {
        Res[i] = float(InVec[i] + 0.5f);
    }
    return Res;
}

template <size_t N>
FORCEINLINE FPoint<int, N> VectorCast(const FPoint<float, N>& InVec) {
    FPoint<int, N> Res;
    for (uint32 i = 0; i < N; ++i) {
        Res[i] = int(InVec[i]);
    }
    return Res;
}

using FVector3i = FPoint<int, 3>;
using FVector3f = FPoint<float, 3>;
using FColor = FPoint<uint8, 4>;
using FVector2f = FPoint<float, 2>;
using FVector2i = FPoint<int, 2>;
using FVector2ui = FPoint<uint32, 2>;
using FPoint3f = FVector3f;
using FVector3 = FPoint<double, 3>;

template <VectorType T>
FORCEINLINE FPoint<T, 3>  Cross(FPoint<T, 3> V1, const FPoint<T, 3>& V2) {
    return FPoint<T, 3>{V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X};
}

constexpr int DEFAULT_ALLOC = 4;

class Matrix {
    friend std::ostream& operator<<(std::ostream& In, Matrix& InM);
public:
    Matrix(int InRows = DEFAULT_ALLOC, int InCols = DEFAULT_ALLOC);
    FORCEINLINE int GetCol();
    FORCEINLINE int GetRow();

    static Matrix Identity(int Dimensions);
    std::vector<float>& operator[] (const int Idx);
    Matrix operator*(const Matrix& InA);
    Matrix Transpose();
    Matrix Inverse();
private:
    std::vector<std::vector<float>> M;
    int Rows, Cols;
};

FORCEINLINE static uint32 ConvertColorToHEX(const FColor& Color) {
    // R G B A
    uint32 FormatColor = (Color[0] << 24) | (Color[1] << 16) | (Color[2] << 8) | (Color[3]);
    return FormatColor;
}

namespace Color{
    static FColor White(255, 255, 255, 255);
    static FColor Sky(173, 216, 230, 255);
    static FColor Black(0, 0, 0, 255);
    static FColor Red(255, 0, 0, 255);
    static FColor Green(0, 255, 0, 255);
    static FColor Blue(0, 0, 255, 255);
}

#endif //SDLGAMEENGINE_GRAPHICMATH_H
