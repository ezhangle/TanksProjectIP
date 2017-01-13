#pragma once

#include <string>


class TankBuildData
{
public:
	float											mHealth;
	float											mDamage;
	float											mSpeed;
	std::string										mTextureIdentifier;

public:
	TankBuildData(float hp, float damage, float speed, std::string textureIdentifier);

private:


private:


};	

inline TankBuildData::TankBuildData(float hp, float damage, float speed, std::string textureIdentifier)
	: mTextureIdentifier(textureIdentifier)
{
	mHealth = hp;
	mDamage = damage;
	mSpeed = speed;
}