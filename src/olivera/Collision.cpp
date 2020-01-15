#include "Collision.h"
#include "Core.h"
#include "Transform.h"
#include "Entity.h"

namespace olivera 
{
	void Collision::setOffset(const glm::vec3 & _offset)
	{
		offset = _offset;
	}

	void Collision::setSize(const glm::vec3 & _size)
	{
		size = _size;
	}

	void Collision::onTick()
	{
		collideBox();
	}

	void Collision::onInitialise()
	{
		size = glm::vec3(1.0f, 1.0f, 1.0f);
		entitySelf = getEntity();
		core = getCore();
		transform = entitySelf.lock()->getComponent<Transform>();
		lastPosition = transform.lock()->getPosition();
	}

	///TODO:: FIX deadass don't know what Im doing
	void Collision::collideBox()
	{
		std::vector<std::shared_ptr<Entity> > bces;
 //   getCore()->getEntities<Collision>(bces);
		///Here is where i get lost
		//getCore()->getEntities<Collision>(bces);
		//getWorld()->getEntities<Collision>(bces);
		glm::vec3 np = transform.lock()->getPosition() + offset;

		for (std::vector<std::shared_ptr<Entity> >::iterator it = bces.begin();
			it != bces.end(); it++)
		{
			if (*it == getEntity())
			{
				continue;
			}

			std::shared_ptr<Collision> bc =
				(*it)->getComponent<Collision>();

			glm::vec3 sp = bc->getCollisionResponse(np, size);
			np = sp;
			np = np - offset;
			transform.lock()->setPosition(np);
			lastPosition = np;
		}
	}

	bool Collision::isColliding(glm::vec3 _position, glm::vec3 _size)
	{
		glm::vec3 a = transform.lock()->getPosition() + offset;
		glm::vec3& as = size;
		glm::vec3& b = _position;
		glm::vec3& bs = _size;

		if (a.x > b.x) // a right of b
		{
			if (a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.x - bs.x > a.x + as.x)
			{
				return false;
			}
		}

		if (a.z > b.z) // a front of b
		{
			if (a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.z - bs.z > a.z + as.z)
			{
				return false;
			}
		}

		if (a.y > b.y) // a above b
		{
			if (a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.y - bs.y > a.y + as.y)
			{
				return false;
			}
		}

		return true;
	}
	
	glm::vec3 Collision::getCollisionResponse(glm::vec3 _position, glm::vec3 _size)
	{
		float amount = 0.1f;
		float step = 0.1f;

		while (true)
		{
			if (!isColliding(_position, _size)) break;
			_position.x += amount;
			if (!isColliding(_position, _size)) break;
			_position.x -= amount;
			_position.x -= amount;
			if (!isColliding(_position, _size)) break;
			_position.x += amount;
			_position.z += amount;
			if (!isColliding(_position, _size)) break;
			_position.z -= amount;
			_position.z -= amount;
			if (!isColliding(_position, _size)) break;
			_position.z += amount;
			_position.y += amount;
			if (!isColliding(_position, _size)) break;
			_position.y -= amount;
			_position.y -= amount;
			if (!isColliding(_position, _size)) break;
			_position.y += amount;
			amount += step;
		}

		return _position;
	}

}





