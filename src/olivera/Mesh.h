#pragma once



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

  struct Texture {
    unsigned int id;
    std::string type;
    std::string path;

    std::string GetPath() { return path; };
    std::string GetType() { return type; };
    unsigned int GetId() { return id; };

  };

  class ShaderProgram;

  class Mesh {
  public:



    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);


    // render the mesh
    void Draw(std::shared_ptr<ShaderProgram> shader);


  private:
    /*  Render data  */

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;
    unsigned int VBO, EBO;

    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh();
  };
}