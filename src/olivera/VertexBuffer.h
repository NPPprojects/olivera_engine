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
/**
* class to generate a vertex array by passing in a .data file(simple shapes)
*/
	class VertexBuffer : public Resource
	{
    
	public:
 
  
    /**
    *\ constuctor calls set vertexData function
    */
    VertexBuffer(std::string _path);

    /**
    *\ reads a a .data file
    */
		void readVertexData(std::string _ObjectFile);
    
    /**
    *\ sets Vertex Data setting up the VAO
    */
		void setVertexData();
    
    /**
    *\ Getter for Vao
    */
		GLuint getVAO();
    
    /**
    *\ Getter verticiesCount
    */
		int getVerticiesCount();


	private:
		int vertexCount;///<Amount of vertecies in an object

		int attributeTypeCount;///<Counter for amount of Attributes

		int stride;///<The vertex stride

		GLuint VBO, VAO, EBO;///<Vertex Buffer Object, Vertex Array Object, Element Buffer Object

		std::ifstream vertexData;///<VertexDataFile

		std::vector<float> vertexInduvidualData;///<All vertex data

		std::vector<int> vertexAttribute;///< vertex Attibute layout number

		int totalVertexFloatCount;///<Total Vertecies Amount

    /**
    *\ Getter for XCoordinate on window
    */
		void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);
	};

}