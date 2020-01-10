
#include <iostream>

#include "MeshRenderer.h"


#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include"Core.h"
#include "Entity.h"
#include "CurrentCamera.h"

#include "Transform.h"
namespace olivera
{


void MeshRenderer::onInitialise()
{
  entitySelf= getEntity();

  shader = entitySelf->getComponent<ShaderProgram>();
  object = entitySelf->getComponent<VertexBuffer>();
  transform = entitySelf->getComponent<Transform>();
  core = getCore();
  cameraContext = core->getCurrentCamera();
  
}

void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::onTick()
{
  glUseProgram(shader->getID());
  projection = glm::mat4(1.0f);
  projection = cameraContext->getProjection();
  shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
  view = cameraContext->getView();
  shader->setMat4("view", view);

  shader->setMat4("model", transform->getModel());
  glUseProgram(0);
}
void MeshRenderer::Draw()
{
  glUseProgram(shader->getID()); 
  glBindVertexArray(object->getVAO());
  glDrawArrays(GL_TRIANGLES, 0, object->getVerticiesCount());

  glBindVertexArray(0);
  glUseProgram(0);
}

//Set Uniform Function
}
