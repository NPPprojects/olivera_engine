
#include "Resource.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace olivera
{
  /*********************************************
  *Resource derived class to generate a texture

  **********************************************/
  class Texture : public Resource
  {
    public:

    /*********************************************************************
    @brief Constructor to generate Texture when a texture gets initalised
    **********************************************************************/
	    Texture(std::string _path);

    /************************
    @brief Getter Texture ID

    *************************/
      GLuint getId();

    private:
    /***************************************************************************************************/
    
      GLuint id;                                                     //!<ID to acecess generated Texture

	
    /***************************************************************************************************/
  };


}
