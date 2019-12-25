#include "MeshRenderer.h"

#include "ShaderProgram.h"

#include <iostream>

namespace olivera
{

void MeshRenderer::onInitialise()
{
  shader = std::make_shared<ShaderProgram>("resources/shaders/simple.vert", "resources/shaders/simple.frag");
 
  shader->initialiseVertexData("resources/objects/triangle.data");
}

void MeshRenderer::onDisplay()
{
  shader->setMat4("in_Model", glm::mat4(1.0f));
  shader->setMat4("in_Projection", glm::mat4(1.0f));
  shader->draw();
}

}
