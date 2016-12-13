#pragma once

#include "Entity.h"

class Tile{
public:
	Tile(Entity* entity);
private:
	Entity* mEntity;
};