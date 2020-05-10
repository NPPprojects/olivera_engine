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

    lightColor = glm::vec3(10.0f, 10.0f, 10.0f);
    diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
    ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    specularColor = glm::vec3(10.f, 10.f, 10.f);

    attenuationValues.constant = 1.0f;
    attenuationValues.linear = 0.045f;
    attenuationValues.quadratic = 0.0075f;


    shader = getCore()->getResources()->load<ShaderProgram>(_shader);
    shader.lock()->useShader();

  }
 
  void Light::onTick()
  {
    shader.lock()->useShader();
    for (unsigned int i = 0; i < entitiesOther.size(); ++i)
    {
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].ambient", ambientColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].diffuse", diffuseColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].specular", specularColor);

      //Point light attenuation
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].constant", attenuationValues.constant);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].linear", attenuationValues.linear);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].quadratic", attenuationValues.quadratic);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].position", entitiesOther.at(i).lock()->getComponent<Transform>()->getPosition());
    };
  }

  void Light::setLightColor(glm::vec3 _lightColor)
  {
    lightColor = _lightColor;
  }

  void Light::setDiffuseColor(glm::vec3 _diffuseColor)
  {
    diffuseColor = _diffuseColor;
  }

  void Light::setAmbientColor(glm::vec3 _ambientColor)
  {
    ambientColor = _ambientColor;
  }

  void Light::setSpecularColor(glm::vec3 _specularColor)
  {
    specularColor = _specularColor;
  }

  void Light::setAttenuation(float _constant, float _linear, float _quadratic)
  {
    attenuationValues.constant = _constant;
    attenuationValues.linear = _linear;
    attenuationValues.quadratic = _quadratic;
  }


}