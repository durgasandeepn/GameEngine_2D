/****************************************************************
// File Name: EventManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles adding event, broadcasting, and removing events.
// This EventManager forgoes the need for an EventListener class.
****************************************************************/

#ifndef EVENT_MANAGER_INL
#define EVENT_MANAGER_INL

#include "EventManager.h"
#include "Math/UUIDGenerator.h"

/*public method function : AddListener
   @param: std::function<void(const EventType&)> callback - A function that takes the Templated EventType as a parameter
   @returns: void */
template <typename EventType>
uint32_t EventManager::AddListener(std::function<void(const EventType&)> callback) {
    uint32_t objectId = UUIDGenerator::Instance().GenerateUUID();
    auto& callbackWrappers = listeners[typeid(EventType)];
    callbackWrappers.push_back({ objectId, [callback](const Event& event) {
        // Perform a safe cast to the correct EventType
        const EventType& specificEvent = static_cast<const EventType&>(event);
        callback(specificEvent);
    } });

    return objectId;
}

template <typename EventType>
void EventManager::RemoveListener(uint32_t objectId) {
    auto it = listeners.find(typeid(EventType));
    if (it != listeners.end()) {
        auto& callbackWrappers = it->second;
        callbackWrappers.erase(
            std::remove_if(callbackWrappers.begin(), callbackWrappers.end(),
                [objectId](const CallbackWrapper& wrapper) {
                    return wrapper.objectId == objectId;
                }),
            callbackWrappers.end()
        );

        // If there are no more callbacks, remove the event type
        if (callbackWrappers.empty()) {
            listeners.erase(it);
        }
    }
}

/*public method function : BroadcastEvent
   @param: const EventType& event - A templated EventType. Will find all listeners to this event and call them using this event
   @returns: void */
template <typename EventType>
void EventManager::BroadcastEvent(const EventType& event) const {
    // Uses type_index (https://en.cppreference.com/w/cpp/types/type_index)
    // of the templated type in order to retrieve from the map
    auto it = listeners.find(std::type_index(typeid(EventType)));
    if (it != listeners.end()) {
        auto callbacks = it->second;
        for (const auto& wrapper : callbacks) {
            if (wrapper.callback) {
                wrapper.callback(event);
            }
        }
    }
}
#endif