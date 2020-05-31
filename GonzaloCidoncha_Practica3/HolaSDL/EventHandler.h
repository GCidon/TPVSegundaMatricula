#pragma once
#include "SDL.h" // Windows
#include "checkML.h"
#include <list>

class EventHandler
{
public:
	EventHandler() {}
	virtual ~EventHandler() {}
	virtual bool handleEvent(SDL_Event const& evt) = 0;

	void setItHandler(const std::list<EventHandler*>::iterator& it) {
		ithandlers_ = it;
	}

protected:
	std::list<EventHandler*>::iterator ithandlers_;
};

