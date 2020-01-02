#include <iostream>

#include "MeshRenderer.h"


#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "Camera.h"
#include "Texture.h"
#include"Entity.h"

namespace olivera
{


void MeshRenderer::onInitialise(std::shared_ptr<Entity> _cameraEntity)
{
  entitySelf= getEntity();
  cameraEntity = _cameraEntity;
  shader = entitySelf->getComponent<ShaderProgram>();
  object = entitySelf->getComponent<VertexBuffer>();
  core = getCore();
  
}

void MeshRenderer::onDisplay()
{ 
  Draw();
}
void MeshRenderer::Draw()
{

  
  glUseProgram(shader->getID());
  

  projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(cameraEntity->getComponent<Camera>()->getZoom()), (float)800 / (float)600, 0.1f, 100.0f);
  shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
  view = cameraEntity->getComponent<Camera>()->GetViewMatrix();
  shader->setMat4("view", view);
  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
  shader->setMat4("model", model);
  //
  glBindVertexArray(object->getVAO());
  glDrawArrays(GL_TRIANGLES, 0, object->getVerticiesCount());
  glBindVertexArray(0);
  glUseProgram(0);
}

//Set Uniform Function
}
