#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace olivera 
{
  /**
* Component class to hold transformation logic for entities 
*/
  class Transform : public Component
  {
  public:
  
  /**
  *\ Getter for the model matrix of an entity
  */
  glm::mat4 getModel();
  
  /**
  *\ Brief update model is ran every tick to update the model matrix with newest position/rotation/scale
  */
	void updateModel();
  
  /**
  *\ Setter for Position vector
  */
	void setPosition(glm::vec3 _position);
	
  /**
  *\ Setter for Rotation vector
  */
  void setRotation(glm::vec3 _rotation);
  
  /**
  *\ Setter for Scale Vector
  */
  void setScale(glm::vec3 _scale);

  /**
  *\ Getter for Position vector
  */
  glm::vec3 getPosition();

  /**
  *\ Getter for Rotation vector
  */
  glm::vec3 getRotation();
	
  /**
  *\ Getter for Scale Vector
  */
  glm::vec3 setScale();

  /**
  *\ onTick function for this component in which updateModel is called
  */
  void onTick();
	
  /**
  *\ initial initalisation for transform component
  */
  void onInitialise();
  
  private:  
	glm::vec3 position;///<position for Entity
  glm::vec3 rotation;///<rotation for Entity
  glm::vec3 scale;///<scale for Entity
    


  glm::mat4 model;///<Model Matrix for Entity
    

  };

}
