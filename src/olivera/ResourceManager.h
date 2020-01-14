
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
    void load(std::string _path)
    {
       resources.emplace_back(std::make_shared<T>(_path));
    }

    template <typename T>
    std::shared_ptr<T> create()
    {
      std::shared_ptr<T> resource = std::make_shared<T>();
      resources.push_back(resource);
      return resource;
    }

    std::vector<std::shared_ptr<Resource>> getResources();

  private:
    std::vector<std::shared_ptr<Resource>> resources;

  };
}