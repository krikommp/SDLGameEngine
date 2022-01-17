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
#include <chrono>
#include <functional>
#include <vector>
#include <exception>
#include <random>
#include <thread>

#include <SDL.h>
#include <fmt/format.h>

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

template <typename Signature>
struct Listener;

template <typename RET, typename... ArgTypes>
struct Listener<RET(ArgTypes...)> {
    using Functor = std::function<void(ArgTypes...)>;

public:
    void Register(Functor&& Func) {
        Functions.push_back(Func);
    }

    void NotifyAll(ArgTypes... Args) {
        for(const auto& Func : Functions) {
            Func(Args...);
        }
    }

private:
    std::vector<Functor> Functions;
};
#endif //SDLGAMEENGINE_SORTWAREPCH_H
