#include "Materials.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Core.h"
namespace olivera 
{

  void Materials::onInitialise(std::string _shader)
  {
    shader = getCore()->getResources()->load<ShaderProgram>(_shader);
    modifications = false;
    shader.lock()->useShader();
    shader.lock()->setFloat("material.shininess", 0.0f);
    shader.lock()->setInt("material.diffuse", 0);
    shader.lock()->setInt("material.specular", 0);
  }

  void Materials::onTick()
  {
    if (modifications == true)
    {
      shader.lock()->useShader();
      shader.lock()->setFloat("material.shininess", material.shininess);
      shader.lock()->setInt("material.diffuse", material.diffuse);
      shader.lock()->setInt("material.specular", material.specular);
    }

  }
  void Materials::setMaterial(float _shininess, int _diffuse, int _specular)
  {
    modifications = true;
    material.shininess = _shininess;
    material.diffuse = _diffuse;
    material.specular = _specular;
  }

  void Materials::setDefaultMaterial(float _shininess, int _diffuse, int _specular)
  {
    material.shininess = _shininess;
    material.diffuse = _diffuse;
    material.specular = _specular;
    shader.lock()->useShader();
    shader.lock()->setFloat("material.shininess", material.shininess);
    shader.lock()->setInt("material.diffuse", material.diffuse);
    shader.lock()->setInt("material.specular", material.specular);
  }
  
}