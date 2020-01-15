
#include "Resource.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace olivera
{

  class Texture : public Resource
  {
	  friend class Resource;
  public:

	Texture() {}
	Texture(std::string path);
    glm::vec2 getSize();
    GLuint getId();


	
	//Resource



  private:
    GLuint id;
    glm::vec2 size;
	

  };


}
