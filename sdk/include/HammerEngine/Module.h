#ifndef HAMMER_ENGINE_MODULE__H_
#define HAMMER_ENGINE_MODULE__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

namespace Hammer
{

//    typedef void (*InputFilterCallback) ();
//    typedef void (*ActorControllerCallback) ();
//    typedef void (*PhysicsHandlerCallback) ();

//    enum ControllerType
//    {
//        Player        = 1,
//        Character,
//        StaticObject,
//        DynamicObject,
//        User // User controller types should be defined as User+0, User+1, etc
//    };

//    class Renderer;

//    class Engine
//    {
//    public:
//        virtual ~Engine () {}

//        /**
//          * Specify a custom render.
//          * Not yet supported.
//          */
//        virtual void setRenderer        (Renderer*)=0;

//        /**
//          * Add an Input Filter.
//          * Input filters take input events and map them to game events (eg, commands for Actors).
//          * At least one input filter should exist in a game. Multiple input filters are supported
//          * and can be used to, eg, support multiple input device types (eg, keyboard and joystick).
//          */
//        virtual void addInputFiler      (InputFilterCallback)=0;

//        /**
//          * Add an Actor controller.
//          * Contoller callbacks are used to implement the logic for the Actors behaviour.
//          * Controllers can be added for a number of different types of Actors:
//          *    - Player             This is the Actor(s) controlled by the player
//          *    - Character          These Actors are AI Ncharacters.
//          *    - StaticObject       Actors which are generally sdtatic, but may sometimes move, eg doors.
//          *    - DynamicObject      Actors which are not characters, but move, eg rocks that can move.
//          */
//        virtual void addActorController (ControllerType, ActorControllerCallback)=0;

//        /**
//          * Add callback to perform physics updates.
//          * Should take each object and apply physics to it, detect collisions and handle collision response.
//          */
//        virtual void addPhysicsHandler  (PhysicsHandlerCallback)=0;
//    };

#include <HammerEngine/EntitySystem/EntitySystem.h>
#include <HammerEngine/EntitySystem/BehaviorFunctor.h>

    class Engine
    {
    public:
        virtual ~Engine () {}

        virtual EntitySystem* entitySystem ()=0;
    };

    /**
      * BehaviorBuilder
      *
      * Convenience helper class to simplify creating behaviors.
      *
      * Eg:
      *    void do_position_behavior   (const Position& in, Position& out);
      *    void do_renderable_behavior (const Renderable& in1, const Position& in2, const Animation& in3, const Orientation& in4, Renderable& out);
      *    ...
      *    BehaviorBuilder builder(engine);
      *    builder.registerBehavior<Position>(do_position_behavior);
      *    builder.registerBehavior<Renderable, Position, Animation, Orientation>(do_renderable_behavior);
      */
    class BehaviorBuilder
    {
    private:
        const EntitySystem* entitySystem;
    public:
        BehaviorBuilder (Engine* ngin) : entitySystem(ngin->entitySystem()) {}
        ~BehaviorBuilder () {}

        // One input trait
        template <class T1>
        void registerBehavior(void (*func) (const T1&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1>(func));}

        // Two input traits
        template <class T1, class T2>
        void registerBehavior(void (*func) (const T1&, const T2&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2>(func));}

        // Three input traits
        template <class T1, class T2, class T3>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3>(func));}

        // Fourinput traits
        template <class T1, class T2, class T3, class T4>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4>(func));}

        // Five input traits
        template <class T1, class T2, class T3, class T4, class T5>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4, T5>(func));}

        // Six input traits
        template <class T1, class T2, class T3, class T4, class T5, class T6>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6>(func));}

        // Seven input traits
        template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7>(func));}

        // Eight input traits
        template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7, T8>(func));}

        // Nine input traits
        template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
        void registerBehavior(void (*func) (const T1&, const T2&, const T3&, const T4&, const T5&, const T6&, const T7&, const T8&, const T9&, T1&))
        {entitySystem->registerBehavior(T1::id, BehaviorFunctorWrapper<T1, T2, T3, T4, T5, T6, T7, T8, T9>(func));}
    };

} // Hammer


/**
  * Exported initialization function.
  * Each module must implement this function.
  * This function is used to pass the modules callback functions to the engine.
  */
extern "C" void hammerEngineInit (Hammer::Engine*);

#endif
