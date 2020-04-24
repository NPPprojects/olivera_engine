#ifndef OLIVERA_CURRENTCAMERA_H
#define OLIVERA_CURRENTCAMERA_H


#include <memory>
#include <vector>
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
 
  class PostProcessing;

  /***********************************************************
  @brief Camera context held within the engine, users have to 
  write the camera functionality themselves.

  *Provides method to access and modify a camera's viewport,
  framebuffer, projection and view matrix.
  
  ************************************************************/
  class CurrentCamera 
  {
  public:
  /***********************************
  @brief Getter for projection matrix.
  
  @return Camera's projection matrix.
  
  ************************************/
    glm::mat4 getProjection();

  /***********************************
  @brief Getter for view matrix.

  @return Camera's view matrix.

  ************************************/
    glm::mat4 getView();
  
  /***********************************
  @brief getter for camera's viewport.

  @return camera's viewport.

  ************************************/ 
    glm::vec4 getViewport();

  /***************************************
  @brief getter for camera's framebuffer.

  @return camera's framebuffer.

  ****************************************/
    std::shared_ptr<PostProcessing> getFrameBuffer();

  /***********************************
  @brief Setter for view matrix.

  @param glm::mat4 viewMatrix.

  ************************************/
	  void setView(glm::mat4 _view);

  /***********************************
  @brief Setter for projection matrix.

  @param glm::mat4 projectionMatrix.

  ************************************/
    void setProjection(glm::mat4 _projection);
  
  /***********************************
  @brief Setter for camera's viewport.

  @param glm::vec4 cameraViewport.

  ************************************/
    void setViewport(glm::vec4 _viewport);


  /*********************************************
  @brief Setter for camera's framebuffer.

  @param std::shared_ptr<Core> active core
  @param std::string _shader of the framebuffer
  @param std::string _mesh of the framebuffer

  **********************************************/
    void setFrameBuffer(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh);


  /***********************************
  @brief Prepares the openGl for the
  current camera's framebuffer.

  ************************************/
  void activeFrameBuffer();

  /***********************************
  @brief Render's the framebuffer
  after loading it with the scene's 
  render texture.

  ************************************/
  void useFrameBuffer();

/**************************************
@brief Reset's the framebuffer to zero
after creating the rendertexture 

***************************************/
    void clear();

  private:
  /**************************************************************************/

    glm::mat4 view;   //!<Camera's view matrix
    glm::mat4 projection;//!<Camera's projection matrix
    glm::vec4 viewport;//!< Camera's viewport coordinates
    
    std::shared_ptr<PostProcessing> framebuffer;//!< Camera's framebuffer

  /**************************************************************************/
  };
}

#endif