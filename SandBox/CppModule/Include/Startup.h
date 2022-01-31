//
// Created by kriko on 2022/1/1.
//

#ifndef SDLGAMEENGINE_STARTUP_H
#define SDLGAMEENGINE_STARTUP_H

#include <string>

template<typename ...> struct TypeList;

template<typename Head, typename ...Tail> struct TypeList<Head, Tail...>{
    using head = Head;
    using tail = TypeList<Tail...>;
};

template<typename TList> struct Length;

template<typename... Types> struct Length<TypeList<Types...>> {
    static constexpr int Value = sizeof...(Types);
};

template<typename TList, unsigned int i> struct IndexAt;

template<typename Head, typename... Tail> struct IndexAt<TypeList<Head, Tail...>, 0> {
    using Value = Head;
};

template<typename Head, typename... Tail, unsigned int i> struct IndexAt<TypeList<Head, Tail...>, i> {
    using Value = typename IndexAt<TypeList<Tail...>, i - 1>::Value;
};

const std::string RootPath(ROOTPATH);

#endif //SDLGAMEENGINE_STARTUP_H
