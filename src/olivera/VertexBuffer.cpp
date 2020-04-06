#include "VertexBuffer.h"

namespace olivera {
	void VertexBuffer::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
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

  VertexBuffer::VertexBuffer(std::string _path)
  {
    readVertexData(_path);
    setVertexData();
  }

  void VertexBuffer::readVertexData(std::string _ObjectFile)
	{
		std::string line;
		std::vector <std::string> Splitline;

		vertexData.open(_ObjectFile);                    //  read-Stream

		getline(vertexData, line);


		splitStringWhitespace(line, Splitline);

		attributeTypeCount = atoi(Splitline.at(0).c_str()); //Assign count of attributes

		vertexCount = atoi(Splitline.at(1).c_str());
		stride = atoi(Splitline.at(2).c_str());

		for (int i = 0; i < attributeTypeCount; i++)
		{
			vertexAttribute.push_back(i);
			vertexAttribute[i] = atoi(Splitline.at(3 + i).c_str());

		}
		vertexData >> totalVertexFloatCount;            //Total Vertex Float Count


		for (int i = 0; i < totalVertexFloatCount; i++)
		{
			vertexInduvidualData.push_back(i);
			vertexData >> vertexInduvidualData[i];
		}


		vertexData.close();
	}

	void VertexBuffer::setVertexData()
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

			glVertexAttribPointer(i, vertexAttribute[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)((SkipCounter) * sizeof(float)));
			SkipCounter = SkipCounter + vertexAttribute[i];
			glEnableVertexAttribArray(i);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	}

	GLuint VertexBuffer::getVAO()
	{
		return VAO;
	}

	int VertexBuffer::getVerticiesCount()
	{
		return vertexCount;
	}



}