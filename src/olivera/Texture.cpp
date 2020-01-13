#include "Texture.h"
#include "stb_image.h"
#include <iostream>

namespace olivera
{
  int Texture::LoadTexture()
  {
	 
    glGenTextures(1, &id);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(getPath().c_str(), &width, &height, &channels, 0);
    if (data)
    {
      GLenum format;
      if (channels == 1)
        format = GL_RED;
      else if (channels == 3)
        format = GL_RGB;
      else if (channels == 4)
        format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, id);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(data);
    }
    else
    {
      std::cout << "Texture failed to load at path: " << getPath() << std::endl;
      stbi_image_free(data);
    }
    return id;
  }

  glm::vec2 Texture::getSize()
  {
    return size;
  }

  GLuint Texture::getId()
  {
    return id;
  }

  std::shared_ptr<Texture> Texture::load(std::string _path)
  {
	  std::cout << _path << std::endl;
	  setPath(_path);
	  return std::shared_ptr<Texture>();
  }


}