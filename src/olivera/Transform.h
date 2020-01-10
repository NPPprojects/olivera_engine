#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace olivera 
{
  class Transform : public Component
  {
  public:
    glm::mat4 getModel();

	void updateModel();

	void setPosition(glm::vec3 _position);
	void setRotation(glm::vec3 _rotation);
	void setScale(glm::vec3 _scale);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 setScale();

	void onTick();
	void onInitialise();
  private:
    
	glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    


	glm::mat4 model;
    

  };

}
