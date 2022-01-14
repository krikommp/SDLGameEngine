//
// Created by chenyifei on 2022/1/13.
//

#ifndef SDLGAMEENGINE_SORTWAREPCH_H
#define SDLGAMEENGINE_SORTWAREPCH_H

#include <cstdlib>
#include <ostream>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cassert>
#include <SDL.h>

using uint32 = unsigned int;
using uint8 = uint8_t;

class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    NonCopyable(const NonCopyable&) = delete;
    const NonCopyable& operator=(const NonCopyable&) = delete;
};


#endif //SDLGAMEENGINE_SORTWAREPCH_H
