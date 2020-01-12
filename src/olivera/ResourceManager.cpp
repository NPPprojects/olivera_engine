#include "ResourceManager.h"

#include "ResourceAllocator.h"
namespace olivera
{
	ResourceManager::ResourceManager()
	{
	}
	ResourceManager::~ResourceManager()
	{
	}
	void ResourceManager::addResource(std::shared_ptr<ResourceAllocator> resource, const std::string& name, const std::string& path)
	{
		resource->setResourcePath(path);
		resource->setResourceId(mResources.size());
		resource->loadResource();

		mResources.insert(std::pair<std::string, std::shared_ptr<ResourceAllocator>>(name, resource));
	}

	ResourceManager & ResourceManager::getInstance()
	{
		// TODO: insert return statement here
	}

	std::shared_ptr<ResourceManager> ResourceManager::getInstancePtr()
	{
		return std::shared_ptr<ResourceManager>();
	}


}