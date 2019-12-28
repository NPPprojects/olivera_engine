#include "MeshRenderer.h"

#include "ShaderProgram.h"

#include "Texture.h"
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

  shader->draw();
}

}
