#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Core.h"
#include "ShadowsFBO.h"


namespace olivera
{

  void ShadowsFBO::initialise()
  {

    glGenFramebuffers(1, &FBO);

    // create depth cubemap texture
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void ShadowsFBO::createCubemapTransformationMatrices(glm::vec3 _lightPos)
  {
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)resolution / (float)resolution, nearPlane, farPlane);

    shadowTransforms.clear();
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(_lightPos, _lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
  }

  void ShadowsFBO::bindFBO(std::shared_ptr<Core> _core, std::string _shader)
  {
    glViewport(0, 0, resolution, resolution);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < 6; ++i)
    {
      _core->getResources()->load<ShaderProgram>(_shader)->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    }
  }
  float ShadowsFBO::getNearPlane()
  {
    return nearPlane;
  }
  float ShadowsFBO::getFarPlane()
  {
    return farPlane;
  }
}