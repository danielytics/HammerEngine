#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>

#include "Trait.h"

class TraitBuilder;
class BehaviorBuilder;

struct Movement
{
    float x;
    float y;
    float z;

    Movement& operator= (const Movement& input)
    {
        x = input.x;
        y = input.y;
        z = input.z;
        return *this;
    }
};

namespace MovementUtils
{
    void init (Movement& output, const float x, const float y, const float z);

    void install (TraitBuilder* tb, BehaviorBuilder* bb);
};

std::ostream& operator<< (std::ostream& os, const Movement& input);

#endif // MOVEMENT_H
