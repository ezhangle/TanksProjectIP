#pragma once
#include "AddButton.h"
#include "RemoveButton.h"
#include "Entity.h"

class teamRecord
{
public:
	Entity*											mEntity;
	RemoveButton*									mRemoveButton;
	sf::Text										mText;
	size_t											index;
	teamRecord(Entity* entity, RemoveButton* button, sf::Text text, size_t ind);
	teamRecord(RemoveButton* button, std::string string);
};

inline teamRecord::teamRecord(Entity* entity, RemoveButton* button, sf::Text text, size_t ind)
	: mEntity(entity)
	, mRemoveButton(button)
	, mText(text)
{
	mText.setPosition(mRemoveButton->getText().getPosition() + sf::Vector2f(-260.0f, 0.0f));
	index = ind;
}

inline teamRecord::teamRecord(RemoveButton* button, std::string string)
	: mEntity(nullptr)
	, mRemoveButton(button)
{
	mText.setFont(Game::get()->mFonts.get(Font::VanillaExtractRegular));
	mText.setCharacterSize(20);
	mText.setString(string);
	index = 0;
}