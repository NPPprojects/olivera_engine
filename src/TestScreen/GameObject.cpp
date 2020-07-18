#include "GameObject.h"



GameObject::GameObject(std::shared_ptr<olivera::Core> &_scene,std::string _shader, std::string _model)
{

  shaderProgram = _scene->getResources()->load<olivera::ShaderProgram>(_shader);
  objectResouces->create<olivera::ShaderProgram>(shaderProgram->getName(), shaderProgram->getPath());
 

  self = _scene->addEntity();
  transform = self->addComponent<olivera::Transform>();
  meshRenderer = self->addComponent<olivera::MeshRenderer>( _model, shaderProgram->getName(),objectResouces);
  
}
void GameObject::addLight(std::vector <std::shared_ptr <olivera::Entity >> &_lightSources) 
{
 
  addMaterial();
  lightSources = self->addComponent<olivera::Light>(shaderProgram->getName(),_lightSources, objectResouces);

}

void GameObject::addMaterial()
{
  material = self->addComponent<olivera::Materials>(shaderProgram->getName(), objectResouces);
  material->setDefaultMaterial(32.0f, 0, 1);
}

std::shared_ptr<olivera::Transform> GameObject::getTransform()
{
  return transform;
}