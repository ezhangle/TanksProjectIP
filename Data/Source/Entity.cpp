#include "Entity.h"

sf::Vector2f Entity::getPos() const {
	return mSprite->getPosition();
}

void Entity::setPos(sf::Vector2f* pos) {
	mSprite->setPosition(*pos);
}

Entity::Entity(sf::Vector2f* pos, sf::Sprite* sprite)
: mSprite(sprite){
	setPos(pos);
}

void Entity::draw(sf::RenderWindow* window) {
	window->draw(*mSprite);
}