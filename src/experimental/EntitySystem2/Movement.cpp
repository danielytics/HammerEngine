
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"

#include "Movement.h"
#include "Position.h"

void MovementUtils::init (Movement& output, const float x, const float y, const float z)
{
    output.x = x;
    output.y = y;
    output.z = z;
}

void do_move (const Position& position, const Movement& movement, Position& out)
{
    PositionUtils::init(out,
                        position.x + movement.x,
                        position.y + movement.y,
                        position.z + movement.z);
}

void MovementUtils::install (TraitBuilder* tb, BehaviorBuilder* bb)
{
    tb->registerTrait<MemoryFeatures::DefaultDynamicPoolFeatures, Movement>();
    bb->registerBehavior(do_move);
}

std::ostream& operator<< (std::ostream& os, const Movement& input)
{
    os << "<Movement: " << input.x << ", "
                        << input.y << ", "
                        << input.z << ">";
    return os;
}

