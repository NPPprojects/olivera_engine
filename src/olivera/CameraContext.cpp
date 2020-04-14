#include "CameraContext.h"

namespace olivera 
{
  std::vector<std::shared_ptr<CurrentCamera>> CameraContext::getCameraList()
  {
    return cameraList;
  }
  void CameraContext::setCurrentCamera(int _currentCamera)
  {
    currentCamera = _currentCamera;
  }

  std::shared_ptr<CurrentCamera> CameraContext::getCurrentCamera()
  {
   return cameraList.at(currentCamera);
  }

  void CameraContext::addCamera(std::shared_ptr<CurrentCamera> _cameraContext)
  {
    cameraList.push_back(_cameraContext);
  }
 
}