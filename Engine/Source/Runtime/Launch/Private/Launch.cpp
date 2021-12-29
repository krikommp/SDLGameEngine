//
// Created by chenyifei on 2021/12/29.
//

#include "LaunchEngineLoop.h"

EngineLoop GEngineLoop;

/**
 * 预先初始化流程
 * 包括一些子系统的初始化
 * @return
 */
int EnginePreInit() {
    int ErrorLevel = GEngineLoop.PreInit();
    return ErrorLevel;
}


int GuardedMain() {

}