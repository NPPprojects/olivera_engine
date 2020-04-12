#include <memory>
#include <vector>
#include "CurrentCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace olivera
{
  class CameraContext
  {
  public:
    std::vector<std::shared_ptr <CurrentCamera>> getCameraList();

    void setCamera(std::shared_ptr<CurrentCamera> _cameraContext);
    
    void setCurrentCamera(int _currentCamera);

    std::shared_ptr<CurrentCamera>  getCurrentCamera();

    void addCamera(std::shared_ptr<CurrentCamera> _cameraContext);

  private:
   std::vector<std::shared_ptr<CurrentCamera>>  cameraList;

    int currentCamera;
  };

}
