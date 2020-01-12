#include "Component.h"

#include <string>
#include <map>
#include <memory>

namespace olivera
{

	class ResourceAllocator;



	class ResourceManager : public Component
	{

		
	public:
		ResourceManager();
		virtual ~ResourceManager();

		void addResource(std::shared_ptr<ResourceAllocator> resource, const std::string& name, const std::string& path);

		template <typename T>
		T* getResource(const std::string& name) {
			return dynamic_cast<T*>(mResources.find(name)->second);
		}

		static ResourceManager& getInstance();
		static std::shared_ptr<ResourceManager> getInstancePtr();

	private:
		std::map<std::string, std::shared_ptr<ResourceAllocator>> mResources;

	};
}