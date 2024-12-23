//
// Created by Romain on 22/12/2024.
//

#ifndef EVENTKEYBOARD_H
#define EVENTKEYBOARD_H

#include "Event.h"
#include "pch.h"

class KeyEvent : public Event {
   public:
    int GetKeyCode() const { return m_KeyCode; }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

   protected:
    explicit KeyEvent(const int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class KeyPressedEvent final : public KeyEvent {
   public:
    explicit KeyPressedEvent(const int keycode, const bool isRepeat = false)
        : KeyEvent(keycode), m_IsRepeat(isRepeat) {}
    ~KeyPressedEvent() override = default;

    inline bool IsRepeat() const { return m_IsRepeat; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressed: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";

        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::KeyPressed)

   private:
    bool m_IsRepeat;
};

class KeyReleasedEvent final : public KeyEvent {
   public:
    explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}
    ~KeyReleasedEvent() override = default;

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleased: " << m_KeyCode;

        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::KeyReleased)
};

#endif  // EVENTKEYBOARD_H
