#include "ResourceAllocator.h"


	namespace olivera
	{
		ResourceAllocator::ResourceAllocator()
		{
		}
		ResourceAllocator::~ResourceAllocator()
		{

		}

		void ResourceAllocator::setResourceId(unsigned id)
		{
			mResourceId = id;
		}

		unsigned ResourceAllocator::getResourceId() const
		{
			return mResourceId;
		}

		void ResourceAllocator::setResourcePath(const std::string & path)
		{
			mResourcePath = path;
		}

		std::string ResourceAllocator::getResourcePath() const
		{
			return std::string();
		}


	}
