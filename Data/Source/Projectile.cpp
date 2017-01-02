#include "Projectile.h"
#include "Game.h"
#include "Tank.h"
#include "Player.h"
#include "AI.h"
#include <iostream>

Projectile::Projectile(sf::Sprite* sprite, sf::Vector2f* position, sf::Vector2f* velocity, float damage, Tank* parent):
Entity(position, sprite),
mVelocity(velocity),
mDamage(damage),
mParent(parent){

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
				if (SAT.collision(mSprite, (*it2)->getCollisionSprite())) {
					collideSolid = true;

					if (Tank* proj = dynamic_cast<Tank*>((*it2))) {
						if (mParent->mTeam != proj->mTeam) {
							proj->mHealth -= mDamage;
							if (proj->mHealth <= 0.f) {
					
								for (auto itAi = Game::get()->mMap->mEntities[2].begin(); itAi != Game::get()->mMap->mEntities[2].end(); ++itAi) {
									if (AI* ai = dynamic_cast<AI*>((*itAi))) {
										if (ai->mTarget == proj) {
											ai->findNewTarget();
										}
											
									}
								}
							}
						}
						else
							collideSolid = false;
					}

					if (Projectile* proj = dynamic_cast<Projectile*>((*it2))) {
						collideSolid = false;
					}
					
				}
			}
		}
	}

	if(collideSolid == true)
		Game::get()->mMap->mEffects.insert(Game::get()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mSprite->getPosition()), Texture::expl_01_0000, Texture::expl_01_0023, 20, false));

	return collideSolid;

}


Projectile::~Projectile() {
	delete mVelocity;
}