
#include "Component.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
class ShaderProgram;

class VertexBuffer;

class CurrentCamera;

class Core;

class Transform;

class MeshRenderer : public Component
{
public:
  void onInitialise();
  void onDisplay();
  void onTick();
  void Draw();

private:


  glm::mat4 view;
  glm::mat4 projection;
  glm::mat4 model;

  std::weak_ptr<ShaderProgram> shader;
  std::weak_ptr<VertexBuffer> object;
  std::weak_ptr<Entity> entitySelf;
  std::weak_ptr<CurrentCamera> cameraContext;
  std::weak_ptr<Core> core;
  std::shared_ptr<Transform> transform;
};

}
