
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"

#include "Observed.h"
#include "Position.h"
#include "Movement.h"

void do_observe (const ReadOnlyEntity& entity, const Observed& observed, const Movement& movement, const Position& position)
{
    std::cout << "Observing "
              << entity.id
              << "\t (" << &position << ") "
              << position << " " << movement << "\n";
}

void ObservedUtils::install (TraitBuilder* tb, BehaviorBuilder* bb)
{
    tb->registerTrait<MemoryFeatures::DefaultDynamicPoolFeatures, Observed>();
    bb->registerBehavior(do_observe);
}

std::ostream& operator<< (std::ostream& os, const Observed& input)
{
    os << "<Observed>";
    return os;
}
