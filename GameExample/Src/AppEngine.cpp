//
// Created by chenyifei on 2022/1/10.

#include "MyAppEngine.h"

int main(int argc, char *argv[]) {
    Chapter03::PerspectiveModelApp GApp;
    // Chapter02::DrawTriangleApp GApp;
    GApp.Construct();
    GApp.Start();

    return EXIT_SUCCESS;
}