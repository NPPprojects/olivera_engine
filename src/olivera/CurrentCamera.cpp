#include "CurrentCamera.h"
#include "Core.h"

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



}