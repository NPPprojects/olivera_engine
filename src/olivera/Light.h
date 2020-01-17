#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
{
  class Entity;
  class ShaderProgram;
  /**
  *Component derived class to set up lighting for object
  */
  class Light :public Component
  {
  public:
    void onTick();
    void onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther);

  private:

    std::weak_ptr<ShaderProgram> shader;
    std::vector<std::weak_ptr<Entity>> entitiesOther;
    
    
  };



}