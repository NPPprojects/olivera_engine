#include "Component.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
class ShaderProgram;

class VertexBuffer;

class Camera;

class MeshRenderer : public Component
{
public:
  void onInitialise(std::shared_ptr<ShaderProgram> _shader, std::shared_ptr<VertexBuffer> _object);
  void onInitialise(std::shared_ptr<ShaderProgram> _shader, std::shared_ptr<VertexBuffer> _object, std::shared_ptr<Camera> _camera);
  void onDisplay();
  void Draw();

private:
  std::shared_ptr<ShaderProgram> shader;
  std::shared_ptr<VertexBuffer> object;
  std::shared_ptr<Camera> camera;

  glm::mat4 view;
  glm::mat4 projection;
  glm::mat4 model;


};

}
