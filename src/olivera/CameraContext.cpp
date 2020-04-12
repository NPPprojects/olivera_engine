#include "CameraContext.h"

namespace olivera 
{
  std::vector<std::shared_ptr<CurrentCamera>> CameraContext::getCameraList()
  {
    return cameraList;
  }
  void CameraContext::setCamera(std::shared_ptr<CurrentCamera> _currentCamera)
  {
    cameraList.push_back(_currentCamera);
  }
  void CameraContext::setCurrentCamera(int _currentCamera)
  {
    currentCamera = currentCamera;
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