#include "Component.h"

#include <memory>
#include <vector>


#define ADDCOMPONENT \
  std::shared_ptr<T> component = std::make_shared<T>(); \
  component->entity = self; \
  component->began = false; \
  components.push_back(component);

namespace olivera
{
  class  Core;
  
  /**
  *Entity class that handles the creation of objects(entities) to which components are added
  */
  class Entity
  {
    friend class Core;

  public:
    /**
    *\ Getter function for core
    */
    std::shared_ptr<Core> getCore();

    /**
    *\ Getter function for component within entity
    */
    template <typename T>
    std::shared_ptr<T> getComponent()
    {
      for (size_t i = 0; i < components.size(); i++)
      {
        std::shared_ptr<T> tst = std::dynamic_pointer_cast<T>(components.at(i));

        if (tst)
        {
          return tst;
        }
      }

      throw std::exception();
    }

    /**
    *\ function to add a component to entity without passing parameters 
    */
    template <typename T>
    std::shared_ptr<T> addComponent()
    {
      ADDCOMPONENT
        component->onInitialise();
  
      return component;
    }
    /**
    *\ function to add a component to entity and passing 1 parameter
    */
    template <typename T, typename A>
    std::shared_ptr<T> addComponent(A a)
    {
      ADDCOMPONENT
        component->onInitialise(a);
 
      return component;
    }

    /**
    *\ function to add a component to entity and passing 2 parameters
    */
    template <typename T, typename A, typename B>
    std::shared_ptr<T> addComponent(A a, B b)
    {
      ADDCOMPONENT
        component->onInitialise(a, b);

      return component;
    }
    /**
    *\ function to add a component to entity and passing 3 parameters
    */
    template <typename T, typename A, typename B, typename C>
    std::shared_ptr<T> addComponent(A a, B b, C c)
    {
      ADDCOMPONENT
        component->onInitialise(a, b, c);

      return component;
    }

    /**
    *\ function to search for a specific component within entities and return true if found or false if not
    */
    template<typename T>
    bool checkForComponent()
    {
      for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
      {
        std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*it);

        if (rtn)
        {
          return true;
        }
      }

      return false;
    }
  private:
    std::weak_ptr<Entity> self;///< weak pointer to self
    std::weak_ptr<Core> core;///< weak pointer to core
    std::vector<std::shared_ptr<Component> > components; ///<vector to store components

    /**
    *\ function to go thorugh each component and then call their onTick function
    */
    void tick();

    /**
  *\ function to go thorugh each component and then call their onDisplay function
  */
    void display();




  };

}
