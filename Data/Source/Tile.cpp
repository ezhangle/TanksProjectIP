#pragma once

#include "Tile.h"

Tile::Tile() {

}

void Tile::draw(sf::RenderWindow* window) {
	std::list<Entity*>::iterator it;

	for (it = mEntities.begin(); it != mEntities.end(); ++it) {
		(*it)->draw(window);
	}
}

void Tile::update(sf::Time dt) {
	std::list<Entity*>::iterator it;

	for (it = mEntities.begin(); it != mEntities.end(); ++it) {
		(*it)->update(dt);
	}
}

void Tile::insertEntity(Entity* entity) {
	mEntities.insert(mEntities.begin(), entity);
}

void Tile::eraseEntity(Entity* entity) {
	std::list<Entity*>::iterator it = mEntities.begin();

	while (*it != entity) {
		++it;
	}

	mEntities.erase(it);
}

void Tile::eraseEntity(std::list<Entity*>::iterator it) {
	mEntities.erase(it);
}