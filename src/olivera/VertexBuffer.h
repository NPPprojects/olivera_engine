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
	class VertexBuffer : public Resource
	{
    
	public:
    VertexBuffer() {}
    VertexBuffer(std::string _path);

		void readVertexData(std::string _ObjectFile);
		void setVertexData();
		GLuint getVAO();
		int getVerticiesCount();
		void onInitialise(std::string _ObjectFile);

	private:
		int vertexCount; //Amount of vertecies in an object
		int attributeTypeCount; //Counter for amount of Attributes
		int stride;     //The stride
		GLuint VBO, VAO, EBO; //Vertex Buffer Object, Vertex Array Object, Element Buffer Object
		std::ifstream vertexData; //VertexDataFile
		std::vector<float> vertexInduvidualData; //All vertex data
		std::vector<int> vertexAttribute; //Layout number
		int totalVertexFloatCount;       //Total Vertex Amount

		void splitStringWhitespace(std::string&, std::vector<std::string>&);
	};
}