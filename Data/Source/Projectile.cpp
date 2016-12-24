#include "Projectile.h"
#include "Game.h"
#include "Tank.h"
#include "Player.h"
#include <iostream>

Projectile::Projectile(sf::Sprite* sprite, sf::Vector2f* position, sf::Vector2f* velocity, float damage):
Entity(position, sprite),
mVelocity(velocity),
mDamage(damage){

}

void Projectile::update(sf::Time dt) {
	sf::Vector2f newPos(mSprite->getPosition());
	newPos.x += sin(mSprite->getRotation()*3.14f / 180.f)* dt.asSeconds() * mVelocity->x;
	newPos.y -= cos(mSprite->getRotation()*3.14f / 180.f)* dt.asSeconds() * mVelocity->y;

	mSprite->setPosition(newPos);

	if (outOfBounds() || checkCollision()) {
		mDelete = true;
	}
}

bool Projectile::outOfBounds() {
	sf::Vector2f pos = mSprite->getPosition();

	if (pos.x < -64.f || pos.x >(float)Game::get()->mWidth + 64.f ||
		pos.y < -64.f || pos.y >(float)Game::get()->mHeight + 64.f)
		return true;

	return false;
}

bool Projectile::checkCollision() {
	
	bool collideSolid = false;

	Map* map = Game::get()->mMap;

	for (auto it1 = map->mEntities.begin(); it1 != map->mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2) != this)
			{
				if (SAT.collision(mSprite, (*it2)->getSprite())) {
					Game::get()->mMap->mEffects.insert(Game::get()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mSprite->getPosition()), Texture::expl_01_0000, Texture::expl_01_0023, 20, false));

					if (Tank* proj = dynamic_cast<Tank*>((*it2))) {
						proj->mHealth -= mDamage;
						
					}
					collideSolid = true;
				}
			}
		}
	}

	return collideSolid;

}


Projectile::~Projectile() {
	delete mVelocity;
}