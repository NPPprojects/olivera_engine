
#include <iostream>

#include "MeshRenderer.h"


#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include"Core.h"
#include "Entity.h"
#include "CurrentCamera.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
namespace olivera
{


void MeshRenderer::onInitialise()
{
 
  entitySelf= getEntity();
  
  shader = entitySelf.lock()->getComponent<ShaderProgram>();
  object = entitySelf.lock()->getComponent<VertexBuffer>();
  transform = entitySelf.lock()->getComponent<Transform>();
  core = getCore();
  cameraContext = core.lock()->getCurrentCamera();
   
}

void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::onTick()
{

  glUseProgram(shader.lock()->getID());
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
  glUseProgram(shader.lock()->getID());
  glBindVertexArray(object.lock()->getVAO());
  glDrawArrays(GL_TRIANGLES, 0, object.lock()->getVerticiesCount());

  glBindVertexArray(0);
  glUseProgram(0);
}

//Set Uniform Function
}
