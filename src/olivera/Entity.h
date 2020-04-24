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
  
  /******************************************************************
  @brief Entity class that handles the creation of objects(entities) 
         to which components are added
  
  *******************************************************************/
  class Entity
  {
    friend class Core;

  public:
    /*******************************
    @brief Getter function for core

    ********************************/
      std::shared_ptr<Core> getCore();

    /**************************************************
    @brief Getter function for component within entity

    ***************************************************/
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

    /********************************************
    @brief function to add a component to entity 
    without passing parameters 
    
    *********************************************/
     template <typename T>
      std::shared_ptr<T> addComponent()
    {
      ADDCOMPONENT
        component->onInitialise();
  
      return component;
    }

    /********************************
    @brief Add a component to entity
    and pass 1 parameter

    *********************************/
    template <typename T, typename A>
      std::shared_ptr<T> addComponent(A a)
    {
      ADDCOMPONENT
        component->onInitialise(a);
 
      return component;
    }

    /********************************
    @brief Add a component to entity
    and pass 2 parameter

    *********************************/
    template <typename T, typename A, typename B>
      std::shared_ptr<T> addComponent(A a, B b)
    {
      ADDCOMPONENT
        component->onInitialise(a, b);

      return component;
    }

    /********************************
    @brief Add a component to entity
    and pass 3 parameter

    *********************************/
    template <typename T, typename A, typename B, typename C>
      std::shared_ptr<T> addComponent(A a, B b, C c)
    {
      ADDCOMPONENT
        component->onInitialise(a, b, c);

      return component;
    }

    /*******************************************************
    @brief Search for a specific component within entities 
    
    @return True if found specified component within entity
    or false if not

    ********************************************************/
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
  /********************************************************************************************************/
    
    /*****************************************
    @brief Go thorugh each component and call
    their onTick function

    ******************************************/
      void tick();

    /*****************************************
    @brief Go thorugh each component and call
    their onDisplay function

    ******************************************/
     void display();


    std::weak_ptr<Entity> self;                                                   //!< Weak pointer to self
    std::weak_ptr<Core> core;                                                     //!< Weak pointer to core
    std::vector<std::shared_ptr<Component> > components;                     //!<Vector to store components

  /********************************************************************************************************/
  };

}
