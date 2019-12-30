#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>


namespace olivera
{
  class Entity;
  class Keyboard;

  class Core
  {

  public:
    static std::shared_ptr<Core> initialise();    //Initialisation function that will add all entities to the tick rate and display them
    std::shared_ptr<Entity> addEntity();      //Adds an entity to the entity vector

    std::shared_ptr<Keyboard> getKeyboard();
    void start(SDL_Event &event);
    void stop();


  private:

    std::vector<std::shared_ptr<Entity>> entities;      //Vector of all entities
    std::weak_ptr<Core> self;                   //Weak pointer to self refrence 
    bool running;

    //Window SDL_Context
    SDL_Window *window;
    //Keyboard Inputs
    std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>();
    //Audio
    ALCdevice* device;
    ALCcontext* context;
    //Matricies for screen coordinates
    
    
  };
}
