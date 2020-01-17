#include "Component.h"

#include <glm/glm.hpp>


namespace olivera
{
	class Transform;
	
  /**
  *Component derived class to handle collision between entities
  */
	class Collision : public Component
	{
	public:

   /**
  *\ setter for offset
  */
		void setOffset(const glm::vec3& _offset);
  /**
  *\ setter for size
  */
		void setSize(const glm::vec3& _size);
    
  /**
  *\ Check if entities with collision objects are colliding every tick by calling collideBox 
  */
		void onTick();
	
  /**
  *\ setup when initalising
  */
    void onInitialise();
   
  /**
  *\ check if colliding
  */
    void collideBox();

  /**
  *\ AABB collision check
  */
		bool isColliding(glm::vec3 _position, glm::vec3 _size);
	
  /**
  *\ response whenever collision occurs which is moving the object
  */
    glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size);

	private:
		glm::vec3 size;///<size of collision box
		glm::vec3 offset;///< offset of collsiion box
		glm::vec3 lastPosition;///< stores last position
	
		std::weak_ptr<Core> core; ///< weak pointer to core
		std::weak_ptr<Transform> transform; ///< weak pointer to store entitie's transform
		std::weak_ptr<Entity> entitySelf; ///<weak pointer to point to the entity this component belongs to 
	};


}