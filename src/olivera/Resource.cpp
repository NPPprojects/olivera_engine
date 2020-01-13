#include "Resource.h"


	namespace olivera
	{
		std::string Resource::getPath()
		{
			return path;
		}
		
		void Resource::setPath(std::string _path)
		{
			path = _path;
		}
		
	}
