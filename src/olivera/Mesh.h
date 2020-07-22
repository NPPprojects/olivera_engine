#include <GL/glew.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace olivera 
{
  class ShaderProgram;

  /***************************************************
  @briefStruct to hold vertex data from the 3d model

  ****************************************************/
  struct Vertex {
    // position
    glm::vec3 Position;
    // normals
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // s
    glm::vec3 Tangent;
    // bitangents
    glm::vec3 Bitangent;
  };

  /****************************************************
  @brief Struct to hold texture data from the 3d model

  *****************************************************/
  struct Textures {
    unsigned int id;
    std::string type;
    std::string path;

    std::string GetPath() { return path; };
    std::string GetType() { return type; };
    unsigned int GetId() { return id; };

  };
  /********************************************
  @brief Mesh class used by the model class to 
  generate the mesh for the 3D object.

  *********************************************/
  class Mesh {
    public:

      /***********************************************************
      @brief  When its constructed, pass the object's verticies, 
      indicies and textures to then call setupMesh() to
      initialise all VAO/VBO/EBOs the mesh contains.

      @param std::vector<Vetex> vertices
      @param std::vector<unsigned int> indices
      @param std::vector<Textures> textures

      ************************************************************/
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);


      /********************************************************
      @brief Render the mesh using the attached shader program

      @param std::shared_ptr<ShaderProgram>  shader 
    
      *********************************************************/
       void draw(std::shared_ptr<ShaderProgram> shader, unsigned int _shadowCubemap);

      void draw();


    private:
    /************************************************************************************************************/

      /**************************************************
      @brief Initalise all VAO/VBO/EBO the mesh contains

      ***************************************************/
        void setupMesh();
                                                                       
      std::vector<Vertex> vertices;                                           //!< Store verticies relevent data                                                                    
      std::vector<Textures> textures;                                              //!< Store textures of object
                                                                        
      unsigned int VAO;                                                                 //!< Vertex Array Object
      unsigned int VBO;                                                                //!<Element Buffer Object 
      unsigned int EBO;                                                                 //!<Vertex Buffer Object  
                                                       
      std::vector<unsigned int> indices;                   //!<Store vertex indicies in models where EBO is used

    /************************************************************************************************************/
  };
}


