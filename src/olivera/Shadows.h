#include <memory>
#include <vector>
#include <string>
#include "Component.h"
#include <glm/glm.hpp>

namespace olivera 
{
  class ShaderProgram;

  class ResourceManager;

  class Entity;

  /************************************************************
  @brief Component derived class to set up shadows for object

  *************************************************************/
  class Shadows :public Component
  {
    public:
    
      /************************************************************
      @brief Add depth Shader, and provide method to obtrain 
      all pos of lightsources.

      *************************************************************/
        void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther, std::shared_ptr<ResourceManager> _resourceManager);

      /************************************************************
      @brief configure DepthShader and set relevenat uniform values
      
      *************************************************************/
        void onTick();



    private: 
      /********************************************************************************************************************/
      std::weak_ptr<ShaderProgram> shader;                                        //!<Weak pointer to shader

      std::vector<std::weak_ptr<Entity>> entitiesOther;


      std::weak_ptr<ResourceManager> shadowResources;

      /************************************************************************************************************************/
  };
}
