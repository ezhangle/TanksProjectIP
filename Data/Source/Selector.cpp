#include "Selector.h"



Selector::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<Button> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtonVector(vector)
	, game(Game::get())
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector::~Selector()
{
	
}

void Selector::move(enum Movement direction)
{
	switch (direction)
	{
		case Movement::down:
		{
			if (mIndex == mNumberOfButtons - 1)
			{
				mIndex = 0;
				mSelectedButton = &mButtonVector[mIndex];
				mSprite.setPosition(45.0f, mButtonVector[mIndex].mButtonSprite.getPosition().y);
			}

			else
			{
				mSelectedButton = &mButtonVector[++mIndex];
				mSprite.move(0.0f, mMoveDistance);
			}

			break;
		}

		case Movement::up:
		{
			if (mIndex == 0)
			{
				mSelectedButton = &mButtonVector[mNumberOfButtons - 1];
				mIndex = mNumberOfButtons - 1;
				mSprite.setPosition(45.0f, mButtonVector[mNumberOfButtons - 1].mButtonSprite.getPosition().y);
			}

			else
			{
				mSelectedButton = &mButtonVector[--mIndex];
				mSprite.move(0.0f, -mMoveDistance);
			}

			break;
		}


		default:break;
	}
}

void Selector::draw()
{
	game->mWindow.draw(mSprite);
}

