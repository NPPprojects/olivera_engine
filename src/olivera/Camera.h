#include "glm/glm.hpp"
#include <GL/glew.h>
#include "Component.h"

namespace olivera
{

  class Camera : public Component
  {
  public:
    enum CameraMovement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
    };
    void updateCameraVectors();

    Camera();
    ~Camera();

    void ProcessMouseScroll(float _yoffset);
    void ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch = true);
    void ProcessKeyboard(CameraMovement _direction, float _deltaTim);
    glm::mat4 GetViewMatrix();
    float getZoom() const;
    glm::vec3 GetPosition();
    int getYaw();
    int getPitch();
    void onInitialise();

  private:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    float YAW = -90.0f;
    float PITCH = 0.0f;
    float SPEED = 2.5f;
    float SENSITIVITY = 0.1f;
    float ZOOM = 45.0f;


  };

}