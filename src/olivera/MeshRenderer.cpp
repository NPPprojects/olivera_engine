
#include <iostream>

#include "MeshRenderer.h"

#include"Core.h"
#include "Entity.h"

#include "ResourceManager.h"
#include "CurrentCamera.h"

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Model.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
namespace olivera
{


void MeshRenderer::onInitialise(std::vector<std::string> _texturePaths, std::string _meshPath)
{
  entitySelf= getEntity();
  core = getCore();
  shader = entitySelf.lock()->getComponent<ShaderProgram>();
  object = core.lock()->getResources()->load<VertexBuffer>(_meshPath);
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCurrentCamera();
  shader.lock()->useShader();
  for (int i = 0; i < _texturePaths.size(); i++)
  {
	  texture.push_back(core.lock()->getResources()->load<Texture>(_texturePaths.at(i)));	 
    shader.lock()->setInt("texture" + std::to_string(i) + "", i);
  }
}
void MeshRenderer::onInitialise(std::string _modelPath)
{
  entitySelf = getEntity();
  core = getCore();
  shader = entitySelf.lock()->getComponent<ShaderProgram>();
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCurrentCamera();
  //model = core.lock()->getResources()->load<Model>(_modelPath);
  
}
void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::onTick()
{

  shader.lock()->useShader();
  projection = glm::mat4(1.0f);
  projection = cameraContext.lock()->getProjection();
  shader.lock()->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
  view = cameraContext.lock()->getView();
  shader.lock()->setMat4("view", view);
  shader.lock()->setMat4("model", transform.lock()->getModel());
  glUseProgram(0);
}
void MeshRenderer::Draw()
{
  shader.lock()->useShader();
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
   // model.lock()->Draw(shader.lock());
  }
}

//Set Uniform Function
}
