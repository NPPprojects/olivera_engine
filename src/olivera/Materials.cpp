#include "Materials.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Core.h"
namespace olivera 
{

  void Materials::onInitialise(std::string _shader)
  {
    shader = getCore()->getResources()->load<ShaderProgram>(_shader);
    shader.lock()->useShader();
    shader.lock()->setFloat("material.shininess", 32.0f);
    shader.lock()->setInt("material.diffuse", 0);
    shader.lock()->setInt("material.specular", 1);
  }

}