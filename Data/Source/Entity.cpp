#include "Entity.h"

sf::Vector2f Entity::getPos() const {
	return mSprite->getPosition();
}

void Entity::setPos(sf::Vector2f* pos) {
	mSprite->setPosition(*pos);
}

void Entity::draw(sf::RenderWindow* window) {
	window->draw(*mSprite);
}

Entity::Entity(sf::Vector2f* pos, sf::Sprite* sprite, Map* map)
: mSprite(sprite),
mCurrentMap(map){
	setPos(pos);
}

Entity::Entity(Map* map)
:mCurrentMap(map){

}

