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

  /**
  *Camera context held within the engine, users have to write the camera functionality themselves and use this class to set the projection and view 
  */
  class CurrentCamera 
  {
  public:
  /**
  *\ Getter for Projection Matrix
  */
    glm::mat4 getProjection();

  /**
  *\ Getter for View Matrix
  */
  glm::mat4 getView();
  
  /**
  *\ Setter for View Matrix
  */
	void setView(glm::mat4 _view);

  /**
  *\ Setter for Projection matrix
  */
  void setProjection(glm::mat4 _projection);
  
  void setViewport(glm::vec4 _viewport);

  void activeFrameBuffer();

  void useFrameBuffer();

  void clear();

  void setFrameBuffer(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh
  );

  glm::vec4 getViewport();

  std::shared_ptr<PostProcessing> getFrameBuffer();


  private:
    glm::mat4 view;///<view matrix
    glm::mat4 projection;///<projection matrix
    glm::vec4 viewport;///< store viewport coordinates
    
    std::shared_ptr<PostProcessing> framebuffer;

  };
}

#endif