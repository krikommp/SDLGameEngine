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

#include <cmath>

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

template <std::size_t ...N>
void PrintfIndexSequence(std::index_sequence<N...>) {
    Printf2(N...);
}

template <typename T, T... Ins> class TestClass {
public:
    void Test() {
        std::cout << "In TestCLass Func Test = ";
        Printf2(Ins...);
    }
};

template <int... N>
struct IndexSeq{};

template <int N, int... M>
struct MakeIndexSeq : public MakeIndexSeq<N - 1, N - 1, M...> {};

template <int... M>
struct MakeIndexSeq<0, M...> : public IndexSeq<M...> {};

template <int... N>
void TestMakeIndex(IndexSeq<N...>) {
    Printf2(N...);
}

#include <tuple>

template <typename Tuple, typename Func, size_t... N>
void FunCallTuple(const Tuple& tuple, Func&& Function, std::index_sequence<N...>) {
    // 用到了逗号运算符，会返回逗号后面的数值
    static_cast<void>(std::initializer_list<int>{ (Function(std::get<N>(tuple)), 0)... });
}

template <typename... Args, typename Function>
void TravelTuple(const std::tuple<Args...>& InTuple, Function&& Lambda) {
    FunCallTuple(InTuple, std::forward<Function>(Lambda), std::make_index_sequence<sizeof...(Args)>());
}

constexpr static std::size_t ConstNums[] = { 0, 1, 4 ,9, 16 };

template <typename T, std::size_t... N>
constexpr decltype(auto) PrepareImpl(T Arg, std::index_sequence<N...>) {
    return std::integer_sequence<char, T::get()[N]...>();
}

template <typename T>
constexpr decltype(auto) Prepare(T Arg) {
    return PrepareImpl(Arg, std::make_index_sequence<sizeof(T::get()) - 1>());
}

#define STRING(S) \
    (Prepare([] { \
    struct tmp { static constexpr decltype(auto) get() { return S; } }; \
    return tmp{}; \
    }()))


template <typename T>
int Compare(const T Left, const T Right) {
    std::cout << "这是一个泛化的函数" << std::endl;
    return (Left - Right);
}

template < >
int Compare(const char* Left, const char* Right) {
    std::cout << "这是一个特化的函数" << std::endl;
    return strcmp(Left, Right);
}

template <typename T>
class DetectX{
    struct Fallback { int X; };
    struct Derived : T, Fallback { };

    template<class U, U> struct Check;

    typedef char ArrayOfOne[1];
    typedef char ArrayOfTwo[2];

    template<class U> static ArrayOfOne & Func(Check<int Fallback::*, &U::X>* );

    template<class U> static ArrayOfTwo & Func(...);

public:
    typedef DetectX type;
    enum { value = sizeof(Func<Derived>(0)) == 2 };
};

struct ValueClass_1{
public:
    std::string Name = "Name";
    std::string ShaderParameterName = "ShaderParameterName";
    uint32_t Index = 0;
    uint32_t Association = 0;
};

struct ValueClass_2{
public:
    std::string Name = "Name";
    std::string ShaderParameterName = "ShaderParameterName";
    uint32_t Index = 0;
    uint32_t Association = 0;
    std::string GroupName = "GroupName";
    float X;
};

struct ValueClass_3{
public:
    std::string Name = "Name";
    std::string ShaderParameterName = "ShaderParameterName";
    uint32_t Index = 0;
    uint32_t Association = 0;
    std::string GroupName = "GroupName";
    std::string Desc = "Desc";
};

class Parent{
public:
    int X;
};

class Child : public Parent{
public:
    Child(int InA, int InB) { Child::X = InA; Parent::X = InB; }

    void Debug() {
        std::cout << "Child X = " << Child::X << std::endl;
        std::cout << "Parent X = " << Parent::X << std::endl;
     }
public:
    int X;
};

class TValue {
public:
    // std::string X;
    float X;
};

class BValue {
public:
    int X;
};

class CValue : public BValue, public TValue{

};

template <class U, U>
struct Check{};

template <class U>
void CheckFunc(Check<int BValue::*, &U::X>*) {
    std::cout << "no X value" << std::endl;
}

template <class U>
void CheckFunc(...) {
    std::cout << "has X value" << std::endl;
}

int main(int argc, char **args)
{
    // MyActor actor;
    // actor.Tick(0.5f);

    Printf2("Hello World", 2, 2.04, 0x001);
    // PrintfIndexSequence(std::make_index_sequence<10>());
    TestClass<int, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0> a;
    a.Test();

    TestMakeIndex(MakeIndexSeq<100>());

    auto T = std::make_tuple(1, 0.3545, "Happy Day");
    TravelTuple(T, [](auto&& Item){
        std::cout << Item << ", ";
    });
    std::cout << std::endl;

    auto Str = STRING("1234");
    using Tyu = decltype(Str);
    static_assert(std::is_same<Tyu, std::integer_sequence<char, '1', '2', '3', '4'>>::value, "WTF");

    Compare(12, 13);
    Compare("My", "My");

    Child CCC(1, 2);
    CCC.Debug();

    std::cout << DetectX<ValueClass_2>::value << std::endl;

    CheckFunc<CValue>(0);

    return 0;
}