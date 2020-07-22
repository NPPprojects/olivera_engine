
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Component.h"
namespace olivera
{

  class ShadowsFBO
  {
  public:

    void configureFBO();

    void createCubemapTransformationMatrices(glm::vec3 _lightPos);

    void bindFBO(std::shared_ptr<ResourceManager> _resourceManager, std::string _shader);

    float getNearPlane();

    float getFarPlane();

    int getDepthCubemap();


  private:
    const unsigned int resolution = 2048;
    const float nearPlane = 1.0f;
    const float farPlane = 100.f;
    unsigned int FBO;
    unsigned int depthCubemap;
    std::vector<glm::mat4> shadowTransforms;

  };



}

