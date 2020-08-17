#include "Collision.h"
#include "CurrentCamera.h"
#include "CameraContext.h"
#include "Core.h"
#include "Transform.h"
#include "Entity.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "ResourceManager.h"
#include "Resource.h"
namespace olivera
{
  void Collision::setOffset(const glm::vec3 & _offset)
  {
    offset = _offset;
  }

  void Collision::setScale(const glm::vec3 & _size)
  {
    size = _size;
  }

  void Collision::onTick()
  {
    collideBox();
    if (isVisable == true)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, transform.lock()->getPosition());
      model = glm::scale(model, size);
      shader.lock()->useShader();
      shader.lock()->setMat4("projection", cameraContext.lock()->getProjection());
      shader.lock()->setMat4("view", cameraContext.lock()->getView());
      shader.lock()->setMat4("model", model);
      glUseProgram(0);
    }
  }

  void Collision::onDisplay()
  {
    DrawBox();
  }

  void Collision::onInitialise(bool _isVisable)
  {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    entitySelf = getEntity();
    core = getCore();
    transform = entitySelf.lock()->getComponent<Transform>();
    lastPosition = transform.lock()->getPosition();
    cameraContext = core.lock()->getCameraList()->getCurrentCamera();
    isVisable = _isVisable;

    if (isVisable == true)
    {
      collisionResources = std::make_shared<ResourceManager>();
      collisionResources->create<VertexArray>(std::string("CollisionBox"), std::string("../resources/objects/CollisionBox.data"));
      collisionResources->create<ShaderProgram>(std::string("BoxShader"), std::string("../resources/shaders/CollisionBoxShader.txt"));

      mesh = collisionResources->load<VertexArray>("CollisionBox");
      shader = collisionResources->load<ShaderProgram>("BoxShader");
    }
  }


  void Collision::collideBox()
  {

    getCore()->GetEntities<Collision>(bces);
    glm::vec3 np = transform.lock()->getPosition() + offset;

    for (auto it : bces)
    {
      if (it == getEntity())
      {
        continue;
      }

      std::shared_ptr<Collision> bc = (it)->getComponent<Collision>();

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

  void Collision::DrawBox()
  { 
    if (isVisable == true)
    {
      shader.lock()->useShader();
      glBindVertexArray(mesh.lock()->getVAO());
      glDrawArrays(GL_LINES, 0, mesh.lock()->getVerticiesCount());
      glBindVertexArray(0);
      glUseProgram(0);
    } 
  }
 
}





