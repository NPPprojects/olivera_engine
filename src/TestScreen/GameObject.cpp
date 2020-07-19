#include "GameObject.h"



GameObject::GameObject(std::shared_ptr<olivera::Core> &_scene, std::string _objectShader, std::string _depthMapShader, std::string _model)
{

  objectShaderProgram = _scene->getResources()->load<olivera::ShaderProgram>(_objectShader);
  objectResouces->create<olivera::ShaderProgram>(objectShaderProgram->getName(), objectShaderProgram->getPath());
  shadowShaderProgram = _scene->getResources()->load<olivera::ShaderProgram>(_depthMapShader);
  objectResouces->create<olivera::ShaderProgram>(shadowShaderProgram->getName(), shadowShaderProgram->getPath());

  self = _scene->addEntity();
  transform = self->addComponent<olivera::Transform>();
  meshRenderer = self->addComponent<olivera::MeshRenderer>(_model, objectShaderProgram->getName(), objectResouces);

}
void GameObject::addLight(std::vector <std::shared_ptr <olivera::Entity >> &_lightSources)
{

  addMaterial();
  addShadows(_lightSources);
  lightSources = self->addComponent<olivera::Light>(objectShaderProgram->getName(), _lightSources, objectResouces);

}

void GameObject::addMaterial()
{
  material = self->addComponent<olivera::Materials>(objectShaderProgram->getName(), objectResouces);
  material->setDefaultMaterial(32.0f, 0, 1);
}

void GameObject::addShadows(std::vector <std::shared_ptr <olivera::Entity >> &_lightSources)
{
  shadows = self->addComponent<olivera::Shadows>(shadowShaderProgram->getName(), _lightSources, objectResouces);

}
std::shared_ptr<olivera::Transform> GameObject::getTransform()
{
  return transform;
}