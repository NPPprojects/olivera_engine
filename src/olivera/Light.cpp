#include "Light.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
namespace olivera
{
 
  void Light::onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther)
  {
    for (int i = 0; i < _entitiesOther.size(); i++)
    {
      entitiesOther.push_back(_entitiesOther.at(i));
    }

    glm::vec3 lightColor = glm::vec3(10.0f, 10.0f, 10.0f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

    shader = getCore()->getResources()->load<ShaderProgram>(_shader);
    shader.lock()->useShader();

    for (unsigned int i = 0; i <= entitiesOther.size(); ++i)
    {


     // shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].position", glm::vec3(0.0f, 0.0f, 0.0f));
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].ambient", ambientColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].diffuse", diffuseColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].specular", 10.0f, 10.0f, 10.0f);

      //Point light attenuation
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].linear", 0.045f);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.075f);
    };

  }
  void Light::onTick()
  {
    shader.lock()->useShader();
    for (unsigned int i = 0; i < entitiesOther.size(); ++i)
    {
    shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].position", entitiesOther.at(i).lock()->getComponent<Transform>()->getPosition());
    };
  }

}