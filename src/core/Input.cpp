//
// Created by Romain on 22/12/2024.
//

#include "Input.h"

#include "Application.h"
#include "Window.h"
#include "gfx/GraphicContext.h"

bool Input::IsKeyPressed(const int keycode) {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();

    const auto state = glfwGetKey(window, keycode);
    return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressed(const int button) {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();

    const auto state = glfwGetMouseButton(window, button);
    return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

glm::dvec2 Input::GetMousePosition() {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();

    glm::dvec2 position;
    glfwGetCursorPos(window, &position.x, &position.y);

    return position;
}

void Input::SetMousePosition(double x, double y) {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();
    glfwSetCursorPos(window, x, y);
}
