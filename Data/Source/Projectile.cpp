#include "Projectile.h"


Projectile::Projectile(sf::Sprite* sprite, sf::Vector2f* position, sf::Vector2f* velocity, Animation* onhit, float damage):
Entity(position, sprite),
mVelocity(velocity),
onHitAnim(onhit),
mDamage(damage){

}

void Projectile::update(sf::Time dt) {
	sf::Vector2f newPos(mSprite->getPosition());
	newPos.x += sin(mSprite->getRotation()*3.14f / 180.f)* dt.asSeconds() * mVelocity->x;
	newPos.y -= cos(mSprite->getRotation()*3.14f / 180.f)* dt.asSeconds() * mVelocity->y;

	mSprite->setPosition(newPos);
}