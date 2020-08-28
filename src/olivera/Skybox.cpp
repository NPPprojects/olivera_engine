#include "Skybox.h"
#include "CurrentCamera.h"
#include "CameraContext.h"

#include "Core.h"
#include "Entity.h"

#include "VertexArray.h"
#include "ShaderProgram.h"

#include "ResourceManager.h"
#include "stb_image.h"

#include "Texture.h"

namespace olivera
{


  void Skybox::onInitialise(std::vector<std::string> _textures)
  {
    entitySelf = getEntity();
    core= entitySelf.lock()->getCore();

    cameraContext = core.lock()->getCameraList()->getCurrentCamera();

    resources = std::make_shared<ResourceManager>();
    resources->create<VertexArray>(std::string("skyboxMesh"), std::string("../resources/objects/skyboxMesh.data"));
    resources->create<ShaderProgram>(std::string("skyboxShader"), std::string("../resources/shaders/skyboxShader.txt"));

    mesh = resources->load<VertexArray>("skyboxMesh");
    shader = resources->load<ShaderProgram>("skyboxShader");
    shader.lock()->useShader();
    for (int i = 0; i < 6; i++)
    {
      faces.push_back(core.lock()->getResources()->load<Texture>(_textures.at(i)));
    }
    shader.lock()->setInt("skybox", 0);
    cubemapTexture = loadCubemap();

  

  }

  void Skybox::onTick()
  {
  

  }

  void Skybox::onDisplay()
  {
    
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    shader.lock()->useShader();
    glm::mat4 view = glm::mat4(glm::mat3(cameraContext.lock()->getView()));

    //Projection matrix
    shader.lock()->useShader();
    shader.lock()->setMat4("view", view);
    shader.lock()->setMat4("projection", ((cameraContext.lock()->getProjection())));
    glBindVertexArray(mesh.lock()->getVAO());
    glActiveTexture(GL_TEXTURE0);
    std::cout << cubemapTexture << std::endl;
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);	//Will always be 36 as skybox is just a cube
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
  }

  int Skybox::loadCubemap()
  {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
      unsigned char *data = stbi_load(faces[i].lock()->getPath().c_str(), &width, &height, &nrChannels, 0);
      if (data)
      {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
      }
      else
      {
        std::cout << "Cubemap texture failed to load at path: " << faces[i].lock()->getPath() << std::endl;
        stbi_image_free(data);
      }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
  }

}