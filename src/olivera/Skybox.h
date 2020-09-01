#include "Component.h"

#include <vector>
#include <string>



namespace olivera
{
  class VertexArray;

  class CurrentCamera;

  class ShaderProgram;

  class ResourceManager;

  class Texture;

  class Skybox : public Component
  {
  public:
   
    void onInitialise(std::vector<std::string> _textures);

    void onDisplay();

    int loadCubemap(); 

    private:
    /************************************************************************************************************/

    std::shared_ptr<ResourceManager> resources;               //!< Storage for all resources needed for a skybox
    
    std::vector<std::weak_ptr<Texture>> faces;
    
    std::weak_ptr<Core> core;
    std::weak_ptr<Entity> entitySelf;                        //!< Weak pointer to entity this is a component off
    std::weak_ptr<CurrentCamera> cameraContext;
    
    std::weak_ptr<VertexArray> mesh;
    std::weak_ptr<ShaderProgram> shader;
    
    unsigned int cubemapTexture;

    /************************************************************************************************************/
  };

}