
#include "Resource.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace olivera
{

  class Texture : public Resource
  {
	  friend class Resource;
  public:

	  int LoadTexture();
    glm::vec2 getSize();
    GLuint getId();


	
	//Resource
	std::shared_ptr<Texture> load(std::string _path);


  private:
    GLuint id;
    glm::vec2 size;
	

  };


}


