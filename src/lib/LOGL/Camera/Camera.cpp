#include <LOGL/Camera.h>

using namespace LOGL;
using namespace std;

const float Camera::YAW = -90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::ZOOM = 45.0f;

Camera::Camera(glm::vec3 position,
               glm::vec3 up,
               float rationWH,
               float yaw,
               float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM),
      FPS(false) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    RationWH = rationWH;
    updateCameraVectors();
}

/*
Camera::Camera(float posX,
               float posY,
               float posZ,
               float upX,
               float upY,
               float upZ,
               float yaw,
               float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
*/

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
    // glm::mat4 a(1), b(1);// didnot work ;c
    // a[0][0] = Right.x;
    // a[0][1] = Right.y;
    // a[0][2] = Right.z;
    // a[1][0] = Up.x;
    // a[1][1] = Up.y;
    // a[1][2] = Up.z;
    // a[2][0] = Front.x;
    // a[2][1] = Front.y;
    // a[2][2] = Front.z;
    // b[0][3] = -Position.x;
    // b[1][3] = -Position.y;
    // b[2][3] = -Position.z;
    // return a * b;
}

glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(Zoom), RationWH, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 front =
        glm::normalize(Front * (FPS ? glm::vec3(1, 0, 1) : glm::vec3(1)));
    if (direction == CAM_FORWARD)
        Position += front * velocity;
    if (direction == CAM_BACKWARD)
        Position -= front * velocity;
    if (direction == CAM_LEFT)
        Position -= Right * velocity;
    if (direction == CAM_RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset,
                                  float yoffset,
                                  GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(
        Front, WorldUp)); /* Normalize the vectors, because their length gets
                             closer to 0 the more you look up or down which
                             results in slower movement.*/
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::EnableFPS() {
    FPS = true;
}
void Camera::DisableFPS() {
    FPS = false;
}
