#include "Projectile.h"
#include "Game.h"
#include "Tank.h"
#include "Player.h"
#include "AI.h"
#include "Obstacle.h"
#include <iostream>

#include "GameState_Play.h"

Projectile::Projectile(sf::Sprite* sprite, Tank* parent):
Entity(sprite),
mVelocity(parent->mProjectileSpeed),
mDamage(parent->mDamage),
mParent(parent){

	mSprite->setRotation(mParent->mTop->getRotation());
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

	Map* map = GameState_Play::getStatePointer()->mMap;

	for (auto it1 = map->mEntities.begin(); it1 != map->mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2) != this)
			{
				if (SAT.collision(mSprite, (*it2)->getCollisionSprite())) {

					if (Tank* proj = dynamic_cast<Tank*>((*it2))) {
						if (mParent->mTeam != proj->mTeam) {
							collideSolid = true;
							proj->mHealth -= mDamage;
							if (proj->mHealth <= 0.f) {
					
								for (auto itAi = GameState_Play::getStatePointer()->mMap->mEntities[2].begin(); itAi != GameState_Play::getStatePointer()->mMap->mEntities[2].end(); ++itAi) {
									if (AI* ai = dynamic_cast<AI*>((*itAi))) {
										if (ai->mTarget == proj) {
											ai->findNewTarget();
										}
											
									}
								}
							}
						}
					}

					if (Obstacle* obs = dynamic_cast<Obstacle*>((*it2))) {
						collideSolid = true;
					}
					
				}
			}
		}
	}

	if(collideSolid == true)
		GameState_Play::getStatePointer()->mMap->mEffects.insert(GameState_Play::getStatePointer()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mSprite->getPosition()), Texture::expl_01_0000, Texture::expl_01_0023, 20, false));

	return collideSolid;

}


Projectile::~Projectile() {
	delete mVelocity;
}