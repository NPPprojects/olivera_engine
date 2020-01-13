#include "ResourceManager.h"


namespace olivera
{



	std::vector<std::shared_ptr<Resource>> ResourceManager::getResources()
	{
		return resources;
	}

}