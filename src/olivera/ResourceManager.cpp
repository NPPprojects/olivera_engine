#include "ResourceManager.h"

#include "ResourceAllocator.h"
namespace olivera
{
	
	void ResourceManager::addResource(std::shared_ptr<ResourceAllocator> resource, const std::string& name, const std::string& path)
	{
		resource->setResourcePath(path);
		resource->setResourceId(mResources.size());
		resource->loadResource();

		mResources.insert(std::pair<std::string, std::shared_ptr<ResourceAllocator>>(name, resource));
	}


}