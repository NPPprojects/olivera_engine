#include "ShaderProgram.h"

namespace olivera
{
  ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
  {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      // open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
      // if geometry shader path is present, also load a geometry shader
      if (geometryPath != nullptr)
      {
        gShaderFile.open(geometryPath);
        std::stringstream gShaderStream;
        gShaderStream << gShaderFile.rdbuf();
        gShaderFile.close();
        geometryCode = gShaderStream.str();
      }

    }
    catch (std::ifstream::failure e)
    {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if (geometryPath != nullptr)
    {
      const char * gShaderCode = geometryCode.c_str();
      geometry = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(geometry, 1, &gShaderCode, NULL);
      glCompileShader(geometry);
      checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (geometryPath != nullptr)
      glAttachShader(ID, geometry);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
      glDeleteShader(geometry);
    //Reset shader state
    glUseProgram(0);
  }

  void ShaderProgram::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
  {
    std::string curr;
    output.clear();
    for (size_t i = 0; i < input.length(); i++)
    {
      if (input.at(i) == ' ' ||
        input.at(i) == 'f' ||
        input.at(i) == ',' ||
        input.at(i) == '\r' ||
        input.at(i) == '\n' ||
        input.at(i) == '\t')
      {
        if (curr.length() > 0)
        {
          output.push_back(curr);
          curr = "";
        }
      }
      else
      {
        curr += input.at(i);
      }
    }
    if (curr.length() > 0)
    {
      output.push_back(curr);
    }
  }

  void ShaderProgram::readVertexData(const char* _ObjectFile)
  {
    std::string line;
    std::vector <std::string> Splitline;
   
      vertexData.open(_ObjectFile);                    //  read-Stream

      getline(vertexData, line);


      splitStringWhitespace(line, Splitline);

      attributeTypeCount = atoi(Splitline.at(0).c_str()); //Assign count of attributes

      verteciesCount = atoi(Splitline.at(1).c_str());
      stride = atoi(Splitline.at(2).c_str());

      for (int i = 0; i < attributeTypeCount; i++)
      {
        vertexPrValue.push_back(i);
        vertexPrValue[i] = atoi(Splitline.at(3 + i).c_str());

      }
      vertexData >> totalVertexFloatCount;            //Total Vertex Float Count


      for (int i = 0; i < totalVertexFloatCount; i++)
      {
        vertexInduvidualData.push_back(i);
        vertexData >> vertexInduvidualData[i];
        //	std::cout << vertexInduvidualData[i] << std::endl;
      }
    
 
    vertexData.close();
  }

  void ShaderProgram::setVertexData()
  {
    unsigned int SkipCounter = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexInduvidualData.size() * sizeof(vertexInduvidualData.at(0)), &vertexInduvidualData.at(0), GL_STATIC_DRAW);


    // Set the vertex attributes pointers
    for (int i = 0; i < attributeTypeCount; i++)
    {

      glVertexAttribPointer(i, vertexPrValue[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)((SkipCounter) * sizeof(float)));
      SkipCounter = SkipCounter + vertexPrValue[i];
      glEnableVertexAttribArray(i);
    }
  }

  void ShaderProgram::initialiseVertexData(const char* _ObjectFile)
  {
    readVertexData(_ObjectFile);
    setVertexData();
  }

  void ShaderProgram::draw()
  {
    glUseProgram(ID);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, verteciesCount);

    glBindVertexArray(0);
    glUseProgram(0);
  }

  void ShaderProgram::useShader()
  {
    glUseProgram(ID);
  }

  GLuint ShaderProgram::getID()
  {
    return ID;
  }

  void ShaderProgram::checkCompileErrors(GLuint shader, std::string type)
  {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      }
    }
    else
    {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success)
      {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      }
    }
  }
}