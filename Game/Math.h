//
// Created by chenyifei on 2022/1/13.
//

#ifndef SDLGAMEENGINE_MATH_H
#define SDLGAMEENGINE_MATH_H

template <typename T, std::size_t N>
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
    T& operator[] (std::size_t Index) {
        assert(Index < N && "Invalid Index");
        return Coords[Index];
    }

    T operator[] (std::size_t Index) const {
        assert(Index < N && "Invalid Index");
        return Coords[Index];
    }

private:
    T Coords[N];
};

using FVector3f = FPoint<float, 3>;
using FColor = FVector3f;
using FPoint3f = FVector3f;

template<typename T, std::size_t N>
std::ostream& operator<< (std::ostream& OS, const FPoint<T, N>& Point) {
    OS << "(";
    for (std::size_t Index = 0; Index < N - 1; ++Index) {
        OS << Point[Index];
        OS << ",";
    }
    OS << Point[N - 1];
    OS << ")";
    return OS;
}


#endif //SDLGAMEENGINE_MATH_H
