#include "Entity.h"
#include "Game.h"

void Entity::draw(sf::RenderWindow* window) {
	window->draw(*mSprite);
	mDelete = false;
}

sf::Sprite*	Entity::getCollisionSprite() {
	return mSprite;
}

Entity::Entity(sf::Vector2f* pos, sf::Sprite* sprite)
: mSprite(sprite)
{
	mSprite->setPosition(*pos);
}

Entity::Entity(sf::Sprite* sprite)
	: mSprite(sprite)
{

}

Entity::~Entity() {
	delete mSprite;
}