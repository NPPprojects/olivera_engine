#ifndef OLIVERA_COMPONENT_H
#define OLIVERA_COMPONENT_H

#include <memory>
/********************************************************************
ALL MEMBER VARIABLES SHOULD BE PRIVATE
*********************************************************************/


namespace olivera
{
  class  Entity;

  class  Core;

  /***********************************************************************
  @brief Base class to add components to entities.

  *Every class inheriting from component will have access to 4 virtual 
  functions, as well as methods for getting access to the engine 
  core and the entity the component belongs to

  ***********************************************************************/
  class Component
  {
    friend class Entity;

  public:
    /*************************************************
    @brief Virtual deconstructor for derived classes.

    **************************************************/
    virtual ~Component();

    /**************************************************
    @brief Getter for entity.

    @return the entity this component is attached to.
    
    ***************************************************/
    std::shared_ptr<Entity> getEntity();
    
    /************************************
    @brief Getter for the engine.

    @return the engine as a weak pointer.
    *************************************/
    std::shared_ptr<Core> getCore();


    std::weak_ptr<Entity> entity;          //!< Weak pointer to the entity the component belongs to

    bool began;                               //</ Enables/disables the component within the entity

  private:
	/************************************************************************************************/

    /*******************************************************
    @brief Virtual function for a component's initilastion.
    
    *Constructor for the component

    ********************************************************/
   virtual void onInitialise();

   /*************************************************
   @brief Virtual function for on Start Function

   **************************************************/
   virtual void onStart();

   /****************************************************
   @param Virtual function that gets called every tick 
   after the core's start function gets called.

   *****************************************************/
   virtual void onTick();

   /*******************************************************
  *\Virtual function that gets called every display call.

  *********************************************************/
   virtual void onDisplay();

  };

  /************************************************************************************************/
}

#endif