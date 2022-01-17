//
// Created by kriko on 2022/1/16.
//

#ifndef SDLGAMEENGINE_THREADPOOL_H
#define SDLGAMEENGINE_THREADPOOL_H

#include "SortWarePCH.h"

template <typename T>
class ThreadPool {
public:
    void Init(uint32 InThreadNum = 8, uint32 InRequiresNum = 10000);

private:
    static void* Work(void* Args);
private:
    uint32 ThreadNum;
    uint32 MaxRequiresNum;

    std::vector<std::thread> Threads;
};

template<typename T>
void ThreadPool<T>::Init(uint32 InThreadNum, uint32 InRequiresNum) {
    if (InThreadNum <= 0 || InRequiresNum <= 0)
        throw std::exception();
    ThreadNum = InThreadNum;
    MaxRequiresNum = InRequiresNum;
    Threads.resize(InThreadNum);
    for (uint32 I = 0; I < ThreadNum; ++I) {
        Threads[I] = std::thread(Work, this);
        Threads[I].detach();
    }
}

template<typename T>
void *ThreadPool<T>::Work(void *Args) {
    ThreadPool* Pool = (ThreadPool*)Args;
    if (Pool != nullptr)
        std::cout << "not null" << std::endl;
    std::cout << "In Work Func" << std::endl;
    return nullptr;
}

#endif //SDLGAMEENGINE_THREADPOOL_H
