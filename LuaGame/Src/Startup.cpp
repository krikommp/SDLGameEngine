//
// Created by chenyifei on 2022/1/18.
//
#include "LuaGamePCH.h"

using namespace std;

EXPORTC long long CCodeMyAdd(long long A, long long B) {
    return A + B;
}

EXPORTC int PCFCCodeMyAdd(lua_State* L) {
    long long A = lua_tointeger(L, -2);
    long long B = lua_tointeger(L, -1);
    long long Ret = CCodeMyAdd(A, B);
    lua_pushinteger(L, Ret);
    return 1;
}

int main(int argc, char *argv[]) {
    cout << "---------------test c code for lua--------------------" << endl;
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, "./LuaSrc/Startup.lua")) {
        cerr << "Load Lua file Error" << endl;
        cerr << lua_tostring(L, -1) << endl;
        lua_pop(L,1);
    }

    cout << ">> 从 lua 执行 C++ 方法" << endl;
    cout << ">>>> 首先要在 lua 中注册 C++ 方法" << endl;
    lua_register(L, "CCodeMyAdd", PCFCCodeMyAdd);

    cout << ">> 执行 lua 文件" << endl;
    if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
        cerr << "执行文件出现错误" << endl;
        cerr << lua_tostring(L, -1) << endl;
        lua_pop(L,1);
    }

    cout << ">> C++ 调用 Lua 函数" << endl;
    lua_getglobal(L, "TestLuaFunction");
    lua_pushinteger(L, 123);
    lua_call(L, 1, 1);
    cout << ">> 获取 Lua 函数返回值：" << lua_tostring(L, -1) << endl;
    lua_pop(L, 1);

    cout << "释放 lua 资源" << endl;
    lua_close(L);

    cout << "---------------test c code for lua--------------------" << endl;
    return 0;
}