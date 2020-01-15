
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
	std::shared_ptr<T> load(std::string _path)
    {
		std::shared_ptr<T> rtn;
		for (std::vector<std::shared_ptr<Resource>>::iterator i = resources.begin(); i != resources.end(); ++i)
		{
		
			if ((*i)->getPath() == _path)
			{
				rtn = std::dynamic_pointer_cast<T>(*i);
				if (rtn)
				{
          return rtn;
				}
			}
		}
		throw std::exception();
    return nullptr;
    }

    template <typename T>
    std::shared_ptr<T> create(const std::string& _name, std::string &_path)
    {
		std::shared_ptr<T> resource = std::make_shared<T>(_path);
		resource->setPath(_name);
		resources.push_back(resource);
		return resource;
    }

    std::vector<std::shared_ptr<Resource>> getResources();

  private:
    std::vector<std::shared_ptr<Resource>> resources;

  };
}