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

  void CurrentCamera::setView(glm::mat4 _view)
  {
    view = _view;
  }

  void CurrentCamera::setProjection(glm::mat4 _projection)
  {
    projection = _projection;
  }

}