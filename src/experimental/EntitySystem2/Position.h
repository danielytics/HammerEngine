#ifndef POSITION_H
#define POSITION_H

#include <iostream>

#include "Trait.h"

class TraitBuilder;
class BehaviorBuilder;

struct Position
{
    float x;
    float y;
    float z;
    float padding[1];

    Position& operator= (const Position& input)
    {
        x = input.x;
        y = input.y;
        z = input.z;
        return *this;
    }
};

namespace PositionUtils
{
    void init (Position& output, const float x, const float y, const float z);

    void install (TraitBuilder* tb, BehaviorBuilder* bb);
};

std::ostream& operator<< (std::ostream& os, const Position& input);

#endif // POSITION_H
