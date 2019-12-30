#include "Component.h"

#include <memory>
#include<vector>


#define ADDCOMPONENT \
  std::shared_ptr<T> component = std::make_shared<T>(); \
  component->entity = self; \
  component->began = false; \
  components.push_back(component);

namespace olivera
{
  class  Core;

  class Entity
  {
    friend class Core;

  public:
    std::shared_ptr<Core> getCore();

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

    template <typename T>
    std::shared_ptr<T> addComponent()
    {
      ADDCOMPONENT
        component->onInitialise();
  
      return component;
    }

    template <typename T, typename A>
    std::shared_ptr<T> addComponent(A a)
    {
      ADDCOMPONENT
        component->onInitialise(a);
 
      return component;
    }

    template <typename T, typename A, typename B>
    std::shared_ptr<T> addComponent(A a, B b)
    {
      ADDCOMPONENT
        component->onInitialise(a, b);

      return component;
    }

  private:
    std::weak_ptr<Entity> self;
    std::weak_ptr<Core> core;
    std::vector<std::shared_ptr<Component> > components;

    void tick();
    void display();




  };

}
