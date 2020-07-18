#include "Resource.h"


	namespace olivera
	{
		std::string Resource::getName()
		{
			return name;
		}
		
		void Resource::setName(std::string _name)
		{
      name = _name;
		}
		
    std::string Resource::getPath()
    {
      return path;
    }

    void Resource::setPath(std::string _path)
    {
      path = _path;
    }
	}
