#include "Shadows.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include "ShadowsFBO.h"
namespace olivera 
{

  void Shadows::onInitialise(std::string _shader, std::vector<std::shared_ptr<Entity>> &_entitiesOther, std::shared_ptr<ResourceManager> _resourceManager)
  {
    shadowResources = _resourceManager;
    shader = _resourceManager->load<ShaderProgram>(_shader);
    for (int i = 0; i < _entitiesOther.size(); i++)
    {
      entitiesOther.push_back(_entitiesOther.at(i));
    }
  }

  void Shadows::onTick()
  {
    getCore()->getShadowFBO()->createCubemapTransformationMatrices(entitiesOther.at(0).lock()->getComponent<Transform>()->getPosition());
    shader.lock()->useShader();
    shader.lock()->setVec3("lightPos", entitiesOther.at(0).lock()->getComponent<Transform>()->getPosition());
    shader.lock()->setFloat("far_plane", getCore()->getShadowFBO()->getFarPlane());
    getCore()->getShadowFBO()->bindFBO(shadowResources.lock(), shader.lock()->getName());

    
  }

  void Shadows::onDisplay()
  {

  }

}