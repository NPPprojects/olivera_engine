#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>

/********************************************************************
CHANGE FOR LOOPS
*********************************************************************/

namespace olivera
{
  class Mouse;

  class Entity;

  class Keyboard;

  class Environment;

  class ShaderProgram;

  class CameraContext;

  class PostProcessing;

  class ResourceManager;

  /**********************************************
  @brief Engine is contained within this class
  
  ***********************************************/
  class Core
  {
    public:

      /**********************************************************
      @brief Initialisation function that will add all entities
      to the tick rate and display them.                       
                                                             
      @param int WindowWidth                                   
      @param int WindowHeight                                  
                                                             
      @return the core set up                                  
      ***********************************************************/
        static std::shared_ptr<Core> initialise(int _windowWidth, int _windowHeight);
    
      /*******************************************
      @brief Adds an entity to the entity vector.

      @return pointer to the entity.

      ********************************************/
        std::shared_ptr<Entity> addEntity();    
    
      /******************************************************
      @brief Get Entities with a specific component attached.
                                                           
      *******************************************************/
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

      /******************************************************
        @brief Get the Keyboard object in core.
     
        *Contains methods for accessing the current keys that
        are pressed or held.

        @return weak pointer to the keyboard object in core.

      *******************************************************/
        std::shared_ptr<Keyboard> getKeyboard(); 

      /*******************************************************
      @brief Get the Environment object in core.

      *Contains methods for accessing and modifying deltaTime

      @return weak pointer to the environment object in core.
      ********************************************************/
        std::shared_ptr<Environment> getEnvironment();  

      /**************************************************
      @brief Get access to the camera list in core.

      @return weak pointer to the cameraList in core.
      ***************************************************/
        std::shared_ptr<CameraContext> getCameraList();  

      /******************************************
      @brief Get the list of current resources.
    
      @return a weak pointer to a resource list 
      in core.

      *******************************************/
	      std::shared_ptr<ResourceManager> getResources(); 
    

      /***********************************
      @brief Get access to mouse object.

      @return mouse object inside core.

      ************************************/
        std::shared_ptr<Mouse> getMouse();     
    
      /*****************************************************************************************
      @brief Core while loop.

      *Record mouse and keyboard inputs and sends them to their respective objects.
      All entites go through their tick functions, and then through their dispay functions. 
      A viewport is set up using the user inputed window width and height. 
      Further viewports are created for user defined cameras.

      ******************************************************************************************/
        void start();
    
      /****************************
      @brief Stops the main loop.
    
      *****************************/
       void stop();
    
      /*****************************
      @brief Get the screen width.

      @return screenWidth

      ******************************/
        int getScreenWidth();

      /******************************
      @brief get the screen height.

      @return screenHeight

      *******************************/
        int getScreenHeight();

    private:
    /************************************************************************************************************************/
    
      SDL_Window *window;                                                                                  //!<Window context
    
    
      ALCdevice* device;                                                                                            //!<Audio
      ALCcontext* context;                                                                                          //!<Audio
    
    
      std::vector<std::shared_ptr<Entity>> entities;                                               //!<Vector of all entities
    
    
      std::weak_ptr<Core> self;                                                             //!<Weak pointer to self refrence 
    
      std::shared_ptr<CameraContext> cameraContext = std::make_shared<CameraContext>();                     //!<Store Cameras
	    std::shared_ptr<ResourceManager> resources = std::make_shared<ResourceManager>();               //!<Store all Resources 
      std::shared_ptr<Environment> environment = std::make_shared<Environment>();                //!<Store environment object 
      std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>();                           //!<Stores keyboard inputs
      std::shared_ptr<Mouse> mouse = std::make_shared <Mouse>();                                     //!< Stores Mouse Inputs
    
      int windowWidth;                                                                               //</ Stores window width
      int windowHeight;                                                                              //</Stores window height
    
      bool running;                                                                              //</If true main loop starts
    
    /************************************************************************************************************************/
  };
}
