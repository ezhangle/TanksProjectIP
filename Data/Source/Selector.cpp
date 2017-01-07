#include "Selector.h"


#include "FullscreenButton.h"
#include "ResolutionButton.h"
#include "VSyncButton.h"
#include "AddButton.h"
#include "Team_Record.h"


template <typename buttonType>
Selector<buttonType>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<buttonType> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<TextButton>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<TextButton> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<ResolutionButton>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<ResolutionButton> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<VSyncButton>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<VSyncButton> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<FullscreenButton>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<FullscreenButton> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<AddButton>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<AddButton> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}

Selector<teamRecord>::Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<teamRecord> &vector)
	: mSprite(texture)
	, mIndex(0)
	, mSelectedButton(&vector[0])
	, mMoveDistance(moveDistance)
	, mButtons(vector)
{
	mSprite.setPosition(startLocation);
	mNumberOfButtons = vector.size();
}


template <typename buttonType>
void Selector<buttonType>::move(Movement direction)
{
	switch (direction)
	{
		case Movement::down:
		{
			if (mIndex == mNumberOfButtons - 1)
			{
				mIndex = 0;
				mSelectedButton = &mButtons[mIndex];
				mSprite.setPosition(20.0f, mButtons[mIndex].getText().getPosition().y - 20.0f);
			}

			else
			{
				mSelectedButton = &mButtons[++mIndex];
				mSprite.move(0.0f, mMoveDistance);
			}

			break;
		}

		case Movement::up:
		{
			if (mIndex == 0)
			{
				mSelectedButton = &mButtons[mNumberOfButtons - 1];
				mIndex = mNumberOfButtons - 1;
				mSprite.setPosition(20.0f, mButtons[mNumberOfButtons - 1].getText().getPosition().y - 20.0f);
			}

			else
			{
				mSelectedButton = &mButtons[--mIndex];
				mSprite.move(0.0f, -mMoveDistance);
			}

			break;
		}


		default:break;
	}
}


void Selector<TextButton>::move(Movement direction)
{
	switch (direction)
	{
	case Movement::down:
	{
		if (mIndex == mNumberOfButtons - 1)
		{
			mIndex = 0;
			mSelectedButton = &mButtons[mIndex];
			mSprite.setPosition(20.0f, mButtons[mIndex].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[++mIndex];
			mSprite.move(0.0f, mMoveDistance);
		}

		break;
	}

	case Movement::up:
	{
		if (mIndex == 0)
		{
			mSelectedButton = &mButtons[mNumberOfButtons - 1];
			mIndex = mNumberOfButtons - 1;
			mSprite.setPosition(20.0f, mButtons[mNumberOfButtons - 1].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[--mIndex];
			mSprite.move(0.0f, -mMoveDistance);
		}

		break;
	}


	default:break;
	}
}

void Selector<ResolutionButton>::move(Movement direction)
{
	switch (direction)
	{
	case Movement::down:
	{
		if (mIndex == mNumberOfButtons - 1)
		{
			mIndex = 0;
			mSelectedButton = &mButtons[mIndex];
			mSprite.setPosition(20.0f, mButtons[mIndex].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[++mIndex];
			mSprite.move(0.0f, mMoveDistance);
		}

		break;
	}

	case Movement::up:
	{
		if (mIndex == 0)
		{
			mSelectedButton = &mButtons[mNumberOfButtons - 1];
			mIndex = mNumberOfButtons - 1;
			mSprite.setPosition(20.0f, mButtons[mNumberOfButtons - 1].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[--mIndex];
			mSprite.move(0.0f, -mMoveDistance);
		}

		break;
	}


	default:break;
	}
}

void Selector<VSyncButton>::move(Movement direction)
{
	switch (direction)
	{
	case Movement::down:
	{
		if (mIndex == mNumberOfButtons - 1)
		{
			mIndex = 0;
			mSelectedButton = &mButtons[mIndex];
			mSprite.setPosition(20.0f, mButtons[mIndex].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[++mIndex];
			mSprite.move(0.0f, mMoveDistance);
		}

		break;
	}

	case Movement::up:
	{
		if (mIndex == 0)
		{
			mSelectedButton = &mButtons[mNumberOfButtons - 1];
			mIndex = mNumberOfButtons - 1;
			mSprite.setPosition(20.0f, mButtons[mNumberOfButtons - 1].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[--mIndex];
			mSprite.move(0.0f, -mMoveDistance);
		}

		break;
	}


	default:break;
	}
}

void Selector<FullscreenButton>::move(Movement direction)
{
	switch (direction)
	{
	case Movement::down:
	{
		if (mIndex == mNumberOfButtons - 1)
		{
			mIndex = 0;
			mSelectedButton = &mButtons[mIndex];
			mSprite.setPosition(20.0f, mButtons[mIndex].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[++mIndex];
			mSprite.move(0.0f, mMoveDistance);
		}

		break;
	}

	case Movement::up:
	{
		if (mIndex == 0)
		{
			mSelectedButton = &mButtons[mNumberOfButtons - 1];
			mIndex = mNumberOfButtons - 1;
			mSprite.setPosition(20.0f, mButtons[mNumberOfButtons - 1].getText().getPosition().y - 20.0f);
		}

		else
		{
			mSelectedButton = &mButtons[--mIndex];
			mSprite.move(0.0f, -mMoveDistance);
		}

		break;
	}


	default:break;
	}
}
