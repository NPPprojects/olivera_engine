#include "Materials.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Core.h"
namespace olivera 
{

  void Materials::onInitialise(std::string _shader)
  {
    shader = getCore()->getResources()->load<ShaderProgram>(_shader);
    shader->useShader();
    shader->setFloat("material.shininess", 32.0f);
    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
  }

}