//
// Created by Romain on 21/12/2024.
//

#ifndef EVENT_H
#define EVENT_H

enum class EventType {
    None = 0,

    /* Window events */
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,

    /* Application events*/
    AppTick,
    AppUpdate,
    AppRender,

    /* Keyboard events */
    KeyPressed,
    KeyReleased,
    KeyTyped,

    /* Mouse events */
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

/* Use of bit shift operations because an event can be in multiple categories */
enum EventCategory {
    None = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryMouseButton = 1 << 4,
    EventCategoryAll = EventCategoryApplication | EventCategoryInput | EventCategoryKeyboard | EventCategoryMouse |
                       EventCategoryMouseButton
};

#define EVENT_CLASS_TYPE(type)                                  \
    virtual EventType GetType() const override { return type; } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

#define BIND_EVENT_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

/* Pure virtual class, will be inherited by all the sub event classes */
class Event {
   public:
    Event() = default;
    virtual ~Event() = default;

    [[nodiscard]] virtual int GetCategoryFlags() const = 0;

    [[nodiscard]] virtual EventType GetType() const = 0;

    [[nodiscard]] virtual const char* GetName() const = 0;

    [[nodiscard]] virtual std::string ToString() const = 0;

    [[nodiscard]] inline bool IsInCategory(const EventCategory& category) const {
        return GetCategoryFlags() & category;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
};

#endif  // EVENT_H
