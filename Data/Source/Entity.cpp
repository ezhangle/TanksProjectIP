#include "Entity.h"
#include "Game.h"

sf::Vector2f Entity::getPos() const {
	return mSprite->getPosition();
}

void Entity::setPos(sf::Vector2f* pos) {
	mSprite->setPosition(*pos);
}

void Entity::draw(sf::RenderWindow* window) {
	window->draw(*mSprite);
}

sf::Sprite*	Entity::getSprite() {
	return mSprite;
}

Entity::Entity(sf::Vector2f* pos, sf::Sprite* sprite)
: mSprite(sprite)
{
	setPos(pos);
}

void Entity::selfDestruct() {
	auto it = Game::get()->mMap->mEntities[2].begin();

	while ((*it) != this) {
		++it;
	}

	Game::get()->mMap->mEntities[2].erase(it);

	delete this;
}

Entity::~Entity() {
	delete mSprite;
}