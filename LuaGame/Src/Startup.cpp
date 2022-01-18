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

    cout << ">> �� lua ִ�� C++ ����" << endl;
    cout << ">>>> ����Ҫ�� lua ��ע�� C++ ����" << endl;
    lua_register(L, "CCodeMyAdd", PCFCCodeMyAdd);

    cout << ">> ִ�� lua �ļ�" << endl;
    if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
        cerr << "ִ���ļ����ִ���" << endl;
        cerr << lua_tostring(L, -1) << endl;
        lua_pop(L,1);
    }

    cout << ">> C++ ���� Lua ����" << endl;
    lua_getglobal(L, "TestLuaFunction");
    lua_pushinteger(L, 123);
    lua_call(L, 1, 1);
    cout << ">> ��ȡ Lua ��������ֵ��" << lua_tostring(L, -1) << endl;
    lua_pop(L, 1);

    cout << "�ͷ� lua ��Դ" << endl;
    lua_close(L);

    cout << "---------------test c code for lua--------------------" << endl;
    return 0;
}