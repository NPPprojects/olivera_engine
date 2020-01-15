
#include <iostream>

#include "MeshRenderer.h"


#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include"Core.h"
#include "Entity.h"
#include "CurrentCamera.h"
#include "Transform.h"
#include "ResourceManager.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
namespace olivera
{


void MeshRenderer::onInitialise(std::vector<std::string> _TexturePaths)
{
 
  entitySelf= getEntity();
  core = getCore();
  shader = entitySelf.lock()->getComponent<ShaderProgram>();
  object = entitySelf.lock()->getComponent<VertexBuffer>();
  transform = entitySelf.lock()->getComponent<Transform>();
  cameraContext = core.lock()->getCurrentCamera();
  shader.lock()->useShader();
  for (int i = 0; i < _TexturePaths.size(); i++)
  {
	  texture.push_back(core.lock()->getResources()->load<Texture>(_TexturePaths.at(i)));	 
	 // shader.lock()->setInt("texture"+std::to_string(i)+"", texture.at(i).lock()->getId());

  }
  shader.lock()->setInt("texture0", 0);
  shader.lock()->setInt("texture1", 1);
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
  shader.lock()->setMat4("model", transform->getModel());
  glUseProgram(0);
}
void MeshRenderer::Draw()
{
  shader.lock()->useShader();
  glBindVertexArray(object.lock()->getVAO());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.at(0).lock()->getId());
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture.at(1).lock()->getId());
  	
  glDrawArrays(GL_TRIANGLES, 0, object.lock()->getVerticiesCount());

  glBindVertexArray(0);
  glUseProgram(0);
}

//Set Uniform Function
}
