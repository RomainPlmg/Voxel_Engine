//
// Created by Romain on 22/12/2024.
//

#include "Input.h"

#include "Application.h"
#include "Window.h"
#include "gfx/GraphicContext.h"

bool Input::IsKeyPressed(const int keycode) {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    return (state[keycode] != 0);
}

bool Input::IsMouseButtonPressed(const int button) {
    const Uint32 state = SDL_GetMouseState(nullptr, nullptr);

    if (button == SDL_BUTTON_LEFT) {
        return (state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    } else if (button == SDL_BUTTON_RIGHT) {
        return (state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
    } else if (button == SDL_BUTTON_MIDDLE) {
        return (state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
    }

    return false;
}

glm::dvec2 Input::GetMousePosition() {
    glm::ivec2 position;
    SDL_GetMouseState(&position.x, &position.y);
    return position;
}

void Input::SetMousePosition(double x, double y) {
    const auto window = Application::GetInstance()->GetWindow()->GetHandler();
    SDL_WarpMouseInWindow(window, x, y);
}
