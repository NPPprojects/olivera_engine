#include <GL/glew.h>
#include <glm/glm.hpp>


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

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
   
};