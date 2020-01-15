
#include "Component.h"


#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
class ShaderProgram;
class VertexBuffer;
class CurrentCamera;
class Core;
class Transform;
class Texture;

class Model;
class MeshRenderer : public Component
{
public:
  void onInitialise(std::vector<std::string> _texturePaths, std::string _meshPath);
  void onInitialise(std::string _modelPath);
  void onDisplay();
  void onTick();
  void Draw();

private:


  std::vector<std::weak_ptr<Texture>> texture;
  std::weak_ptr<ShaderProgram> shader;
  std::weak_ptr<VertexBuffer> object;
  std::weak_ptr<Entity> entitySelf;
  std::weak_ptr<CurrentCamera> cameraContext;
  std::weak_ptr<Core> core;
  std::weak_ptr<Transform> transform;

  std::weak_ptr<Model> model;
};

}
