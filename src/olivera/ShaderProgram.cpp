#include "ShaderProgram.h"

namespace olivera
{
  void ShaderProgram::loadShaderProgram(std::string _path)
  {
    std::string vertPath;
    std::string fragPath;


    
    std::ifstream file(_path);
    if (!file.is_open())
    {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    else
    {
      std::string line;
      std::getline(file, line);
      vertPath += line;
      std::getline(file, line);
      fragPath += line;
    }
    file.close();

    std::string vertexCode;
    std::string fragmentCode;
    
    file.open(vertPath);
    if (!file.is_open())
    {
      std::cout << "ERROR::SHADER.VERT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    else
    {
      while (!file.eof())
      {
        std::string line;
        std::getline(file, line);
        vertexCode += line + "\n";
      }
    }
    file.close();

    file.open(fragPath);

    if (!file.is_open())
    {
      std::cout << "ERROR::SHADER.FRAG::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    else
    {
      while (!file.eof())
      {
        std::string line;
        std::getline(file, line);
        fragmentCode += line + "\n";
      }
    }
    file.close();

    // 1. retrieve the vertex/fragment source code from filePath
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  
    try
    {
      // open files
      vShaderFile.open(vertexCode);
      fShaderFile.open(fragmentCode);
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
      
    }
    catch (std::ifstream::failure e)
    {
    //  std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
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
   
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
   
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    //Reset shader state
    glUseProgram(0);
  }

   ShaderProgram::ShaderProgram(std::string _path)
  {
    loadShaderProgram(_path);
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