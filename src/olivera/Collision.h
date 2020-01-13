#include "Component.h"

#include <glm/glm.hpp>


namespace olivera
{
	class Transform;
	

	class Collision : public Component
	{
	public:

		void setOffset(const glm::vec3& _offset);
		void setSize(const glm::vec3& _size);

		void onTick();
		void onInitialise();
		void collideBox();

		bool isColliding(glm::vec3 _position, glm::vec3 _size);
		glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size);

	private:
		glm::vec3 size;
		glm::vec3 offset;
		glm::vec3 lastPosition;
	
		std::weak_ptr<Core> core;
		std::weak_ptr<Transform> transform;
		std::weak_ptr<Entity> entitySelf;
	};


}