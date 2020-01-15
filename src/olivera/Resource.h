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
		virtual ~Resource() {}
    Resource();

	private:
		std::string path;
	};
}

#endif