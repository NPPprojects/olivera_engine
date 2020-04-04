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


  class ShaderProgram;
  class ResourceManager;

  /**
  *Camera context held within the engine, users have to write the camera functionality themselves and use this class to set the projection and view
  */
  class Core
  {

  public:
    /**
    *\Initialisation function that will add all entities to the tick rate and display them
    */
    static std::shared_ptr<Core> initialise(int _windowWidth, int _windowHeight);
    
    /**
    *\Adds an entity to the entity vector
    */
    std::shared_ptr<Entity> addEntity();    

  /**
  *\Get Entities with a specific component attached
  */
    template<typename T>
    void GetEntities(std::vector<std::shared_ptr<Entity>>& _entities)
    {
      for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
      {
        bool found = (*it)->checkForComponent<T>();

        if (found)
        {
          _entities.push_back((*it));
        }
      }
    }
    /**
    *\Get the Keyboard so input class has access to keys that have been pressed;
    */
    std::shared_ptr<Keyboard> getKeyboard(); 

    /**
    *\get envioronment time
    */
    std::shared_ptr<Environment> getEnvironment();  

    /**
    *\get current camera context to pass view and projection matrix values
    */
    std::shared_ptr<CurrentCamera> getCurrentCamera();  

    /**
    *\Get Resources list
    */
	  std::shared_ptr<ResourceManager> getResources(); 
    
    /**
    *\set PostProcessing shader
    */
    void setPostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh, int _width, int _height);

    /**
    *\Get Mouse user inputs;
    */
    std::shared_ptr<Mouse> getMouse();     
    
    /**
    *\Core while loop;
    */
    void start(int _viewportWidth, int _viewportHeight);
    
    /**
    *\Shut down engine
    */
    void stop();
    
    /**
    *\Set window parameters
    */

  private:

    std::vector<std::shared_ptr<Entity>> entities;///<Vector of all entities
    std::weak_ptr<Core> self;///<Weak pointer to self refrence 
    bool running;

    
    SDL_Window *window; ///<Window SDL_Context

    std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>();///<Keyboard Inputs
    
    ALCdevice* device;///<Audio
 
    ALCcontext* context;///<Audio
 
    std::shared_ptr<CurrentCamera> cameraContext = std::make_shared<CurrentCamera>(); ///<Current Camera context pointer
   
    std::shared_ptr<Environment> environment = std::make_shared<Environment>();///<Pointer to environment
    //Mouse coordinate and inputs
    std::shared_ptr<Mouse> mouse = std::make_shared <Mouse>();///< Pointer to mouse
    //Post Processing
    std::shared_ptr<PostProcessing> postProcessing;///<Pointer to postProcessing 
    //Resources
	  std::shared_ptr<ResourceManager> resources = std::make_shared<ResourceManager>();///<pointer to Resources
   

  };
}
