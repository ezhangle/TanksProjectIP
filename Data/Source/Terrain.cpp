#pragma once
#include "Terrain.h"

Terrain::Terrain(sf::Vector2f* pos, sf::Sprite* sprite, bool solid)
	:Entity(pos, sprite),
	bSolid(solid) {

}

void Terrain::update(sf::Time dt) {

}