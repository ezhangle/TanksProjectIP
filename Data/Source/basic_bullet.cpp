#include "basic_bullet.h"
#include "Enums.h"
#include "Game.h"


BasicBullet::BasicBullet(Tank* parent):
Projectile(new sf::Sprite(Game::get()->mTextures.get(Texture::bullet_orange)), parent)
{

	mSprite->setRotation(parent->mTop->getRotation());
	mSprite->setOrigin(mSprite->getLocalBounds().width / 2.f, mSprite->getLocalBounds().height / 2.f);

	sf::Vector2f pos(sin(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().width / 2.f + parent->mTop->getPosition().x,
		-cos(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().height / 2.f + parent->mTop->getPosition().y);

	mSprite->setPosition(pos);

	
}

void BasicBullet::spawnOnHitAnimation()
{
	Game::get()->mMap->mEffects.insert(Game::get()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mSprite->getPosition()), Texture::expl_01_0000, Texture::expl_01_0023, 20, false));
}
