/*
#include <falcon/engine.h>
#include <iostream>

class AppFalcon
{
public:
   AppFalcon();
   ~AppFalcon();
   int embed( const char *script_name );
};

AppFalcon::AppFalcon()
{
   Falcon::Engine::Init();
}

AppFalcon::~AppFalcon()
{
   Falcon::Engine::Shutdown();
}

// This is the routine that embeds falcon
int AppFalcon::embed( const char *script_name )
{
   // first of all, we need a module loader to load the script.
   // The parameter is the search path for where to search our module
    std::cout << "On line " << __LINE__ << "\n";
   Falcon::ModuleLoader theLoader("game/");

   // As we want to use standard Falcon installation,
   // tell the loader that is safe to search module in system path
   std::cout << "On line " << __LINE__ << "\n";
   theLoader.addFalconPath();

   // Allow the script to load iteratively other resources it may need.
   std::cout << "On line " << __LINE__ << "\n";
   Falcon::Runtime rt( &theLoader );
   std::cout << "On line " << __LINE__ << "\n";
   try
   {
       rt.loadFile( script_name );
   } catch (...)
   {
       std::cout << "Caught exception\n";
       return 2;
   }

   // We are ready to go. Let's create our VM and link in minimal stuff
   std::cout << "On line " << __LINE__ << "\n";
   Falcon::VMachineWrapper vm;

   std::cout << "On line " << __LINE__ << "\n";
   vm->link( Falcon::core_module_init() );  // add the core module

   // try to link our module and its dependencies.
   // -- It may fail if there are some undefined symbols
   std::cout << "On line " << __LINE__ << "\n";
   vm->link( &rt );

   // we're ready to go. Still, we may fail if the script has not a main routine.
   std::cout << "On line " << __LINE__ << "\n";
   vm->launch();

   return 0;
}


int scriptmain(int argc, char *argv[])
{
    AppFalcon myApp;

    char* script_name = "fail.fal";

    try {
       return myApp.embed(script_name);
    }
    catch( Falcon::Error* err )
    {
       // For now, let's use a simple STD:: provided stream.
       Falcon::AutoCString edesc( err->toString() );
       std::cerr << edesc.c_str() << std::endl;
       err->decref();
       return 1;
    }
}
*/
