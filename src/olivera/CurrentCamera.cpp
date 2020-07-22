#include "CurrentCamera.h"
#include "Core.h"
#include "PostProcessing.h"
#include <GL/glew.h>
#include <iostream>

namespace olivera
{

  glm::mat4 CurrentCamera::getProjection()
  {
    return projection;
  }

  glm::mat4 CurrentCamera::getView()
  {
    return view;
  }

  glm::vec4 CurrentCamera::getViewport()
  {
    return viewport;
  }

  std::shared_ptr<PostProcessing> CurrentCamera::getFrameBuffer()
  {
    return framebuffer;
  }

  void CurrentCamera::setView(glm::mat4 _view)
  {
    view = _view;
  }

  void CurrentCamera::setProjection(glm::mat4 _projection)
  {
    projection = _projection;
  }

  void CurrentCamera::setViewport(glm::vec4 _viewport)
  {
    viewport = _viewport;
  }

  void CurrentCamera::activeFrameBuffer()
  {

    if (framebuffer != nullptr)
    {
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->getFBO());
      glEnable(GL_DEPTH_TEST); // enable depth testing (is di sabled for rendering screen-space quad)
      glEnable(GL_CULL_FACE);
      glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    

  }
  void CurrentCamera::useFrameBuffer()
  {
    if (framebuffer != nullptr)
    {
      framebuffer->use();
    }
  }
  void CurrentCamera::clear()
  {
    if (framebuffer != nullptr)
    {
      //now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
      // clear all relevant buffers
      glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
  }

  void CurrentCamera::setFrameBuffer(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh)
  {
    framebuffer = std::make_shared<PostProcessing>(_core, _shader, _mesh,  viewport.z, viewport.w);
   
  }


}