#include "LaserBall.h"
#include "Game.h"
#include "VectorUtility.h"
#include "GameState_Play.h"

LaserBall::LaserBall(Tank* parent):
	Projectile(new sf::Sprite(Game::get()->mTextures.get(Texture::bullet_laser_ball)), parent),
	mLaserRange(100.f)
{
	mSprite->setRotation(parent->mTop->getRotation());
	mSprite->setOrigin(mSprite->getLocalBounds().width / 2.f, mSprite->getLocalBounds().height / 2.f);

	sf::Vector2f pos(sin(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().width / 2.f + parent->mTop->getPosition().x,
		-cos(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().height / 2.f + parent->mTop->getPosition().y);

	mSprite->setPosition(pos);
}

void LaserBall::update(sf::Time dt)
{
	Projectile::update(dt);

	mLasers.clear();

	sf::VertexArray laser(sf::Lines, 2);
	laser[0].position = mSprite->getPosition();
	laser[0].color = sf::Color::Yellow;
	laser[1].color = sf::Color::Red;

	auto it1 = GameState_Play::getStatePointer()->mMap->mEntities[2].begin();
	auto it2 = GameState_Play::getStatePointer()->mMap->mEntities[2].end();

	for (; it1 != it2; ++it1) {
		if (Tank* enemy = dynamic_cast<Tank*>(*it1)) {
			if (enemy->mTeam != mParent->mTeam) {
				float distance = Vector2f::distance(mSprite->getPosition(), enemy->mBase->getPosition());
				if (distance < mLaserRange) {
					laser[1].position = enemy->mBase->getPosition();
					mLasers.insert(mLasers.begin(), laser);

					enemy->mHealth -= (mDamage / 2.f) * dt.asSeconds();

					sf::Vector2f ballScale(mSprite->getScale());

					if (ballScale.x < 2.f) {
						ballScale.x += 0.01f;
						ballScale.y += 0.01f;

						mLaserRange += 1.f;
						mSprite->setScale(ballScale);
					}			
				}	
			}
		}
	}

}

void LaserBall::draw(sf::RenderWindow * window)
{
	Entity::draw(window);

	auto del = mLasers.begin();
	for (auto it = mLasers.begin(); it != mLasers.end(); ++it) {
		window->draw((*it));
	}
		
}

void LaserBall::spawnOnHitAnimation()
{
	GameState_Play::getStatePointer()->mMap->mEffects.insert(GameState_Play::getStatePointer()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mSprite->getPosition()), Texture::expl_01_0000, Texture::expl_01_0023, 20, false));
}
