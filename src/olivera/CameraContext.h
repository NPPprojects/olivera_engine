#include <memory>
#include <vector>
#include "CurrentCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace olivera
{
  /***********************************************************************
   @brief Contains a list of camera's and methods to access them.

   *Contains an index to access the currently active camera at any time.

   ***********************************************************************/
  class CameraContext
    {
    public:

      /*********************************************************
        @brief Getter for the camera list contained within core.

        @return a vector of cameras.

      **********************************************************/
      std::vector<std::shared_ptr <CurrentCamera>> getCameraList();

      /*********************************************
        @brief Add a camera to the list of cameras.

        @param CurrentCamera cameraContext

      **********************************************/
      void addCamera(std::shared_ptr<CurrentCamera> _cameraContext);
    
      /***************************************
        @brief Sets the current camera index.

        @param int cameraIndex

      ****************************************/
      void setCurrentCamera(int _currentCamera);

      /******************************************* 
        @brief Gets the currently indexed camera.

        @return Camera at the current index.

      ********************************************/
      std::shared_ptr<CurrentCamera>  getCurrentCamera();
   
    private:
    /**********************************************************************************************/

      std::vector<std::shared_ptr<CurrentCamera>>  cameraList;                 //!< List of cameras
      int currentCamera;                                      //!< Container for camera index value

    /**********************************************************************************************/
    };

}
