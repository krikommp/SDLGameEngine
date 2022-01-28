// //
// // Created by kriko on 2021/12/26.
// //
//
//#include <iostream>
//
//#include <GameFramework/Actor.h>
//#include <Components/SceneComponent.h>
//class MyActor : public Actor
//{
//public:
//    MyActor();
//    ~MyActor();
//
//public:
//    virtual void Tick(float DeltaSeconds) override;
//};
//
//MyActor::MyActor()
//{
//    RootComponent = std::make_shared<SceneCompoent>();
//    const auto TestSceneComponent = std::make_shared<SceneCompoent>();
//    TestSceneComponent->AttachToComponent(RootComponent);
//}
//
//MyActor::~MyActor()
//{
//}
//
//void MyActor::Tick(float DeltaSeconds)
//{
//    if (RootComponent != nullptr)
//    {
//        auto Transform = RootComponent->GetTransform();
//        std::cout << Transform.ToString() << std::endl;
//
//        printf("RootComponet Children Size = %lu\n", RootComponent->GetAttachChildren().size());
//    }
//    else
//    {
//        printf("RootComponent is nullptr!\n");
//    }
//}
//
//#include <cmath>
//
//template <typename... Ts>
//void Magic(Ts... Args)
//{
//    std::cout << sizeof...(Args) << std::endl;
//}
//
//template <typename T0>
//void Printf(T0 Value)
//{
//    std::cout << Value << std::endl;
//}
//
//template <typename T, typename... Ts>
//void Printf(T Value, Ts... Args)
//{
//    std::cout << Value << ", ";
//    Printf(Args...);
//}
//
//template <typename T, typename... Ts>
//void Printf2(T Value, Ts... Args) {
//    std::cout << Value << ", ";
//    if constexpr( sizeof...(Args) > 0 ) {
//        Printf2(Args...);
//    }else {
//        std::cout << std::endl;
//    }
//}
//
//template <std::size_t ...N>
//void PrintfIndexSequence(std::index_sequence<N...>) {
//    Printf2(N...);
//}
//
//template <typename T, T... Ins> class TestClass {
//public:
//    void Test() {
//        std::cout << "In TestCLass Func Test = ";
//        Printf2(Ins...);
//    }
//};
//
//template <int... N>
//struct IndexSeq{};
//
//template <int N, int... M>
//struct MakeIndexSeq : public MakeIndexSeq<N - 1, N - 1, M...> {};
//
//template <int... M>
//struct MakeIndexSeq<0, M...> : public IndexSeq<M...> {};
//
//template <int... N>
//void TestMakeIndex(IndexSeq<N...>) {
//    Printf2(N...);
//}
//
//#include <tuple>
//
//template <typename Tuple, typename Func, size_t... N>
//void FunCallTuple(const Tuple& tuple, Func&& Function, std::index_sequence<N...>) {
//    // ?????????????????????????????
//    static_cast<void>(std::initializer_list<int>{ (Function(std::get<N>(tuple)), 0)... });
//}
//
//template <typename... Args, typename Function>
//void TravelTuple(const std::tuple<Args...>& InTuple, Function&& Lambda) {
//    FunCallTuple(InTuple, std::forward<Function>(Lambda), std::make_index_sequence<sizeof...(Args)>());
//}
//
//constexpr static std::size_t ConstNums[] = { 0, 1, 4 ,9, 16 };
//
//template <typename T, std::size_t... N>
//constexpr decltype(auto) PrepareImpl(T Arg, std::index_sequence<N...>) {
//    return std::integer_sequence<char, T::get()[N]...>();
//}
//
//template <typename T>
//constexpr decltype(auto) Prepare(T Arg) {
//    return PrepareImpl(Arg, std::make_index_sequence<sizeof(T::get()) - 1>());
//}
//
//#define STRING(S) \
//    (Prepare([] { \
//    struct tmp { static constexpr decltype(auto) get() { return S; } }; \
//    return tmp{}; \
//    }()))
//class TestAA{
//public:
//        void f1() { std::cout << "f1 function" << std::endl; }
//    };
//
//class TestBB{};
//
//template <typename T> struct HasMemberF1{
//private:
//    template<typename U>
//    static auto Check(int) -> decltype( std::declval<U>().f1(), std::true_type() );
//    template<typename U>
//    static std::false_type Check(...);
//
//public:
//        enum { Value = std::is_same<decltype(Check<T>(0)), std::true_type>::value };
//};
//
//#include <cassert>
//
//template <typename T, std::size_t N>
//class FPoint{
//    template<typename ...Args, typename Function> void UnPack(Function Lambda, T Value, Args... Values)
//    {
//        if constexpr(sizeof...(Values) > 0) {
//            UnPack(Lambda, Values...);
//        }
//        Lambda(Value);
//    };
//private:
//public:
//    FPoint() {
//        for(unsigned int Index = 0; Index < N; ++Index) {
//            Coords[Index] = 0;
//        }
//    }
//    explicit FPoint(T InCoords[N]) {
//        for(unsigned int Index = 0; Index < N; ++Index) {
//            Coords[Index] = InCoords[Index];
//        }
//    }
//
//    template<typename ...Args>
//    explicit FPoint(Args... InArgs) {
//        static_assert(sizeof...(InArgs) == N);
//        unsigned int Index = 0;
//        UnPack([&](auto Value){
//            Coords[Index] = Value;
//            ++Index;
//        }, InArgs...);
//    }
//
//public:
//    T& operator[] (std::size_t Index) {
//        assert(Index < N && "Invalid Index");
//        return Coords[Index];
//    }
//
//    T operator[] (std::size_t Index) const {
//        assert(Index < N && "Invalid Index");
//        return Coords[Index];
//    }
//
//private:
//    T Coords[N];
//};
//
//template<typename T, std::size_t N>
//std::ostream& operator<< (std::ostream& OS, const FPoint<T, N>& Point) {
//    OS << "(";
//    for (std::size_t Index = 0; Index < N - 1; ++Index) {
//        OS << Point[Index];
//        OS << ",";
//    }
//    OS << Point[N - 1];
//    OS << ")";
//    return OS;
//}
//
//class FShape{};
//
//class FCircle : public FShape{};
//
//using FPoint3f =  FPoint<float, 3>;
//
//#include "Startup.h"
//#include "../Game/Include/GraphicMath.h"
//
//
//class Foo{
//public:
//    Foo() { std::cout << "Foo Construct" << std::endl; }
//};
//
//class Bar {
//public:
//    Foo foo;
//    char* str;
//};
//
//class Dopey{
//public:
//    Dopey() { std::cout << "Dopey Construct" << std::endl; }
//};
//
//class Sneezy{
//public:
//    Sneezy() { std::cout << "Sneezy Construct" << std::endl; }
//    Sneezy(int i) { std::cout << "Sneezy i Construct" << std::endl; }
//};
//
//class Bashful{
//public:
//    Bashful() { std::cout << "Bashful Construct" << std::endl; }
//};
//
//class DerivedSneezy : public Sneezy {
//
//};
//
//class WithConstruct {
//public:
//    WithConstruct(int i) : i(i) { std::cout << "WithConstruct" << std::endl; }
//
//private:
//    int i;
//};
//
//class ShowWhite{
//public:
//public:
//    Dopey Dopey;
//    Sneezy Sneezy;
//    Bashful Bashful;
//
//    int Num;
//};
//
//class MyString{
//public:
//    MyString() : Str(nullptr), Len(0) {}
//
//    explicit MyString(const char* InStr) {
//        Len = strlen(InStr) + 1;
//        Str = (char*) malloc(Len);
//        strcpy_s(Str, Len, InStr);
//    }
//
//    // Error!! if no explicit copy construct, difference String class will has same pointer point to same memory
//    // when destruct, this memory will be released twice!!
//    MyString(const MyString& Other) {
//        Str = (char*) malloc(Other.Len);
//        Len = Other.Len;
//        strcpy_s(Str, Len, Other.Str);
//    }
//
//    ~MyString() { delete[] Str; Str = nullptr; Len = 0; }
//public:
//    char* Str;
//    std::size_t Len;
//};
//
//std::ostream& operator<< (std::ostream& Out, const MyString& String) {
//    Out << String.Str;
//    return Out;
//}
//
//class MyWorld{
//public:
//    int Occurs;
//    MyString String;
//};
//
//#include <lua.hpp>
//
//extern "C" {
//    static int l_cppfunction(lua_State* L) {
//        double arg = luaL_checknumber(L, 1);
//        lua_pushnumber(L, arg * 0.5);
//        return 1;
//    }
//}
//#include <iostream>
//#include <initializer_list>
//#include <algorithm>
//
//using namespace std;
//
//template <int... N>
//class VSS {
//public:
//    VSS()  {
//        auto arr = std::initializer_list<int>{(std::cout << N, 0)...};
//        std::cout << std::endl;
//        for (auto iter : arr) {
//            std::cout << iter << std::endl;
//        }
//    }
//};
//
//int main() {
//    VSS<1, 3, 4, 5> a;
//    return 0;
//}

//int main(int argc, char* argv[]) {
//    lua_State *L;
//    L = luaL_newstate();
//    luaL_openlibs(L);
//    if (luaL_loadfile(L, "F:\\CppProjects\\SDLGameEngine\\Example\\luascript.lua")) {
//        cerr << "Load Lua file Error" << endl;
//        cerr << lua_tostring(L, -1) << endl;
//        lua_pop(L,1);
//    }
//
//    cout << ">> 从 C++ 写入数据到 cppvar" << endl;
//    lua_pushnumber(L, 1.1);
//    lua_setglobal(L, "cppvar");
//
//    cout << ">> 执行 lua 文件" << endl << endl;
//    if (lua_pcall(L,0, LUA_MULTRET, 0)) {
//        cerr << "执行文件出现错误" << endl;
//        cerr << lua_tostring(L, -1) << endl;
//        lua_pop(L,1);
//    }
//
//    cout << ">> 从 lua 中读取全局变量 luavar 到 C++" << endl;
//    lua_getglobal(L, "luavar");
//    double luavar = lua_tonumber(L,-1);
//    lua_pop(L,1);
//    cout << "C++ 从 Lua 读取到的 luavar = " << luavar << endl << endl;
//
//    cout << ">> 从 lua 中执行 myfunction 方法" << endl;
//    lua_getglobal(L, "myluafunction");
//    lua_pushnumber(L, 5);
//    lua_pcall(L, 1, 1, 0);
//    cout << "函数的返回值的: " << lua_tostring(L, -1) << endl << endl;
//    lua_pop(L,1);
//
//    cout << ">> 从 lua 执行 C++ 方法" << endl;
//    cout << ">>>> 首先要在 lua 中注册 C++ 方法" << endl;
//    lua_pushcfunction(L,l_cppfunction);
//    lua_setglobal(L, "cppfunction");
//
//    cout << ">>>> 调用 lua 函数以执行 c++ 函数" << endl;
//    lua_getglobal(L, "myfunction");
//    lua_pushnumber(L, 5);
//    lua_pcall(L, 1, 1, 0);
//    cout << "函数的返回值是：" << lua_tonumber(L, -1) << endl << endl;
//    lua_pop(L,1);
//
//    cout << "释放 lua 资源" << endl;
//    lua_close(L);
//
//    return 0;
//}

//int main(int argc, char **args)
//{
//    // MyActor actor;
//    // actor.Tick(0.5f);
//
//    Printf2("Hello World", 2, 2.04, 0x001);
//    // PrintfIndexSequence(std::make_index_sequence<10>());
//    TestClass<int, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0> a;
//    a.Test();
//
//    TestMakeIndex(MakeIndexSeq<100>());
//
//    auto T = std::make_tuple(1, 0.3545, "Happy Day");
//    TravelTuple(T, [](auto&& Item){
//        std::cout << Item << ", ";
//    });
//    std::cout << std::endl;
//
//    auto Str = STRING("1234");
//    using Tyu = decltype(Str);
//    static_assert(std::is_same<Tyu, std::integer_sequence<char, '1', '2', '3', '4'>>::value, "WTF");
//
//    if ( HasMemberF1<TestBB>::Value ) {
//        std::cout << "Has F1 function" << std::endl;
//    }else {
//        std::cout << "No F1 Function" << std::endl;
//    }
//
//    std::cout << "============" << std::endl;
//    FPoint<double, 3> Location(1.0, 0.5, 0.2);
//    std::cout << Location << std::endl;
//
//    FCircle* pCircle = new FCircle();
//    FShape* pShape = dynamic_cast<FCircle*>(pCircle);
//
//    Bar bar;
//    ShowWhite ShowWhite;
//
//    std::cout << "============" << std::endl;
//    DerivedSneezy DerivedSneezy;
//
//    std::cout << "============" << std::endl;
//    MyString Strss("Hello World");
//    MyString SSA = Strss;
//    std::cout << Strss << std::endl;
//    std::cout << SSA << std::endl;
//    std::cout << "============" << std::endl;
//    return 0;
//}

#include <iostream>

class MyTest {
    // friend MyTest operator+ (const MyTest&, const MyTest&);
    friend std::ostream & operator<<(std::ostream& Out, MyTest& In);
    friend std::ostream & operator<<(std::ostream& Out, MyTest&& In);

public:
    MyTest operator+(const MyTest& In) const {
        MyTest Result;
        Result.a = In.a + a;
        return Result;
    }
public:
    MyTest() : a(0) {}
    explicit MyTest(int InA) : a(InA) {}
private:
    int a;
};

std::ostream & operator<<(std::ostream& Out, MyTest& In) {
    Out << "A Value is = " << In.a << std::endl;
    return Out;
}
std::ostream & operator<<(std::ostream& Out, MyTest&& In) {
    Out << "A Value is = " << In.a << std::endl;
    return Out;
}

int main() {
    MyTest a(1);
    MyTest b(2);
    MyTest c = a + b;
    std::cout << c << std::endl;
    std::cout << a + c << std::endl;
}