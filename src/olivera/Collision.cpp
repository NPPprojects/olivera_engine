#include "Collision.h"
#include "CurrentCamera.h"
#include "CameraContext.h"
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
    if (isVisable == true)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, transform.lock()->getPosition());
      model = glm::scale(model, size);
      glUseProgram(shaderProgram);
      setMat4("projection", cameraContext.lock()->getProjection());
      setMat4("view", cameraContext.lock()->getView());
      setMat4("model", model);
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
      //GLSL code for the vertex shader
      vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model *vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

      //GLSL code for the fragment shader
      fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";
      //build the vertex shader pgoram
      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      glCompileShader(vertexShader);

      fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
      glCompileShader(fragmentShader);

      // link shaders
      shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
      glLinkProgram(shaderProgram);

      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);



      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);

      glBindVertexArray(VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }


  void Collision::collideBox()
  {
    std::vector<std::shared_ptr<Entity> > bces;
    getCore()->GetEntities<Collision>(bces);
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

  void Collision::DrawBox()
  { 
    if (isVisable == true)
    {
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_LINES, 0, 36);
      glBindVertexArray(0);
      glUseProgram(0);
    } 
  }

  void Collision::setMat4(const std::string & name, const glm::mat4 & mat) const
  {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }


 
}





