#ifndef OBSERVED_H
#define OBSERVED_H

#include <iostream>

#include "Trait.h"

class TraitBuilder;
class BehaviorBuilder;

struct Observed
{

};

namespace ObservedUtils
{
    void install (TraitBuilder* tb, BehaviorBuilder* bb);
};

std::ostream& operator<< (std::ostream& os, const Observed& input);

#endif // OBSERVED_H
