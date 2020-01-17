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
* Class to generate Vertex Array by passing user defined objects from a text file
*/
	class VertexBuffer : public Resource
	{
    
	public:
    /**
    *\ Getter for XCoordinate on window
    */
    VertexBuffer() {}

    /**
    *\ Getter for XCoordinate on window
    */
    VertexBuffer(std::string _path);

    /**
    *\ Getter for XCoordinate on window
    */
		void readVertexData(std::string _ObjectFile);
    
    /**
    *\ Getter for XCoordinate on window
    */
		void setVertexData();
    
    /**
    *\ Getter for XCoordinate on window
    */
		GLuint getVAO();
    
    /**
    *\ Getter for XCoordinate on window
    */
		int getVerticiesCount();

    /**
    *\ Getter for XCoordinate on window
    */
		void onInitialise(std::string _ObjectFile);

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
		void splitStringWhitespace(std::string&, std::vector<std::string>&);
	};

}