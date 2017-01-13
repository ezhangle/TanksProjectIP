#pragma once
#include "TextButton.h"
#include "Tank.h"
#include "Selector.h"
#include "TankBuildData.h"

class TankButton
	: public TextButton
{
public:
	TankBuildData									tankData;
	std::vector<sf::Text>							mTextData;

public:
	TankButton(sf::Vector2f position, std::string text, size_t charSize, float hp, float damage, float speed, std::string textureIdentifie);

private:


private:




};

