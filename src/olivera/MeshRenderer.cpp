
#include <iostream>

#include "MeshRenderer.h"

#include"Core.h"
#include "Entity.h"

#include "ResourceManager.h"
#include "CurrentCamera.h"
#include "CameraContext.h"

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Transform.h"

#include "Model.h"

#include "Materials.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
namespace olivera
{


void MeshRenderer::onInitialise(std::vector<std::string> _texturePaths, std::string _meshPath, std::string _shaderPath)
{
  entitySelf= getEntity();
  core = getCore();
  shader = core.lock()->getResources()->load<ShaderProgram>(_shaderPath);
  object = core.lock()->getResources()->load<VertexBuffer>(_meshPath);
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCameraList()->getCurrentCamera();
  shader->useShader();
  for (int i = 0; i < _texturePaths.size(); i++)
  {
	  texture.push_back(core.lock()->getResources()->load<Texture>(_texturePaths.at(i)));	 
    shader->setInt("texture" + std::to_string(i) + "", i);
  }
}
void MeshRenderer::onInitialise(std::string _modelPath, std::string _shaderPath)
{
  entitySelf = getEntity();
  core = getCore();
  shader = core.lock()->getResources()->load<ShaderProgram>(_shaderPath);
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCameraList()->getCurrentCamera();
  model = core.lock()->getResources()->load<Model>(_modelPath);
  
   shader->useShader();


}
void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::onTick()
{

  shader->useShader();

  shader->setMat4("projection", cameraContext.lock()->getProjection()); 
  shader->setMat4("view", cameraContext.lock()->getView());
  shader->setMat4("model", transform.lock()->getModel());
  glUseProgram(0);
}
void MeshRenderer::Draw()
{
  shader->useShader();
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
    model.lock()->draw(shader);
  }
}

//Set Uniform Function
}
 