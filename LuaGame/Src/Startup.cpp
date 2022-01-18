#include "kaguya.hpp"

#include <iostream>

class ABC {
public:
    ABC() : Value(0) {}
    ABC(int InValue) : Value(InValue) {}
    int GetValue() const { return Value; }
    void SetValue(int InValue) { Value = InValue; }
    void OverLoad1() { std::cout << "call OverLoad1" << std::endl; }
    void OverLoad2(int) { std::cout << "call OverLoad2" << std::endl; }
private:
    int Value;
};

void ConstructABC(kaguya::State& State) {
    State["ABC"].setClass(kaguya::UserdataMetatable<ABC>()
            .setConstructors<ABC(), ABC(int)>()
            .addFunction("get_value", &ABC::GetValue)
            .addFunction("set_value", &ABC::SetValue)
            .addOverloadedFunctions("overload", &ABC::OverLoad1, &ABC::OverLoad2)
            .addStaticFunction("nomemberfunc", [](ABC* self, int){ return 1; }));
}

int main() {
    kaguya::State state;
    state["Table1"] = kaguya::NewTable();
    kaguya::LuaTable Table1 = state["Table1"];
    Table1["Value"] = 1;
    ConstructABC(state);
    state.dofile("./LuaSrc/Startup.lua");


    return 0;
}