
#include "Resource.h"

#include <string>
#include <memory>
#include <vector>



namespace olivera
{
  /************************************************************
  @brief Resource Manager class to create/store/load resources
  
  *************************************************************/
  class ResourceManager
  {
    public:

      /**********************************************************************************
      @brief Load a resource from the resources vector by finding it using its name tag.
  
      @param std::string name of resource

      ***********************************************************************************/
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

      /********************************************************************************
      @brief Create a resource by calling its constuctor and then giving it a name tag 
      to find it within the resource vector.
  
      @param const std::string &name defined by user
      @param std::string & path to resource

      *********************************************************************************/
        template <typename T>
        std::shared_ptr<T> create(const std::string& _name, std::string &_path)
        {
		    std::shared_ptr<T> resource = std::make_shared<T>(_path);
		    resource->setName(_name);
		    resources.push_back(resource);
		    return resource;
        }

      /****************************
      @brief Getter for resources

      *****************************/
        std::vector<std::shared_ptr<Resource>> getResources();

    private:
    /**************************************************************************************************************************************/

      std::vector<std::shared_ptr<Resource>> resources;        //!< Resources vector that holds all objects derived from the Resource class

    /**************************************************************************************************************************************/

  };
}