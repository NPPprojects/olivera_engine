
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
  cameraContext = core.lock()->getCurrentCamera();
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
  cameraContext = core.lock()->getCurrentCamera();
  model = core.lock()->getResources()->load<Model>(_modelPath);
  
   shader->useShader();



   glm::vec3 lightColor = glm::vec3(10.0f, 10.0f, 10.0f);
   glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
   glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

   for (unsigned int i = 0; i <= 1; ++i)
   {


     shader->setVec3("pointLights[" + std::to_string(i) + "].position", glm::vec3(0.0f,0.0f,0.0f));
     shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", ambientColor);
     shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", diffuseColor);
     shader->setVec3("pointLights[" + std::to_string(i) + "].specular", 10.0f, 10.0f, 10.0f);

     //Point light attenuation
     shader->setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
     shader->setFloat("pointLights[" + std::to_string(i) + "].linear", 0.045f);
     shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.075f);
   };
  
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
