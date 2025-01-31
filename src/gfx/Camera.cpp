//
// Created by Romain on 22/12/2024.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GraphicContext.h"
#include "core/Application.h"
#include "core/Input.h"
#include "core/Window.h"
#include "events/Event.h"
#include "events/EventDispatcher.h"
#include "events/EventMouse.h"
#include "utils/Log.h"
#include "utils/Time.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    m_Position = position;
    m_WorldUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_MovementSpeed = CAMERA_SPEED;
    m_MouseSensitivity = CAMERA_SENSITIVITY;
    m_Zoom = CAMERA_ZOOM;

    UpdateCameraVectors();
}

Camera::Camera(const float posX, const float posY, const float posZ, const float upX, const float upY, const float upZ,
               const float yaw, const float pitch) {
    m_Position = glm::vec3(posX, posY, posZ);
    m_WorldUp = glm::vec3(upX, upY, upZ);
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_MovementSpeed = CAMERA_SPEED;
    m_MouseSensitivity = CAMERA_SENSITIVITY;
    m_Zoom = CAMERA_ZOOM;

    UpdateCameraVectors();
}

void Camera::Init() {
    Application::GetInstance()->GetWindow()->GetEventDispatcher()->Subscribe(EventCategoryMouse,
                                                                             BIND_EVENT_FN(Camera::OnMouseEvent));

    m_LastMousePosition = Input::GetMousePosition();
}

glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }

glm::vec3 Camera::GetPosition() const { return m_Position; }

std::shared_ptr<Camera> Camera::Create(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    return std::make_shared<Camera>(position, up, yaw, pitch);
}

std::shared_ptr<Camera> Camera::Create(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
                                       float pitch) {
    return std::make_shared<Camera>(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
}

void Camera::Update() {
    const float velocity = m_MovementSpeed * Time::GetDeltaTime();

    // Project m_Front & m_Right on the XZ plan
    glm::vec3 frontXZ = glm::normalize(glm::vec3(m_Front.x, 0.0f, m_Front.z));
    glm::vec3 rightXZ = glm::normalize(glm::vec3(m_Right.x, 0.0f, m_Right.z));

    if (Input::IsKeyPressed(GLFW_KEY_W)) m_Position += frontXZ * velocity;
    if (Input::IsKeyPressed(GLFW_KEY_S)) m_Position -= frontXZ * velocity;
    if (Input::IsKeyPressed(GLFW_KEY_A)) m_Position -= rightXZ * velocity;
    if (Input::IsKeyPressed(GLFW_KEY_D)) m_Position += rightXZ * velocity;
    if (Input::IsKeyPressed(GLFW_KEY_SPACE)) m_Position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) m_Position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
}

void Camera::OnMouseEvent(const Event& event) {
    auto window = Application::GetInstance()->GetWindow();

    if (event.GetType() == EventType::MouseButtonPressed) {
        // m_CapturedMouse = true;
        // Input::SetMousePosition(m_LastMousePosition.x, m_LastMousePosition.y);
        // glfwSetInputMode(window->GetHandler(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (event.GetType() == EventType::MouseButtonReleased) {
        // m_CapturedMouse = false;
        // glfwSetInputMode(window->GetHandler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (event.GetType() == EventType::MouseMoved) {
        const auto mouseEvent = dynamic_cast<const MouseMotionEvent*>(&event);
        double xOffset = m_LastMousePosition.x - mouseEvent->posX;
        double yOffset = m_LastMousePosition.y - mouseEvent->posY;

        // if (!m_CapturedMouse) {
        //     return;
        // }

        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        m_Yaw -= xOffset;
        m_Pitch += yOffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;

        // Update Front, Right and Up Vectors using the updated Euler angles
        UpdateCameraVectors();

        m_LastMousePosition.x = mouseEvent->posX;
        m_LastMousePosition.y = mouseEvent->posY;
    }
}

void Camera::UpdateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    m_Right = glm::normalize(
        glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you
                                          // look up or down which results in slower movement.
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
