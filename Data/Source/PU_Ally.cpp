#include "PU_Ally.h"
#include "Enums.h"
#include "Game.h"
#include "Tank.h"
#include "AI_Easy.h"
#include "GameState_Play.h"

PU_Ally::PU_Ally(sf::Vector2f * position)
	:PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_ally)))
{

}

void PU_Ally::onTrigger(Tank * target)
{
	PowerUp::onTrigger(target);

	if (target->mTeam == 1)
		GameState_GameBuild::get()->teamOne.numberOfMembers++;
	else
		GameState_GameBuild::get()->teamTwo.numberOfMembers++;

	Tank::ProjectileType projType = (Tank::ProjectileType)(rand() % (int)Tank::ProjectileType::NUMBER);

	AI_Easy* ally = new AI_Easy(
		new sf::Sprite(*mTarget->mBase->getTexture()),
		new sf::Sprite(*mTarget->mTop->getTexture()),
		new sf::Vector2f(100.f, 100.f),
		new sf::Vector2f(150.f, 150.f),
		mTarget->mMaxHealth / 10.f,
		mTarget->mDamage / 2.f,
		mTarget->mTeam);

	ally->changeProjectile(projType);

	GameState_Play::getStatePointer()->mMap->mEntities[2].insert(GameState_Play::getStatePointer()->mMap->mEntities[2].begin(), ally);
	onDurationEnd();
}
