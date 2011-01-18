
#include <HammerEngine/Module.h>

void do_input ();
void do_playerInput ();
void do_ai ();
void do_objects ();
void do_physics ();

void hammerEngineInit (Hammer::Engine* engine)
{
    // Input
    engine->addInputFiler(do_input);

    // AI
    engine->addActorController(Player, do_playerInput);
    engine->addActorController(Character, do_ai);
    engine->addActorController(DynamicObject, do_objects);

    // Physics
    engine->addPhysicsHandler(do_physics);
}

//////////

void do_input ()
{

}

void do_playerInput ()
{

}

void do_ai ()
{

}

void do_objects ()
{

}

void do_physics ()
{

}
