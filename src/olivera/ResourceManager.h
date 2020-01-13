
#include "Resource.h"

#include <string>
#include <memory>
#include <vector>


namespace olivera
{
	class ResourceManager
	{
	public:
		template <typename T>
		std::shared_ptr<T> load(std::string _path);

		template <typename T>
		std::shared_ptr<T> create();
		std::vector<std::shared_ptr<Resource>> getResources();

	private:
		std::vector<std::shared_ptr<Resource>> resources;

	};
	template<typename T>
	std::shared_ptr<T> ResourceManager::load(std::string _path)
	{
		std::shared_ptr<T> resource = std::make_shared<T>();
	}

	template<typename T>
	inline std::shared_ptr<T> ResourceManager::create()
	{
		std::shared_ptr<T> resource = std::make_shared<T>();
		resources.push_back(resource);
		return resource;
		
	}
}