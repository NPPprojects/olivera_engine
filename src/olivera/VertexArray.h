#include <GL/glew.h>
#include <glm/glm.hpp>


#include "Resource.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace olivera
{
/**********************************************************************************
@brief class to generate a vertex array by passing in a .data file(simple shapes)

***********************************************************************************/
	class VertexArray : public Resource
	{   
	  public:
 
    /***********************************************
    @brief Constuctor calls set vertexData function

    @param string filePath

    ************************************************/
      VertexArray(std::string _path);

    /**********************************
    @brief reads a .data file

    @param string filePath

    **********************************/
		  void readVertexData(std::string _ObjectFile);
    
    /******************************************
    @brief sets Vertex Data setting up the VAO
    
    *******************************************/
		  void setVertexData();
    
    /**********************
    @brief Getter for VAO

    return GLuint VAO

    ***********************/
		  GLuint getVAO();
    
    /*************************************
    @brief getter for the verticies count 
    in a .data file 

    **************************************/
		  int getVerticiesCount();


	  private:
    /************************************************************************************************************************************/

      /******************************************
      @brief Removes white spaces in text files

      *******************************************/
        void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);

	    int vertexCount;                                                                              //!<Amount of vertecies in an object
	    int attributeTypeCount;                                                                //!<Counter for amount of vertex attributes
	    int stride;                                                                                                  //!<The vertex stride

      GLuint VBO;                                                                                              //!< Vertex Buffer Object
      GLuint VAO;                                                                                               //!< Vertex Array Object
      GLuint EBO;                                                                                             //!< Element Buffer Object

	    std::ifstream vertexData;                                                                                    //!<vertex .data file

	    std::vector<float> vertexInduvidualData;                                                                       //!<All vertex data

	    std::vector<int> vertexAttribute;                                                               //!< vertex Attibute layout number

	    int totalVertexFloatCount;                                                                              //!<Total Vertecies Amount

  /**************************************************************************************************************************************/
	};

}