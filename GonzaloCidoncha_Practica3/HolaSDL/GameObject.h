#pragma once
#include "checkML.h"
class GameObject
{

public:
	GameObject() {}
	virtual ~GameObject() {}
	virtual void render() = 0;
	virtual void update() = 0;
};

