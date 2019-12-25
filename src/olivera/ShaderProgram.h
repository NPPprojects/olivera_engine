#include <GL/glew.h>
#include <glm/glm.hpp>


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace olivera
{

  class ShaderProgram
  {
  public:

    void initialiseVertexData(const char* _ObjectFile);
    int verteciesCount; //Amount of vertecies in an object
    void setVertexData();         //set up vertex data (and buffer(s)) and configure vertex attributes
    void draw();
    GLuint getID();
    void useShader();
    ShaderProgram(const char* VertexPath, const char* fragmentPath, const char* = nullptr);
  protected:


  private:
    GLuint ID;
    //Vertex Data Initialisation
    unsigned int VBO, VAO, EBO; //Vertex Buffer Object, Vertex Array Object, Element Buffer Object
    unsigned int indexCount; //For EBO
    int attributeTypeCount; //Counter for amount of Attributes
    int stride;     //The stride
    std::ifstream vertexData; //VertexDataFile
    int totalVertexFloatCount;       //Total Vertex Amount
    std::vector<float> vertexInduvidualData; //All vertex data
    std::vector<int> vertexPrValue; //Layout number

    void splitStringWhitespace(std::string&, std::vector<std::string>&);
    void readVertexData(const char*);
    void checkCompileErrors(GLuint, std::string);

  public:
    // utility uniform functions
  // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
      glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
      glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
      glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
      glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
      glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
      glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
      glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
      glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
      glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }


  };

}