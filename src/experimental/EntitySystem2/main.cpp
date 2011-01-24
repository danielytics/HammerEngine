
#include "HammerEntitySystem.h"
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"
#include "EventDispatcher.h"

#include "Position.h"
#include "Movement.h"
#include "Observed.h"
#include "Collidable.h"

#include "DebugTools.h"

#include "AlignedMemoryPool.h"
#include <iostream>

EventDispatcher* EventDispatcher::dispatcher = 0;

#define debug std::cout << "On line " << __LINE__ << "\n";

int main(int argc, char *argv[])
{
    try {
        HammerEntitySystem hammerEngine;

        EventDispatcher::implEventDispatcher(hammerEngine.getEventDispatcher());

        TraitBuilder traitBuilder(&hammerEngine);
        BehaviorBuilder behaviorBuilder(&hammerEngine);

        PositionUtils::install(&traitBuilder, &behaviorBuilder);
        MovementUtils::install(&traitBuilder, &behaviorBuilder);
        ObservedUtils::install(&traitBuilder, &behaviorBuilder);
        CollidableUtils::install(&traitBuilder, &behaviorBuilder);

        {
            Entity player = hammerEngine.createEntity()
                                .addTrait<Position>()
                                .addTrait<Movement>()
                                .addTrait<Observed>();
            PositionUtils::init(player.trait<Position>(), 0.0f, 0.0f, 1.0f);
            MovementUtils::init(player.trait<Movement>(), 0.0f, 1.0f, 0.0f);
            player.setState(Running);
        }

        {
            Entity enemy = hammerEngine.createEntity()
                                .addTrait<Position>()
                                .addTrait<Movement>()
                                .addTrait<Collidable>();
//                                .addTrait<Observed>();
            PositionUtils::init(enemy.trait<Position>(), 0.0f, 0.0f, 2.0f);
            MovementUtils::init(enemy.trait<Movement>(), 1.0f, 0.0f, 0.0f);
            enemy.setState(Running);
        }
        {
            Entity enemy = hammerEngine.createEntity()
                                .addTrait<Position>()
                                .addTrait<Movement>();
//                                .addTrait<Observed>();
            PositionUtils::init(enemy.trait<Position>(), 0.0f, 0.0f, 3.0f);
            MovementUtils::init(enemy.trait<Movement>(), 1.0f, 0.0f, 0.0f);
            enemy.setState(Running);
        }

        unsigned int last=0;
        for (unsigned int i = 0; i < 50000; i++) {
            Entity unobserved = hammerEngine.createEntity()
                                    .addTrait<Position>()
                                    .addTrait<Movement>();
            PositionUtils::init(unobserved.trait<Position>(), 0.0f, 0.0f, 0.0f);
            MovementUtils::init(unobserved.trait<Movement>(), 0.0f, 0.0f, -1.0f);
            unobserved.setState(Running);
            last = unobserved.id;
        }

        // Update the system a few times.
        for (unsigned int i = 0; i < 5; ++i)
        {
            hammerEngine.updateBehavior();
        }

        std::cout << "Last unobserved entity: " << Entity(hammerEngine, last).trait<Position>() << "\n";
    }
    catch (std::runtime_error& error)
    {
        std::cout << "Unhandled runtime error detected, program terminating:" << error.what() << "\n";
    }
    catch (std::logic_error& error)
    {
        std::cout << "Logic error detected, program terminating:\n" << error.what() << "\n";
    }
    catch (std::exception& error)
    {
        std::cout << "Fatal exception detected, program terminating:\n" << error.what() << "\n";
    }

    return 0;
}
