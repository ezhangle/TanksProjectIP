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
};

inline teamRecord::teamRecord(Entity* entity, RemoveButton* button, sf::Text text, size_t ind)
	: mEntity(entity)
	, mRemoveButton(button)
	, mText(text)
{
	mText.setPosition(mRemoveButton->getText().getPosition() + sf::Vector2f(-260.0f, 0.0f));
	index = ind;
}