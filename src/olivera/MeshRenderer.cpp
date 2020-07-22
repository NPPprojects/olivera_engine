
#include <iostream>

#include "MeshRenderer.h"

#include"Core.h"
#include "Entity.h"

#include "ResourceManager.h"
#include "CurrentCamera.h"
#include "CameraContext.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Transform.h"

#include "Model.h"

#include "Materials.h"

#include "ShadowsFBO.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
namespace olivera
{


void MeshRenderer::onInitialise(std::vector<std::string> _texturePaths, std::string _meshPath, std::string _shaderPath)
{
  entitySelf= getEntity();
  core = getCore();
  shader = core.lock()->getResources()->load<ShaderProgram>(_shaderPath);
  object = core.lock()->getResources()->load<VertexArray>(_meshPath);
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCameraList()->getCurrentCamera();
  shader.lock()->useShader();
  for (unsigned int i = 0; i < _texturePaths.size(); i++)
  {
	  texture.push_back(core.lock()->getResources()->load<Texture>(_texturePaths.at(i)));	 
    shader.lock()->setInt("texture" + std::to_string(i) + "", i);
  }
}
void MeshRenderer::onInitialise(std::string _modelPath, std::string _shaderPath, std::string _depthMapShader, std::shared_ptr<ResourceManager> _resourceManager)
{
  entitySelf = getEntity();
  core = getCore();
  for (int i = 0; i < shaders.size(); i++)
  {
//    shaders.at(i)= _resourceManager->load<ShaderProgram>(_shaderPath);
  }
  shader = _resourceManager->load<ShaderProgram>(_shaderPath);
  depthShader = _resourceManager->load<ShaderProgram>(_depthMapShader);
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCameraList()->getCurrentCamera();
  model = core.lock()->getResources()->load<Model>(_modelPath);
  



}
void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::onShadowDisplay()
{
  if (depthShader.lock() != nullptr)
  {
    depthShader.lock()->useShader();
    depthShader.lock()->setMat4("model", transform.lock()->getModel());
  
    model.lock()->draw();
    glUseProgram(0);
  }

}
void MeshRenderer::onTick()
{

  glUseProgram(0);
}
void MeshRenderer::Draw()
{
  shader.lock()->useShader();

  shader.lock()->setMat4("projection", cameraContext.lock()->getProjection());
  shader.lock()->setMat4("view", cameraContext.lock()->getView());
  shader.lock()->setMat4("model", transform.lock()->getModel());

  if (object.lock() != nullptr)
  {
    glBindVertexArray(object.lock()->getVAO());

    for (int i = 0; i < texture.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, texture.at(i).lock()->getId());
    }

    glDrawArrays(GL_TRIANGLES, 0, object.lock()->getVerticiesCount());
    glBindVertexArray(0);
    glUseProgram(0);
  }
  else
  {
    model.lock()->draw(shader.lock(),getCore()->getShadowFBO()->getDepthCubemap());
  }
}

//Set Uniform Function
}
 