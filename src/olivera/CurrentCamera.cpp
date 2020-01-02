#include "CurrentCamera.h"
#include "Core.h"
#include "Camera.h"
namespace olivera
{

  glm::mat4 CurrentCamera::getProjection()
  {
    return projection;
  }

  void CurrentCamera::setProjection()
  {
    projection = glm::perspective(glm::radians(camera->getZoom()), (float)800 / (float)600, 0.1f, 100.f);
  }
  glm::mat4 CurrentCamera::getView()
  {
    return view;
  }
  void CurrentCamera::setView()
  {
    view = camera->GetViewMatrix();
  }
}