
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"

#include "Position.h"

void PositionUtils::init (Position& output, const float x, const float y, const float z)
{
    output.x = x;
    output.y = y;
    output.z = z;
}

void PositionUtils::install (TraitBuilder* tb, BehaviorBuilder* bb)
{
    tb->registerTrait<MemoryFeatures::DefaultDynamicPoolFeatures, Position>();
}

std::ostream& operator<< (std::ostream& os, const Position& input)
{
    os << "<Position: " << input.x << ", "
                        << input.y << ", "
                        << input.z << ">";
    return os;
}
