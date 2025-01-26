//
// Created by Romain on 22/12/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "pch.h"

class Event;

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
constexpr float CAMERA_YAW = -90.0f;
constexpr float CAMERA_PITCH = 0.0f;
constexpr float CAMERA_SPEED = 5.0f;
constexpr float CAMERA_SENSITIVITY = 0.52f;
constexpr float CAMERA_ZOOM = 45.0f;

class Camera {
   public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void Init();

    /* Getters */
    glm::mat4 GetViewMatrix() const;
    glm::vec3 GetPosition() const;

    static std::shared_ptr<Camera> Create(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                                          glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CAMERA_YAW,
                                          float pitch = CAMERA_PITCH);
    static std::shared_ptr<Camera> Create(float posX, float posY, float posZ, float upX, float upY, float upZ,
                                          float yaw, float pitch);

    void Update();
    void OnMouseEvent(const Event& event);

   private:
    void UpdateCameraVectors();

    // Camera Attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    glm::dvec2 m_LastMousePosition;
    // Euler Angles
    float m_Yaw;
    float m_Pitch;
    // Camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;

    bool m_CapturedMouse = false;
};

#endif  // CAMERA_H
