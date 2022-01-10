//
// Created by chenyifei on 2021/12/29.
//
#include <iostream>
#include <chrono>

#include "LaunchEngineLoop.h"

EngineLoop GEngineLoop;

bool IsEngineExitRequested = false;
int LoopTestNum = 10;

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

    // 栈对象 确保清除操作一定会执行
    struct EngineLoopCleanupGuard{
        ~EngineLoopCleanupGuard() {
            EngineExit();
        }
    } CleanupGuard;

    {
        ErrorLevel = EngineInit();
    }

    int LoopTime = 0;
    while(!IsEngineExitRequested) {
        EngineTick();
        LoopTime++;
        if (LoopTime >= LoopTestNum) {
            IsEngineExitRequested = true;
        }
    }

    return 0;
}