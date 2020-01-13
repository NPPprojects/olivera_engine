#ifndef OLIVERA_RESOURCE_H
#define OLIVERA_RESOURCE_H

#include <memory>
#include <string>

namespace olivera
{
	class Resource
	{
	public:
		std::string getPath();
		void setPath(std::string _path);
		
		int n=10;
		int getInt()
		{
			return n;
		}

	private:
		std::string path;
	};
}

#endif