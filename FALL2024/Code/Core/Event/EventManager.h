/****************************************************************
// File Name: EventManager
// © 2025 DigiPen (USA) Corporation
// Authors: Mariojulio Alvarez - base code, Alex Humphries - upgrades and refactors
// Description: Handles adding event, broadcasting, and removing events.
// This EventManager forgoes the need for an EventListener class.
****************************************************************/

#pragma once
#include "precompiled.h"
#include "Event.h"

struct CallbackWrapper {
	uint32_t objectId; // Object identifier
	std::function<void(const Event&)> callback; // Actual callback function
};

class EventManager
{
public:
	static EventManager& Instance() {
		static EventManager instance;
		return instance;
	}
	~EventManager() = default;

	/**
	* @brief Adds a listener callback to the listeners map
	* 
	* Usage -> AddListener<{Custom}Event>(
	*	[](const {Custom}Event& event){
	*		... Custom lambda using event data ...
	*	}
	* )
	* @param callback - a function that takes in a templated EventType as a parameter.
	* @return void
	*/
	template <typename EventType>
	uint32_t AddListener(std::function<void(const EventType&)> callback);

	template <typename EventType>
	void RemoveListener(uint32_t objectId);
	/**
	* @brief Broadcasts all events of given EventType to their listeners
	* @param event - Type of event to broadast
	* @return void
	*/
	template <typename EventType>
	void BroadcastEvent(const EventType& event) const;

	/**
	* @brief Clears all event listeners for each event type in the listeners map.
	* @return void
	*/
	void FlushEvents() {
		for (auto& [type, callbacks] : listeners) {
			callbacks.clear();
		}
		listeners.clear();
	}

	/**
	* @brief Removes an event type from the listeners map (should remove all callbacks too)
	* @return void
	*/
	template <typename EventType>
	void RemoveListenersForType() {
		listeners.erase(typeid(EventType));
	}

	size_t GetActiveListenerCount() const {
		size_t count = 0;
		for (const auto& [type, callbacks] : listeners) {
			count += callbacks.size();
		}
		return count;
	}
private:
	// Maps a templated "EventType" index to a vector of functions to execute when that event type is broadcast.
	std::unordered_map<std::type_index, std::vector<CallbackWrapper>> listeners;


	EventManager()=default;
};

#include "EventManager.hpp"