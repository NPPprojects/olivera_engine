#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>


namespace olivera
{
  class Entity;
  class Keyboard;

  class Mouse;
  class Environment;

  class CurrentCamera;
  
  class PostProcessing;
  class VertexBuffer;

  class ShaderProgram;
  class ResourceManager;
  class Core
  {

  public:
    static std::shared_ptr<Core> initialise();    //Initialisation function that will add all entities to the tick rate and display them
    std::shared_ptr<Entity> addEntity();      //Adds an entity to the entity vector

	///Super Lost
    template<typename T>
    void GetEntities(std::vector<std::shared_ptr<Entity>>& _list)
    {
      for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
      {
        bool found = (*it)->checkForComponent<T>();

        if (found)
        {
          _list.push_back((*it));
        }
      }
    }

    std::shared_ptr<Keyboard> getKeyboard();  //Get the Keyboard so input class has access to keys that have been pressed;
    std::shared_ptr<Environment> getEnvironment();  //get envioronment time
    std::shared_ptr<CurrentCamera> getCurrentCamera();  //get current camera context to pass view and projection matrix values
	  std::shared_ptr<ResourceManager> getResources(); //Get Resources list
    void setPostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh);
    std::shared_ptr<Mouse> getMouse();           //Get Mouse user inputs
    void start();
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
    //Current Camera context
    std::shared_ptr<CurrentCamera> cameraContext = std::make_shared<CurrentCamera>();
    //Environment
    std::shared_ptr<Environment> environment = std::make_shared<Environment>();
    //Mouse coordinate and inputs
    std::shared_ptr<Mouse> mouse = std::make_shared <Mouse>();
    //Post Processing
    std::shared_ptr<PostProcessing> postProcessing;
    //Resources
	std::shared_ptr<ResourceManager> resources = std::make_shared<ResourceManager>();
   
  
  };
}
