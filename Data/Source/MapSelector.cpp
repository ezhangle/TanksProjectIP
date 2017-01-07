#include "MapSelector.h"

MapSelector::MapSelector(std::vector<MapButton>& vector)
	: mIndex(0)
	, mSelectedButton(&vector[0])
	, mButtons(vector)
{
}

void MapSelector::setSelected(MapButton &button)
{
	mSelectedButton = &button;
	mSelectedButton->getText().setFillColor(sf::Color::Red);
}
