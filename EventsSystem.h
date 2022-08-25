#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "RangeTree.h"

using EventId = int;
using EventTypeId = int;

class Event;

struct Size {
	int width;
	int height;
};

class EventsTree {
private:
	RangeTree < 
		RangeTree < 
			std::unordered_map < EventTypeId, std::shared_ptr <Event> >
		> 
	> m_tree;
	Size m_windowSize;
public:
	EventsTree(Size windowSize) {
		m_windowSize = windowSize;
		m_tree = RangeTree < 
			RangeTree < 
				std::unordered_map <
					EventTypeId, std::shared_ptr <Event> 
				> 
			> 
		> (
			windowSize.width, 
			RangeTree < 
					std::unordered_map < 
						EventTypeId, 
						std::shared_ptr <Event>
					> 
			>(windowSize.height)
		);
	}
	void addEvent (Point2d pos, EventTypeId typeId, std::shared_ptr <Event> event) {
		auto yTree = m_tree.find(pos.x);
		auto location = yTree->find(pos.y);
		if (location == yTree->end()) {
			yTree->insert(
				std::unordered_map <
					EventTypeId, 
					std::shared_ptr <Event>
				> {
					{ typeId, event }
				},
				pos.y
			);
		}
		else {
			(*location)[typeId] = event;
		}
	}
	void removeEvent() {
		
	}
};

/*
 * TODO :: Make an events system
 * Characteristics:-
 *  1. Loops through all the types of events (Active only) in the main loop. [ TC :: O (n) ]
 *  2. For each event find trigger corresponding to it.  [ TC ::  O (1) TO O (log (n)) ]
 *  3. Execute the event for the trigger. [ TC :: any ]
 *  4. Update the corresponding entities and components for the trigger. [ TC :: O (n) ]
 *
 * */

// genarate type Id for new type of event
inline int eventTypeIdGen() {
	static int id = 0;
	return id++;
}

// get type id of Event
template <typename T>
int eventTypeId() {
	static int id = eventTypeIdGen();
	return id;
}

using listItr = std::list < std::shared_ptr <Event> >::iterator;
using EventTypeId = int;
using EventId = int;

class Div;

class EventsSystem {
private:
	EventsTree m_eventsTree;
	std::unordered_map < EventId, std::shared_ptr <Event> > m_events;
private:
	class Mouse {
	private:
		static Point2d m_pos;
	private:
		static inline bool isMouseEvent(Uint32 Event) {
			return Event >= SDL_MOUSEMOTION && Event <= SDL_MOUSEWHEEL;
			//return Event == SDL_MOUSEMOTION;
			// SDL_MOUSEEVENT are given values from [1024, 1027]
		}
	public:
		static void update(); // will execute the corresponding events for the trigger
		// get position
		static Point2d getPos() { // Point2d is cheap to copy
			return m_pos;
		}

		static Point2d getPosOnBoard();
	};
	class Keyboard {
	private:
		static inline bool isKeyboardEvent(Uint32 Event) {
			return Event >= SDL_KEYDOWN && Event <= SDL_TEXTINPUT;
		}
	public:
		static void update();
		static bool isKeyPressed(int Key);
	};
	static Mouse m_mouse;
	static Keyboard m_keyboard;
public:
	static void addEvent(std::shared_ptr <Event> Event, EventId eventId);
	static void removeEvent(EventTypeId eventType, EventId eventId);
	static void handleEvents();

	static void addDiv(std::shared_ptr <Div> div) {
		
	}
};

class Event {
private:
	int m_typeId;
	int m_eventId;
	static int m_eventIdGen;
	bool m_isHandled;
public:
	Event(int TypeId) : m_typeId(TypeId), m_eventId(m_eventIdGen++), m_isHandled(false) {}

	virtual ~Event() {}
	virtual void handle() = 0;
	bool isHandled() {
		return m_isHandled;
	}
	void setHandled(bool Handled) {
		m_isHandled = Handled;
	}
	int getTypeId() {
		return m_typeId;
	}
	int getEventId() {
		return m_eventId;
	}
};


class Div : public Entity {
private:
	Rect myDest_;
	std::unordered_map<EventTypeId, std::vector<std::shared_ptr <Event>>> myEvents_;
public:
	// consturctor
	Div(Rect dest) : myDest_(dest) {}
	void init() {
		EventsSystem::addDiv(std::shared_ptr <Div>(this));
	}
	template <typename T>
	T& addEventListener(std::shared_ptr<T> eventListener)
	{
		myEvents_[compTypeId<T>()] = eventListener;
		return *eventListener;
	}
	template <typename T>
	void removeEventListener()
	{
		myEvents_.erase(compTypeId<T>());
	}
	// get dest
	Rect getDest() const {
		return myDest_;
	}
	// set dest
	void setDest(Rect dest) {
		myDest_ = dest;
	}
};
