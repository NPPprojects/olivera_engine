#include "Camera.h"
#include "Core.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace olivera
{
  Camera::Camera()
  {
  }


  Camera::~Camera()
  {
  }

  glm::mat4 Camera::GetViewMatrix()
  {
    return glm::lookAt(Position, Position + Front, Up);
  }
  void Camera::ProcessKeyboard(CameraMovement _direction, float _deltaTime)
  {
    float velocity = MovementSpeed * _deltaTime;
    if (_direction == FORWARD)
      Position += Front * velocity;
    if (_direction == BACKWARD)
      Position -= Front * velocity;
    if (_direction == LEFT)
      Position -= Right * velocity;
    if (_direction == RIGHT)
      Position += Right * velocity;
  }
  void Camera::ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch)
  {
    _xoffset *= MouseSensitivity;
    _yoffset *= MouseSensitivity;

    Yaw += _xoffset;
    Pitch += _yoffset;

    // when pitch is out of bounds, screen doesn't get flipped
    if (_constrainPitch)
    {
      if (Pitch > 89.0f)
        Pitch = 89.0f;
      if (Pitch < -89.0f)
        Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
  }


  void Camera::ProcessMouseScroll(float _yoffset)
  {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
      Zoom -= _yoffset;
    if (Zoom <= 1.0f)
      Zoom = 1.0f;
    if (Zoom >= 45.0f)
      Zoom = 45.0f;
  }
  void Camera::updateCameraVectors()
  {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
  }

  float Camera::getZoom() const
  {
    return Zoom;
  }

  glm::vec3 Camera::GetPosition()
  {
    return Position;
  }

  int Camera::getYaw()
  {
    return Yaw;
  }
  int Camera::getPitch()
  {
    return Pitch;
  }

  void Camera::onInitialise()
  {
    Position = glm::vec3(0.0f, 0.0f, 3.0f);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;
    Front = (glm::vec3(1.0f, 0.0f, -1.0f));
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;
    updateCameraVectors();
    core = getCore();
  }

  void Camera::OnTick()
  {
    cameraContext = core->getCurrentCamera();
  }


}