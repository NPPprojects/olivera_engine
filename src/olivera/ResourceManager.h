
#include "Resource.h"

#include <string>
#include <memory>
#include <vector>



namespace olivera
{
  /**
  * Resource Manager class to create/store/load resources
  */
  class ResourceManager
  {
  public:

  /**
  *\ Load a resource from the resources vector by finding it using its name tag
  */
    template <typename T>
	std::shared_ptr<T> load(std::string _name)
    {
		std::shared_ptr<T> rtn;
		for (std::vector<std::shared_ptr<Resource>>::iterator i = resources.begin(); i != resources.end(); ++i)
		{
		
			if ((*i)->getName() == _name)
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

  /**
  *\ Create a resource by calling its constuctor and then giving it a name tag to find it within the resource vector
  */
    template <typename T>
    std::shared_ptr<T> create(const std::string& _name, std::string &_path)
    {
		std::shared_ptr<T> resource = std::make_shared<T>(_path);
		resource->setName(_name);
		resources.push_back(resource);
		return resource;
    }

  /**
  *\ Getter for resources vector
  */
    std::vector<std::shared_ptr<Resource>> getResources();

  private:
    std::vector<std::shared_ptr<Resource>> resources;///< Resources vector that holds all objects derived from the Resource class

  };
}