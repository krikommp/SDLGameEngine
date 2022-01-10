//
// Created by chenyifei on 2021/12/29.
//
#include <iostream>
#include <chrono>

#include "LaunchEngineLoop.h"

EngineLoop GEngineLoop;

bool IsEngineExitRequested = false;

/**
 * 预先初始化流程
 * 包括一些子系统的初始化
 * @return
 */
int EnginePreInit() {
    int ErrorLevel = GEngineLoop.PreInit();
    return ErrorLevel;
}

/**
 * 初始化引擎循环
 * @return
 */
int EngineInit() {
    int ErrorLevel = GEngineLoop.Init();
    return ErrorLevel;
}

/**
 * 引擎循环
 */
void EngineTick( /* void */ ) {
    GEngineLoop.Tick();
}

/**
 * 引擎退出
 */
void EngineExit() {
    GEngineLoop.Exit();
}


int GuardedMain() {
    int ErrorLevel = EnginePreInit();

    {
        ErrorLevel = EngineInit();
    }

    while(!IsEngineExitRequested) {
        EngineTick();
    }

    EngineExit();
    return 0;
}