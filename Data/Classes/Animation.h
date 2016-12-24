#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enums.h"

class Animation {
public:
	Animation(sf::Vector2f* pos, Texture start, Texture end, int frameduration, bool repeated);
	~Animation();

	void	update(sf::Time dt);
	void	draw(sf::RenderWindow* window);
	void	reset();

public:
	int							mCurrentFrame;
	int							mFrameClock;

	int							mFrameDuration;
	int							mNumberOfFrames;
	bool						bRepeated;
	bool						bFinished;
	sf::Vector2f				*mPos;
	std::vector<sf::Sprite*>	mSprites;
};