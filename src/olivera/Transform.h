#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace olivera 
{
  class Transform : public Component
  {
  public:
  
  /**
  *\ Getter for XCoordinate on window
  */
  glm::mat4 getModel();
  
  /**
  *\ Getter for XCoordinate on window
  */
	void updateModel();
  
  /**
  *\ Getter for XCoordinate on window
  */
	void setPosition(glm::vec3 _position);
	
  /**
  *\ Getter for XCoordinate on window
  */
  void setRotation(glm::vec3 _rotation);
  
  /**
  *\ Getter for XCoordinate on window
  */
  void setScale(glm::vec3 _scale);

  /**
  *\ Getter for XCoordinate on window
  */
  glm::vec3 getPosition();

  /**
  *\ Getter for XCoordinate on window
  */
  glm::vec3 getRotation();
	
  /**
  *\ Getter for XCoordinate on window
  */
  glm::vec3 setScale();

  /**
  *\ Getter for XCoordinate on window
  */
  void onTick();
	
  /**
  *\ Getter for XCoordinate on window
  */
  void onInitialise();
  
  private:  
	glm::vec3 position;///<position for Entity
  glm::vec3 rotation;///<rotation for Entity
  glm::vec3 scale;///<scale for Entity
    


  glm::mat4 model;///<Model Matrix for Entity
    

  };

}
