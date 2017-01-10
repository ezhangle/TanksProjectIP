#include "Map.h"
#include "Tank.h"
#include "Player.h"
#include "Game.h"
#include "Obstacle.h"

#include "AI.h"
#include "AI_Easy.h"
#include "AI_Medium.h"
#include "AI_Hard.h"
#include "PU_AttackSpeed.h"
#include "PU_Speed.h"

#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>

Map::Map(std::string& objectsPath, std::vector<Entity*>& entities):
mTileLength(64.f){
	mEntities.resize(NUMBER);
	mWidth = Game::get()->mWidth / mTileLength;
	mHeight = Game::get()->mHeight / mTileLength;
	mPowerUpRespawnClock.restart();

	for each (Entity* entity in entities)
	{
		mEntities[2].push_back(entity);
	}

	loadFromFile(objectsPath);
}

void Map::loadFromFile(std::string& objectsPath) {
	std::ifstream objectsIN(objectsPath);

	int bground;
	objectsIN >> bground;

	mBackground.setTexture(Game::get()->mTextures.get((Texture)bground));
	sf::Vector2f scale;
	scale.x = Game::get()->mWidth / mBackground.getLocalBounds().width;
	scale.y = Game::get()->mHeight / mBackground.getLocalBounds().height;

	mBackground.setScale(scale);

	std::string obj;
	size_t		noObjects;

	objectsIN >> noObjects;

	for (size_t i = 0; i < noObjects; ++i) {
		objectsIN >> obj;
		insertObject(obj, objectsIN);
	}


	objectsIN.close();
	initObstacleMap();
}

void Map::insertObject(std::string& obj, std::ifstream& stream) {
	size_t				team;
	sf::Vector2f*		position, *velocity;
	std::string			tankType;
	float				health, damage;


	if (obj == "player1") {
		
		position = new sf::Vector2f;
		velocity = new sf::Vector2f;

		stream >> tankType;
		stream >> position->x >> position->y;
		stream >> velocity->x >> velocity->y;
		stream >> health >> damage >> team;

		insertPlayerOne(tankType, position, velocity, health, damage, team);
	}
	if (obj == "player2") {
		
		position = new sf::Vector2f;
		velocity = new sf::Vector2f;

		stream >> tankType;
		stream >> position->x >> position->y;
		stream >> velocity->x >> velocity->y;
		stream >> health >> damage >> team;

		insertPlayerTwo(tankType, position, velocity, health, damage, team);
	}

	if (obj == "static_obstacle") {
		std::string	textureStr;
		Texture texture;
		sf::Vector2f* position = new sf::Vector2f;
		
		stream >> textureStr;
		stream >> position->x >> position->y;
	
		insertStaticObject(textureStr, position);
	}

	if (obj == "ai") {

		position = new sf::Vector2f;
		velocity = new sf::Vector2f;

		std::string difficulty;

		stream >> difficulty >> tankType;
		stream >> position->x >> position->y;
		stream >> velocity->x >> velocity->y;
		stream >> health >> damage >> team;

		insertAI(difficulty, tankType, position, velocity, health, damage, team);
	}
}

void Map::update(sf::Time dt) {

	if (mEntities[1].size() < 3) {
		if (mPowerUpRespawnClock.getElapsedTime().asSeconds() > 5.f) {
			sf::Vector2f* position = new sf::Vector2f;

			do {
				position->y = rand() % mHeight;
				position->x = rand() % mWidth;
			} while (mObstacleMap[(int)position->y][(int)position->x] == -1);

			position->y *= mTileLength;
			position->x *= mTileLength;

			insertRandomPowerUp(position);
			mPowerUpRespawnClock.restart();
		}

	}

	//update entities & effects
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			(*it2)->update(dt);
		}
	}

	for (auto it = mEffects.begin(); it != mEffects.end(); ++it) {
		(*it)->update(dt);
	}

	//delete flagged entities & effects
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2)->mDelete == true) {
				Entity* temp = (*it2);
				(*it1).erase(it2);
				delete temp;
			}
		}
	}

	for (auto it = mEffects.begin(); it != mEffects.end(); ++it) {
		if ((*it)->bFinished == true) {
			Animation* temp = (*it);
			mEffects.erase(it);
			delete temp;
		}

	}
}

void Map::draw(sf::RenderWindow* window) {
	
	window->draw(mBackground);
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			(*it2)->draw(window);
		}
	}

	for (auto it = mEffects.begin(); it != mEffects.end(); ++it) {
		(*it)->draw(window);
	}
}

void Map::insertPlayerOne(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team) {
	std::vector<sf::Keyboard::Key> keys;
	keys.resize(20);

	keys[(int)Tank::Command::DOWN] = sf::Keyboard::S;
	keys[(int)Tank::Command::UP] = sf::Keyboard::W;
	keys[(int)Tank::Command::LEFT] = sf::Keyboard::A;
	keys[(int)Tank::Command::RIGHT] = sf::Keyboard::D;

	keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::B;
	keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::M;

	keys[(int)Tank::Command::SHOOT] = sf::Keyboard::N;

	Texture baseTexture, topTexture;
	getTankTextureIds(tankType, baseTexture, topTexture);

	mEntities[TANK].insert(mEntities[TANK].begin(), new Player(
		new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
		new sf::Sprite(Game::get()->mTextures.get(topTexture)),
		position,
		velocity,
		health,
		damage,
		keys,
		team));
}

void Map::insertPlayerTwo(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team) {
	std::vector<sf::Keyboard::Key> keys;
	keys.resize(20);

	keys[(int)Tank::Command::DOWN] = sf::Keyboard::Numpad5;
	keys[(int)Tank::Command::UP] = sf::Keyboard::Numpad8;
	keys[(int)Tank::Command::LEFT] = sf::Keyboard::Numpad4;
	keys[(int)Tank::Command::RIGHT] = sf::Keyboard::Numpad6;

	keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::Numpad7;
	keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::Numpad9;

	keys[(int)Tank::Command::SHOOT] = sf::Keyboard::P;

	Texture baseTexture, topTexture;
	getTankTextureIds(tankType, baseTexture, topTexture);

	mEntities[TANK].insert(mEntities[TANK].begin(), new Player(
		new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
		new sf::Sprite(Game::get()->mTextures.get(topTexture)),
		position,
		velocity,
		health,
		damage,
		keys,
		team));
}

void Map::insertStaticObject(const std::string& textureString, sf::Vector2f* position) {

	Texture texture;
	getStaticObjectTextureId(textureString, texture);

	mEntities[OBSTACLE].insert(mEntities[OBSTACLE].begin(), new Obstacle(position, new sf::Sprite(Game::get()->mTextures.get(texture))));
}

void Map::getTankTextureIds(const std::string& textureString, Texture& baseTexture, Texture& topTexture) {
	if (textureString == "tank1") {
		baseTexture = Texture::tank1_body;
		topTexture = Texture::tank1_gun;
	}
	else if (textureString == "tank1b") {
		baseTexture = Texture::tank1b_body;
		topTexture = Texture::tank1b_gun;
	}
	else if (textureString == "tank2") {
		baseTexture = Texture::tank2_body;
		topTexture = Texture::tank2_gun;
	}
	else if (textureString == "tank2b") {
		baseTexture = Texture::tank2b_body;
		topTexture = Texture::tank2b_gun;
	}
	else if (textureString == "tank3") {
		baseTexture = Texture::tank3_body;
		topTexture = Texture::tank3_gun;
	}
	else if (textureString == "tank3b") {
		baseTexture = Texture::tank3b_body;
		topTexture = Texture::tank3b_gun;
	}
	else if (textureString == "tank3c") {
		baseTexture = Texture::tank3c_body;
		topTexture = Texture::tank3c_gun;
	}
	else if (textureString == "tank3d") {
		baseTexture = Texture::tank3d_body;
		topTexture = Texture::tank3d_gun;
	}
	else
		throw std::runtime_error("Map->getTankTextureIds: The specified texture doesn't exist");
}

void Map::getStaticObjectTextureId(const std::string& textureString, Texture& texture) {
	if (textureString == "box")
		texture = Texture::box;
	else if (textureString == "box_2x1")
		texture = Texture::box_2x1;
	else if (textureString == "box_2x2")
		texture = Texture::box_2x2;
	else if (textureString == "box_small")
		texture = Texture::box_small;
	else
		throw std::runtime_error("Map->getStaticObjectTextureId: The specified texture doesn't exist");
}

void Map::insertAI(const std::string& difficulty, const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team) {

	Texture baseTexture, topTexture;
	getTankTextureIds(tankType, baseTexture, topTexture);

	if (difficulty == "easy") {
		mEntities[TANK].insert(mEntities[TANK].begin(), new AI_Easy(
			new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			velocity,
			health,
			damage,
			team));
	}
	else if (difficulty == "medium") {
		mEntities[TANK].insert(mEntities[TANK].begin(), new AI_Medium(
			new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			velocity,
			health,
			damage,
			team));
	}
	else if (difficulty == "hard") {
		mEntities[TANK].insert(mEntities[TANK].begin(), new AI_Hard(
			new sf::Sprite(Game::get()->mTextures.get(baseTexture)),
			new sf::Sprite(Game::get()->mTextures.get(topTexture)),
			position,
			velocity,
			health,
			damage,
			team));
	}
	
}

void Map::insertRandomPowerUp(sf::Vector2f* position)
{
	int randomIndex = rand() % 2;

	switch (randomIndex) {
	case 0:
		mEntities[1].insert(mEntities[1].begin(), new PU_Speed(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_speed))));
		break;
	case 1:
		mEntities[1].insert(mEntities[1].begin(), new PU_AttackSpeed(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_fast_attacks))));
		break;
	default:
		break;
	}
}

void Map::initObstacleMap() {

	mObstacleMap = new int*[mHeight];
	for (int i = 0; i < mHeight; ++i) {
		mObstacleMap[i] = new int[mWidth]();
	}

	auto it1 = mEntities[0].begin();
	auto it2 = mEntities[0].end();
	for (; it1 != it2; ++it1) {

		sf::FloatRect bounds = (*it1)->mSprite->getGlobalBounds();

		int left = (int)(bounds.left / mTileLength);
		int top = (int)(bounds.top / mTileLength);
		int leftPlus = (int)((bounds.left + bounds.width) / mTileLength);
		int topPlus = (int)((bounds.top + bounds.height) / mTileLength);

		for (int i = top; i <= topPlus; ++i) {
			for (int j = left; j <= leftPlus; ++j) {
				mObstacleMap[i][j] = -1;
			}
		}

	}

	float edgeX, edgeY;
	for (int i = 0; i < mHeight; ++i) {
		for (int j = 0; j < mWidth; ++j) {
			edgeY = i * mTileLength;
			edgeX = j * mTileLength;
			if (edgeX < 64.f || edgeY < 64.f || edgeX >= Game::get()->mWidth - 64.f || edgeY >= Game::get()->mHeight - 64.f)
				mObstacleMap[i][j] = -1;
		}
	}
}