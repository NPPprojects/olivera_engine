#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "PostProcessing.h"
#include "ResourceManager.h"
#include "Core.h"

namespace olivera 
{



  PostProcessing::PostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh, int _width, int _height)
  {
    core = _core;

    shader =core.lock()->getResources()->load<ShaderProgram>(_shader);
    squareMesh = core.lock()->getResources()->load<VertexBuffer>(_mesh);;

    blurIntesity= 1;
    exposure= 0.5;
    gamma= 1.25;
    filter= false;

    FrameBufferConfiguration(_width, _height);
  }

  void PostProcessing::FrameBufferConfiguration(int _width, int _height)
  {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    // create a color attachment texture

    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer); // now actually attach it
    //Error Handling
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  int PostProcessing::getFBO()
  {
    return FBO;
  }

  void PostProcessing::use()
  {
    shader.lock()->useShader();
    glBindVertexArray(squareMesh.lock()->getVAO());
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, squareMesh.lock()->getVerticiesCount());

    shader.lock()->setFloat("gamma", gamma);
    shader.lock()->setFloat("exposure", exposure);
    shader.lock()->setInt("blurIntesity", blurIntesity);
    shader.lock()->setBool("filter", filter);
  }

}