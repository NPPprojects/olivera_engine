#include <memory>
#include <vector>
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
  class Core;
  class Camera;

  class CurrentCamera 
  {
  public:
    glm::mat4 getProjection();

    glm::mat4 getView();

  private:
    glm::mat4 view;
    glm::mat4 projection;
  
    

  };
}