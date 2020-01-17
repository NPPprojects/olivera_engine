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

  /**
  *Struct to hold vertex data from the 3d model
  */
  struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
  };

  /**
  *Struct to hold texture data from the 3d model
  */
  struct Textures {
    unsigned int id;
    std::string type;
    std::string path;

    std::string GetPath() { return path; };
    std::string GetType() { return type; };
    unsigned int GetId() { return id; };

  };
  /**
  *Mesh class used by the model class to generate the mesh for the 3D object
  */
  class Mesh {
  public:



    /**
    *\ Constructor
    */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);


    /**
    *\ Render the mesh
    */
    void draw(std::shared_ptr<ShaderProgram> shader);


  private:

    std::vector<Vertex> vertices;///< Store verticies information
    std::vector<unsigned int> indices; ///<store indicies incase of EBO
    std::vector<Textures> textures;///store textures of object
    unsigned int VAO;///< Vertex Array Object
    unsigned int VBO, EBO;///Vertex Buffer Object and Element Buffer Object

  /**
  *\ initalise all the buffer objects/arrays
  */
    void setupMesh();
  };
}


