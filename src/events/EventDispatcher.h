//
// Created by Romain on 21/12/2024.
//

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Event.h"
#include "pch.h"

class EventDispatcher {
   public:
    EventDispatcher() = default;
    ~EventDispatcher();

    using Listener = std::function<void(const Event&)>;

    // Add a listener to a specific event category
    void Subscribe(EventCategory category, const Listener& listener);
    // Delete a listener to a specific event category
    void Unsubscribe(EventCategory category, const Listener& listener);
    // Push an event on the bus
    void Dispatch(Event& event);

    static std::shared_ptr<EventDispatcher> Create();

   private:
    std::unordered_map<EventCategory, std::vector<Listener>> m_Listeners;
};

#endif  // EVENTDISPATCHER_H
