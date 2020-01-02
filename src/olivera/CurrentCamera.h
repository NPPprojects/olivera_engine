#include <memory>
#include <vector>
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
  class Core;
  class Camera;

  class CurrentCamera : public Component
  {
  public:
    glm::mat4 getProjection();
    void setProjection();
    glm::mat4 getView();
    void setView();

  private:
    glm::mat4 view;
    glm::mat4 projection;
  
    
    std::shared_ptr<Camera> camera;
  };
}