#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace olivera 
{
  /*****************************************************************
  @brief Component class to hold transformation logic for entities 

  *******************************************************************/
  class Transform : public Component
  {
    public:
  
    /**
    @brief Getter for the model matrix of an entity

    @return mat4 model;
    */
      glm::mat4 getModel();
  
    /************************************************
    @brief Update the model matrix with the last set 
    position, rotation and scale vectors

    *************************************************/
	    void updateModel();
  
    /***************************************
    *@brief Setter for the position vector
  
    @param vec3 Position

    ****************************************/
	    void setPosition(glm::vec3 _position);
	
    /**************************************
    @brief setter for the rotation vector
  
    @param vec3 Rotation

    ***************************************/
      void setRotation(glm::vec3 _rotation);
  
    /**************************************
    @brief setter for the scale vector
  
    @param vec3 Scale

    ***************************************/
      void setScale(glm::vec3 _scale);

    /**************************************
    @brief Getter for the position vector

    @return entity's position

    ***************************************/
      glm::vec3 getPosition();

    /**************************************
    @brief Getter for the rotation vector

    @return entity's rotation

    ***************************************/
      glm::vec3 getRotation();
	
    /**************************************
    @brief Getter for the scale vector

    @return entity's scale

    ***************************************/
      glm::vec3 getScale();

    /**************************************
    @brief UpdateModel is called every tick

    ***************************************/
      void onTick();


      /***********************
      @brief Getter for front

      ************************/
      glm::vec3 getFront();
      
      /*************************
      @brief Getter for worldUp

      **************************/
      glm::vec3 getWorldUp();

      /*****************************
      @brief Setter for front

      @param glm:vec3 updated front

      ******************************/
      void setFront(glm::vec3 _front);

  
	
    /*********************************************
    @brief Initalisation transform component with
    default values.

    **********************************************/
      void onInitialise();
  
    private:  
    /***********************************************************************************************/

      glm::vec3 position;                                                    //!< Position of Entity
      glm::vec3 rotation;                                                    //!< Rotation of Entity
      glm::vec3 scale;                                                          //!< Scale of Entity
      glm::vec3 front;                                                          //!< Front of Entity

      glm::vec3 worldUp;                                                      //!< Up in World Space
                                                                                                                                                                                                                    
      glm::mat4 model;                                                    //!<Model Matrix of Entity
    

    /***********************************************************************************************/
  };

}
