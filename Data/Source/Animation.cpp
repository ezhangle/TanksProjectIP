#include "Animation.h"
#include "Game.h"

Animation::Animation(sf::Vector2f* pos, Texture start, Texture end, int frameduration, bool repeated)
:mPos(pos), mFrameDuration(frameduration), bRepeated(repeated), mFrameClock(frameduration){

	reset();

	int s = (int)start;
	int e = (int)end;
	mNumberOfFrames = e - s;
	mSprites.resize(e - s);

	int j;
	for (int i = s; i < e; ++i) {
		j = i - s;
		mSprites[j] = new sf::Sprite(Game::get()->mTextures.get((Texture)i));
		mSprites[j]->setPosition(*pos);
		mSprites[j]->setOrigin(mSprites[j]->getLocalBounds().width / 2.f, mSprites[j]->getLocalBounds().height / 2.f);
	}
}

void Animation::update(sf::Time dt) {

	if (bFinished == false) {
		mFrameClock -= dt.asMilliseconds();

		if (mFrameClock < 0) {
			mFrameClock = mFrameDuration;
			mCurrentFrame++;
		}
	}
	else
		selfDestruct();
}

void Animation::draw(sf::RenderWindow* window) {

	if (bFinished == false) {
		window->draw(*mSprites[mCurrentFrame]);

		if (mCurrentFrame == mNumberOfFrames - 1) {
			if (bRepeated == true)
				mCurrentFrame = 0;
			else
				bFinished = true;
		}
	}
	
}

void Animation::reset() {
	mCurrentFrame = 0;
	bFinished = false;
}

void Animation::selfDestruct() {
	auto it = Game::get()->mMap->mEffects.begin();

	while ((*it) != this) {
		++it;
	}

	Game::get()->mMap->mEffects.erase(it);

	delete this;
}

Animation::~Animation() {
	for (auto it = mSprites.begin(); it != mSprites.end(); ++it)
		delete (*it);

	delete mPos;
}