//
// Created by chenyifei on 2022/1/13.
//

#ifndef SDLGAMEENGINE_GRAPHICMATH_H
#define SDLGAMEENGINE_GRAPHICMATH_H

#include "SoftWarePCH.h"
#include <cmath>

template<typename T>
concept VectorType = std::is_integral<T>::value || std::is_floating_point<T>::value;

template <VectorType T>
struct FVector2{
    template<VectorType> friend std::ostream& operator<<(std::ostream& Out, const FVector2<T>& InVec);
public:
    FVector2<T>() { Coords[0] = Coords[1] = 0; }
    FVector2<T>(T InX, T InY) { Coords[0] = InX; Coords[1] = InY; }
    FVector2<T>(const FVector2<T>& InVec) : X(InVec.X), Y(InVec.Y) { *this = InVec; }
public:
    FORCEINLINE FVector2<T> operator +(const FVector2<T>& InV) const { return FVector2<T>(U + InV.U, V + InV.V); }
    FORCEINLINE FVector2<T> operator -(const FVector2<T>& InV) const { return FVector2<T>(U - InV.U, V - InV.V); }
    FORCEINLINE FVector2<T> operator *(float InF) const { return FVector2<T>(static_cast<T>(U * InF), static_cast<T>(V * InF)); }
    FORCEINLINE T& operator[] (size_t Index) { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }
    FORCEINLINE T operator[] (size_t Index) const { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }
public:
    union {
        struct {T U, V;};
        struct {T X, Y;};
        T Coords[2];
    };
};

template<VectorType T> std::ostream& operator<<(std::ostream& Out, const FVector2<T>& InVec)
{
    Out << "(" << InVec.X << ", " << InVec.Y << ")\n";
    return Out;
}

template <VectorType T>
struct FVector3{
    template<VectorType> friend std::ostream& operator<<(std::ostream& Out, const FVector3<T>& InVec);
public:
    FVector3<T>() { Coords[0] = Coords[1] = Coords[2] = 0; }
    FVector3<T>(T InX, T InY, T InZ) { Coords[0] = InX; Coords[1] = InY; Coords[2] = InZ; }
    FVector3<T>(const FVector3<T>& InVec) : X(InVec.X), Y(InVec.Y), Z(InVec.Z) { *this = InVec; }
    template <VectorType U, std::enable_if_t<std::is_same_v<float, U>, int> = 0>
    FVector3<T>(const FVector3<U>& InVec) : X(int(InVec.X + 0.5f)), Y(int(InVec.Y + 0.5f)), Z(int(InVec.Z + 0.5f)) {}
    FVector3<T>& operator=(const FVector3<T>& InVec)
    {
	    if (this != &InVec)
	    {
            X = InVec.X;
            Y = InVec.Y;
            Z = InVec.Z;
	    }
        return *this;
    }
public:
    FORCEINLINE FVector3<T> operator ^(const FVector3<T>& V) const { return FVector3<T>(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FORCEINLINE FVector3<T> operator +(const FVector3<T>& V) const { return FVector3<T>(X + V.X, Y + V.Y, Z + V.Z); }
    FORCEINLINE FVector3<T> operator -(const FVector3<T>& V) const { return FVector3<T>(X - V.X, Y - V.Y, Z - V.Z); }
    FORCEINLINE FVector3<T> operator *(float V) const { return FVector3<T>(X * V, Y * V, Z * V); }
    FORCEINLINE FVector3<T> operator +(float V) const { return FVector3<T>(X + V, Y + V, Z + V); }
    FORCEINLINE FVector3<T> operator -(float V) const { return FVector3<T>(X - V, Y - V, Z - V); }
    FORCEINLINE T operator *(const FVector3<T>& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FORCEINLINE float Norm() const { return std::sqrt(X * X + Y * Y + Z * Z); }
    FORCEINLINE FVector3<T>& Normalize(T L = 1) { *this = (*this) * (L / Norm()); return *this; }

    FORCEINLINE T& operator[] (size_t Index) { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }

    FORCEINLINE T operator[] (size_t Index) const { assert(Index < 3 && "Invalid Index"); return Coords[Index]; }

public:
    union {
        T Coords[3];
        struct {T X, Y, Z;};
        struct {T iVert, iUV, iNorm;};
    };
};

template<VectorType T>
std::ostream& operator<<(std::ostream& Out, const FVector3<T>& InVec)
{
    Out << "(" << InVec.X << ", " << InVec.Y << ", " << InVec.Z << ")\n";
    return Out;
}

struct FColor
{
public:
    FORCEINLINE explicit  FColor() { R = G = B = A = 0; };
    constexpr FORCEINLINE FColor(uint8 InR, uint8 InG, uint8 InB, uint8 InA) : R(InR), G(InG), B(InB), A(InA) {}
    FORCEINLINE FColor(const FColor& InColor) : R(InColor.R), G(InColor.G), B(InColor.B), A(InColor.A)  {}
    FORCEINLINE explicit  FColor(uint32 InColor) {
        A = uint8(InColor);
        InColor = InColor >> 8;
        B = uint8(InColor);
        InColor = InColor >> 8;
        G = uint8(InColor);
        InColor = InColor >> 8;
        R = InColor;
    }

    bool operator==(const FColor& C) { return DWColor() == C.DWColor(); }
    FORCEINLINE bool operator!=(const FColor& C) { return DWColor() != C.DWColor(); }
    FORCEINLINE FColor operator+(const FColor& InColor)
    {
        return FColor(
            (uint8)std::min((uint32)this->R + (uint32)InColor.R, (uint32)255),
            (uint8)std::min((uint32)this->G + (uint32)InColor.G, (uint32)255),
            (uint8)std::min((uint32)this->B + (uint32)InColor.B, (uint32)255),
            (uint8)std::min((uint32)this->A + (uint32)InColor.A, (uint32)255));
    }
    FORCEINLINE FColor& operator+=(const FColor& InColor)
    {
        R = (uint8)std::min((uint32)R + (uint32)InColor.R, (uint32)255);
        G = (uint8)std::min((uint32)G + (uint32)InColor.G, (uint32)255);
        B = (uint8)std::min((uint32)B + (uint32)InColor.B, (uint32)255);
        A = (uint8)std::min((uint32)A + (uint32)InColor.A, (uint32)255);
        return *this;
    }
    FORCEINLINE FColor operator-(const FColor& InColor)
    {
        return FColor(
            (uint8)std::min((uint32)this->R - (uint32)InColor.R, (uint32)255),
            (uint8)std::min((uint32)this->G - (uint32)InColor.G, (uint32)255),
            (uint8)std::min((uint32)this->B - (uint32)InColor.B, (uint32)255),
            (uint8)std::min((uint32)this->A - (uint32)InColor.A, (uint32)255));
    }
    FORCEINLINE FColor& operator-=(const FColor& InColor)
    {
        R = (uint8)std::min((uint32)R - (uint32)InColor.R, (uint32)255);
        G = (uint8)std::min((uint32)G - (uint32)InColor.G, (uint32)255);
        B = (uint8)std::min((uint32)B - (uint32)InColor.B, (uint32)255);
        A = (uint8)std::min((uint32)A - (uint32)InColor.A, (uint32)255);
        return *this;
    }
    FORCEINLINE FColor operator* (const FColor& InColor)
    {
        return FColor(
            (uint8)std::min((uint32)this->R * (uint32)InColor.R, (uint32)255),
            (uint8)std::min((uint32)this->G * (uint32)InColor.G, (uint32)255),
            (uint8)std::min((uint32)this->B * (uint32)InColor.B, (uint32)255),
            (uint8)std::min((uint32)this->A * (uint32)InColor.A, (uint32)255));
    }
    FORCEINLINE FColor& operator*= (const FColor& InColor)
    {
        R = (uint8)std::min((uint32)R * (uint32)InColor.R, (uint32)255);
        G = (uint8)std::min((uint32)G * (uint32)InColor.G, (uint32)255);
        B = (uint8)std::min((uint32)B * (uint32)InColor.B, (uint32)255);
        A = (uint8)std::min((uint32)A * (uint32)InColor.A, (uint32)255);
        return *this;
    }
    FORCEINLINE FColor operator*(float Scalar)
    {
        return FColor(
            (uint8)std::min((uint32)(this->R * Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->G * Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->B * Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->A * Scalar), (uint32)255));
    }
    FORCEINLINE FColor& operator*=(float Scalar)
    {
        R = (uint8)std::min((uint32)(this->R * Scalar), (uint32)255);
        G = (uint8)std::min((uint32)(this->R * Scalar), (uint32)255);
        B = (uint8)std::min((uint32)(this->R * Scalar), (uint32)255);
        A = (uint8)std::min((uint32)(this->R * Scalar), (uint32)255);
        return *this;
    }

    FORCEINLINE FColor operator/ (const FColor& InColor)
    {
        return FColor(
            (uint8)std::min((uint32)this->R / (uint32)InColor.R, (uint32)255),
            (uint8)std::min((uint32)this->G / (uint32)InColor.G, (uint32)255),
            (uint8)std::min((uint32)this->B / (uint32)InColor.B, (uint32)255),
            (uint8)std::min((uint32)this->A / (uint32)InColor.A, (uint32)255));
    }
    FORCEINLINE FColor& operator/= (const FColor& InColor)
    {
        R = (uint8)std::min((uint32)R / (uint32)InColor.R, (uint32)255);
        G = (uint8)std::min((uint32)G / (uint32)InColor.G, (uint32)255);
        B = (uint8)std::min((uint32)B / (uint32)InColor.B, (uint32)255);
        A = (uint8)std::min((uint32)A / (uint32)InColor.A, (uint32)255);
        return *this;
    }
    FORCEINLINE FColor operator/(float Scalar)
    {
        return FColor(
            (uint8)std::min((uint32)(this->R / Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->G / Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->B / Scalar), (uint32)255),
            (uint8)std::min((uint32)(this->A / Scalar), (uint32)255));
    }
    FORCEINLINE FColor operator/=(float Scalar)
    {
        R = (uint8)std::min((uint32)(this->R / Scalar), (uint32)255);
        G = (uint8)std::min((uint32)(this->R / Scalar), (uint32)255);
        B = (uint8)std::min((uint32)(this->R / Scalar), (uint32)255);
        A = (uint8)std::min((uint32)(this->R / Scalar), (uint32)255);
        return *this;
    }
public:
    struct { uint8 R, G, B, A; };
    FORCEINLINE const uint32 DWColor() const { return uint32(R << 24 | G << 16 | B << 8 | A); }
};

using FVector3i = FVector3<int>;
using FVector3f = FVector3<float>;
using FVector2f = FVector2<float>;
using FVector2i = FVector2<int>;
using FVector2ui = FVector2<uint32>;
using FPoint3f = FVector3f;

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

namespace Color{
    static FColor White(255, 255, 255, 255);
    static FColor Sky(173, 216, 230, 255);
    static FColor Black(0, 0, 0, 255);
    static FColor Red(255, 0, 0, 255);
    static FColor Green(0, 255, 0, 255);
    static FColor Blue(0, 0, 255, 255);
}


FORCEINLINE FVector3i VectorCast(const FVector3f& InVec)
{
    return FVector3i(int(InVec.X + 0.5f), int(InVec.Y + 0.5f), int(InVec.Z + 0.5f));
}

FORCEINLINE FVector3f VectorCast(const FVector3i& InVec)
{
    return FVector3f(float(InVec.X), float(InVec.Y), float(InVec.Z));
}
 
#endif //SDLGAMEENGINE_GRAPHICMATH_H
