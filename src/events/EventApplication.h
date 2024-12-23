//
// Created by Romain on 21/12/2024.
//

#ifndef EVENTAPPLICATION_H
#define EVENTAPPLICATION_H

#include "Event.h"
#include "pch.h"

class ApplicationEvent : public Event {
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent final : public ApplicationEvent {
   public:
    int width, height;

    WindowResizeEvent(const int width, const int height) : width(width), height(height) {}

    EVENT_CLASS_TYPE(EventType::WindowResize)

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "Window resized to: " << width << "x" << height;
        return ss.str();
    }
};

class WindowCloseEvent final : public ApplicationEvent {
   public:
    EVENT_CLASS_TYPE(EventType::WindowClose)

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "Window closed";
        return ss.str();
    }
};

class WindowMovedEvent final : public ApplicationEvent {
   public:
    int xpos, ypos;

    WindowMovedEvent(const int xpos, const int ypos) : xpos(xpos), ypos(ypos) {}

    EVENT_CLASS_TYPE(EventType::WindowMoved)

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "Window moved at: x=" << xpos << " | y=" << ypos;
        return ss.str();
    }
};

#endif  // EVENTAPPLICATION_H
