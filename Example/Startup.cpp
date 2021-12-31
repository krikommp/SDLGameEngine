// //
// // Created by kriko on 2021/12/26.
// //

#include <iostream>

#include <GameFramework/Actor.h>
#include <Components/SceneComponent.h>
class MyActor : public Actor
{
public:
    MyActor();
    ~MyActor();

public:
    virtual void Tick(float DeltaSeconds) override;
};

MyActor::MyActor()
{
    RootComponent = std::make_shared<SceneCompoent>();
    const auto TestSceneComponent = std::make_shared<SceneCompoent>();
    TestSceneComponent->AttachToComponent(RootComponent);
}

MyActor::~MyActor()
{
}

void MyActor::Tick(float DeltaSeconds)
{
    if (RootComponent != nullptr)
    {
        auto Transform = RootComponent->GetTransform();
        std::cout << Transform.ToString() << std::endl;

        printf("RootComponet Children Size = %lu\n", RootComponent->GetAttachChildren().size());
    }
    else
    {
        printf("RootComponent is nullptr!\n");
    }
}

#include <UDRefl/UDRefl.hpp>
#include <cmath>

using namespace Ubpa;
using namespace Ubpa::UDRefl;

struct FVector{
    float X;
    float Y;
    float Normalize() const { return std::sqrt(X * X + Y * Y); }
};

#include <array>

template <std::size_t ...N>
static constexpr auto SquareNums(std::size_t Index, std::index_sequence<N...>) {
    constexpr auto Nums = std::array{ N * N ... };
    return Nums[Index];
}

template <std::size_t N>
constexpr static auto ConstNums(std::size_t Index) {
    return SquareNums(Index, std::make_index_sequence<N>{});
}

#include <tuple>

template <typename Tuple, typename Func, std::size_t ... N>
void FunCallTuple(const Tuple& T, Func&& Function, std::index_sequence<N...>){
    static_cast<void>(std::initializer_list<int>{ ( Function(std::get<N>(T)), 0 ) ... } );
}

template <typename ... Args, typename Func>
void TravelTuple (const std::tuple<Args...>& T, Func&& Function) {
    FunCallTuple(T, std::forward<Func>(Function), std::make_index_sequence<sizeof...(Args)>());
}

template <typename... Ts>
void Magic(Ts... Args)
{
    std::cout << sizeof...(Args) << std::endl;
}

template <typename T0>
void Printf(T0 Value)
{
    std::cout << Value << std::endl;
}

template <typename T, typename... Ts>
void Printf(T Value, Ts... Args)
{
    std::cout << Value << ", ";
    Printf(Args...);
}

template <typename T, typename... Ts>
void Printf2(T Value, Ts... Args) {
    std::cout << Value << ", ";
    if constexpr( sizeof...(Args) > 0 ) {
        Printf2(Args...);
    }else {
        std::cout << std::endl;
    }
}

int main(int argc, char **args)
{
    // MyActor actor;
    // actor.Tick(0.5f);

//    Mngr.RegisterType<FVector>();
//    Mngr.AddField<&FVector::X>("X");
//    Mngr.AddField<&FVector::Y>("Y");
//    Mngr.AddMethod<&FVector::Normalize>("Normalize");
//
//    SharedObject V = Mngr.MakeShared(Type_of<FVector>);
//    std::cout << V.GetType().GetName() << std::endl;
//
//    V.Var("x") = 3;
//    V.Var("y") = 4;
//
//    std::cout << "x: " << V.Var("x") << std::endl;
//    std::cout << "norm: " << V.Invoke("norm") << std::endl;
//
//    for (auto&& [name, info] : FieldRange_of<FVector>)
//        std::cout << name.GetView() << std::endl;
//
//    for (auto&& [name, info] : MethodRange_of<FVector>)
//        std::cout << name.GetView() << std::endl;
//
//    for (auto&& [name, var] : V.GetVars())
//        std::cout << name.GetView() << ": " << var << std::endl;
//
//    std::cout << TypeID_of<float>.GetValue() << std::endl;


//    if (ConstNums<101>(100) == 100 * 100) {
//        printf("Equal\n");
//    }else {
//        printf("No Equal\n");
//    }

    auto t = std::make_tuple(1, 4.56, "happen lee");
    TravelTuple(t, [](auto&& item) {
        std::cout << item << ",";
    });
    std::cout << std::endl;

    Printf2("Hello World", 2, 2.04, 0x001);

    return 0;
}