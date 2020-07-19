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


  class Shadows :public Component
  {
  public:

    void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther, std::shared_ptr<ResourceManager> _resourceManager);

    void onTick();

    void onDisplay();

    std::weak_ptr<ShaderProgram> shader;                                        //!<Weak pointer to shader

    std::vector<std::weak_ptr<Entity>> entitiesOther;
  };
}
