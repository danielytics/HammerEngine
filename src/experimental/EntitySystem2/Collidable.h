#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <iostream>

#include "Trait.h"
#include "Position.h"

class TraitBuilder;
class BehaviorBuilder;

struct Collidable
{

};

struct CollisionCheckEvent
{
    Position start;
    Position end;
};

namespace CollidableUtils
{
    void install (TraitBuilder* tb, BehaviorBuilder* bb);
};

std::ostream& operator<< (std::ostream& os, const Collidable& input);

#endif // COLLIDABLE_H
