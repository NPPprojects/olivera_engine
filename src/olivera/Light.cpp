#include "Light.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Entity.h"
#include "ShadowsFBO.h"
#include "Core.h"
namespace olivera
{
 
  void Light::onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_lightEntities, std::vector<std::shared_ptr<Entity>> &_cameraEntities, std::shared_ptr<ResourceManager> _resourceManager)
  {
    for (int i = 0; i < _lightEntities.size(); i++)
    {
      lightEntities.push_back(_lightEntities.at(i));
    }
    for (int i = 0; i < _cameraEntities.size(); i++)
    {
      cameraEntities.push_back(_cameraEntities.at(i));
    }

    lightColor = glm::vec3(10.0f, 10.0f, 10.0f);
    diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
    ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    specularColor = glm::vec3(10.f, 10.f, 10.f);

    attenuationValues.constant = 1.0f;
    attenuationValues.linear = 0.045f;
    attenuationValues.quadratic = 0.0075f;


    shader = _resourceManager->load<ShaderProgram>(_shader);
    shader.lock()->useShader();
    shader.lock()->setInt("diffuseTexture",0);
    shader.lock()->setBool("depthMap", 1);
  }
 
  void Light::onDisplay()
  {
    shader.lock()->useShader();

    shader.lock()->setBool("displayDepth",0 ); 
    shader.lock()->setFloat("far_plane", getCore()->getShadowFBO()->getFarPlane());

    shader.lock()->setVec3("pointLight.position", lightEntities.at(0).lock()->getComponent<Transform>()->getPosition());
    shader.lock()->setVec3("pointLight.ambient", ambientColor);
    shader.lock()->setVec3("pointLight.diffuse", diffuseColor);
    shader.lock()->setVec3("pointLight.specular", specularColor);
    shader.lock()->setFloat("pointLight.constant", attenuationValues.constant);
    shader.lock()->setFloat("pointLight.linear", attenuationValues.linear);
    shader.lock()->setFloat("pointLight.quadratic", attenuationValues.quadratic);
  
    shader.lock()->setVec3("viewPos", cameraEntities.at(0).lock()->getComponent<Transform>()->getPosition());

  }

  void Light::onTick()
  {
    shader.lock()->useShader();
    for (unsigned int i = 0; i < lightEntities.size(); ++i)
    {
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].ambient", ambientColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].diffuse", diffuseColor);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].specular", specularColor);

      //  //Point light attenuation
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].constant", attenuationValues.constant);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].linear", attenuationValues.linear);
      shader.lock()->setFloat("pointLights[" + std::to_string(i) + "].quadratic", attenuationValues.quadratic);
      shader.lock()->setVec3("pointLights[" + std::to_string(i) + "].position", lightEntities.at(i).lock()->getComponent<Transform>()->getPosition());
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