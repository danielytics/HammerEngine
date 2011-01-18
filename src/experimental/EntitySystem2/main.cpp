
#include "HammerEntitySystem.h"
#include "TraitBuilder.h"
#include "BehaviorBuilder.h"

#include "Position.h"
#include "Movement.h"
#include "Observed.h"

#include "DebugTools.h"

#include "AlignedMemoryPool.h"
#include <iostream>

#define debug std::cout << "On line " << __LINE__ << "\n";

int main(int argc, char *argv[])
{
    try {
        HammerEntitySystem hammerEngine;

        TraitBuilder traitBuilder(&hammerEngine);
        BehaviorBuilder behaviorBuilder(&hammerEngine);

        PositionUtils::install(&traitBuilder, &behaviorBuilder);
        MovementUtils::install(&traitBuilder, &behaviorBuilder);
        ObservedUtils::install(&traitBuilder, &behaviorBuilder);

        {
            Entity player = hammerEngine.createEntity()
                                .addTrait<Position>()
                                .addTrait<Movement>()
                                .addTrait<Observed>();
            PositionUtils::init(player.trait<Position>(), 0.0f, 0.0f, 1.0f);
            MovementUtils::init(player.trait<Movement>(), 0.0f, 1.0f, 0.0f);
            player.setState(Running);
            std::cout << player.id << "\n";
        }

        {
            Entity enemy = hammerEngine.createEntity()
                                .addTrait<Position>()
                                .addTrait<Movement>()
                                .addTrait<Observed>();
            PositionUtils::init(enemy.trait<Position>(), 0.0f, 0.0f, 2.0f);
            MovementUtils::init(enemy.trait<Movement>(), 1.0f, 0.0f, 0.0f);
            enemy.setState(Running);
            std::cout << enemy.id << "\n";
        }
//        {
//            Entity enemy = hammerEngine.createEntity()
//                                .addTrait<Position>()
//                                .addTrait<Movement>()
//                                .addTrait<Observed>();
//            PositionUtils::init(enemy.trait<Position>(), 0.0f, 0.0f, 3.0f);
//            MovementUtils::init(enemy.trait<Movement>(), 1.0f, 0.0f, 0.0f);
//            enemy.setState(Running);
//        }

//        unsigned int last=0;
//        for (unsigned int i = 0; i < 10; i++) {
//            Entity unobserved = hammerEngine.createEntity()
//                                    .addTrait<Position>()
//                                    .addTrait<Movement>();
////                                    .addTrait<Observed>()
//            unobserved.trait<Movement>().x = 1.0f;
//            unobserved.setState(Running);
//            last = unobserved.id;
//        }

        // Update the system a few times.
        for (unsigned int i = 0; i < 5; ++i)
        {
            hammerEngine.updateBehavior();
        }

//        std::cout << "Last unobserved entity: " << Entity(hammerEngine, last).trait<Position>() << "\n";
    }
    catch (std::exception& error)
    {
        std::cout << "Fatal exception caught: " << error.what() << "\n";
    }

    return 0;
}
