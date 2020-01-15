#ifndef OLIVERA_RESOURCE_H
#define OLIVERA_RESOURCE_H

#include <memory>
#include <string>

namespace olivera
{
	class Resource
	{
	public:
		std::string getName();
		void setName(std::string _name);
		virtual ~Resource() {}
    Resource();

	private:
		std::string name;
	};
}

#endif