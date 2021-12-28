#include <fmt/format.h>

#include "Math/Transform.h"

std::string Transform::ToString()
{
    std::string Result = fmt::format("Translation = [{}, {}, {}]", this->Translation.X, this->Translation.Y, this->Translation.Z);
    return Result;
}