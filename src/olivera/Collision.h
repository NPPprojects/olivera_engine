#include "Component.h"

#include <glm/glm.hpp>
#include <string>

/********************************************************************
VARIABLE AND FUNCTION THAT NEED RENAMING 
SetSize()
MAY WANT TO ATTACH A VERTEX BUFFER + SHADER INSTEAD OF REPEATING CODE
*********************************************************************/

namespace olivera            
{
	class Transform;

  class CurrentCamera;

  
  /**********************************************************************
  @brief Handle collision between objects with this components attached.

  *Limited to AABB, collision box is outlined using a shader.

  ***********************************************************************/
	class Collision : public Component
	{
	  public:

     /*****************************************************
     @brief Setter for the offset when colliding.
   
     @param glm::vec3 offset for calculating new position.
 
     *****************************************************/
      void setOffset(const glm::vec3& _offset);


    /************************************************
    @brief Setter for the scale of the collision box.

    @param glm::vec3 size

    *************************************************/
	    void setSize(const glm::vec3& _size);
    
    /**************************************************
    @brief Check if entities are colliding every tick.

    *If isVisable is set to true, a hard coded green 
    bounding box will appear.

    ***************************************************/
		  void onTick();

    /***************************************
     @brief Display collision boulding box.

    ****************************************/
      void onDisplay();
	
    /**********************************************************************
     @brief set up for the collision box.
   
     *Attached a collision box to the entity and if visablity is enabled 
     prepares the VBO VAO and sets ups the hardcoded shaders for use.

    ***********************************************************************/    
      void onInitialise(bool _isVisable);
   
    /**************************************************************************
    @brief check if colliding.
    *Checks for all entites with a collision component and adds it to a list 
     whenever any of the AABBs cross each other enable isColliding.

    @param bool isVisable 


    ***************************************************************************/
      void collideBox();

    /********************************************
     @brief AABB collision check

     @param glm::vec3 position of colliding box
     @param glm::vec3 size of colliding box

     @return true if colliding
    *********************************************/
		  bool isColliding(glm::vec3 _position, glm::vec3 _size);

    /***********************************************
    @brief Response whenever collision occurs.

    @param glm::vec3 position of the colliding box.
    @param glm::Vec3 size of the colliding box.

    @return The new position after colliding.

    ************************************************/
      glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size);

    /********************************************
    @brief Draws the box if isVissable is true.
  
    *********************************************/
      void DrawBox();

	  private:
    /************************************************************************************************************/
		
      /*******************************************
      @brief uniform setter for the model matrix.

      ********************************************/
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
    
    
      glm::vec3 size;                                                                //!< Size of collision box
		  glm::vec3 offset;                                                            //!< Offset of collsiion box
		  glm::vec3 lastPosition;                                      //!< Last position of the box when colliding

      glm::mat4 model;                                                  //!< mModel matrix of the collision box


		  std::weak_ptr<Core> core;                                                       //!< Weak pointer to core
		  std::weak_ptr<Entity> entitySelf;                     //!< Weak pointer to entity this is a component off
      std::weak_ptr<Transform> transform;                        //!< Weak pointer to store entitie's transform
      std::weak_ptr<CurrentCamera> cameraContext;                 //!< Weak pointer to store the current Camera

      const char *vertexShaderSource;                                        //!< Storage for the vertex shader                                              
      const char *fragmentShaderSource;                                    //!< Storage for the fragment shader                                              

      unsigned int VBO, VAO;                                  //!< Vertex Buffer Object and Vertex Array Object                                              

      int vertexShader, fragmentShader, shaderProgram;         //!< Vertex and fragment programs and the shader                                              
                                                                          //!< pProgram they will be attached to                                               

      bool isVisable;                                //!<Boolean to check if the bounding box should be visable                                              
                                                                                                    
      static constexpr float vertices[] = {
              -1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f,  1.0f, -1.0f,
              1.0f,  1.0f, -1.0f,
              -1.0f,  1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,

              -1.0f, -1.0f,  1.0f,
              1.0f, -1.0f,  1.0f,
              1.0f,  1.0f,  1.0f,
              1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,
              -1.0f, -1.0f,  1.0f,

              -1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,

              1.0f,  1.0f,  1.0f,
              1.0f,  1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f, -1.0f,  1.0f,
              1.0f,  1.0f,  1.0f,

              -1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f, -1.0f,  1.0f,
              1.0f, -1.0f,  1.0f,
              -1.0f, -1.0f,  1.0f,
              -1.0f, -1.0f, -1.0f,

              -1.0f,  1.0f, -1.0f,
              1.0f,  1.0f, -1.0f,
              1.0f,  1.0f,  1.0f,
              1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f, -1.0f,
      };                                                   
                                                                //!< Vertices of the bounding box in local space     
                                                                                                    
                                                                                                   
    /************************************************************************************************************/
	};

}