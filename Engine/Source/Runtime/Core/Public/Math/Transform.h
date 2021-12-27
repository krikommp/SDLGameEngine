#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include <string>

#include "Vector.h"

struct Transform
{
public:
    Vector Translation;

public:
    std::string ToString();
};

#endif //  _TRANSFORM_H_