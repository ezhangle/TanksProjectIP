#pragma once

#include <string>
#include <vector>
#include "MapButton.h"

class MapSelector
{
public:
	MapButton*										mSelectedButton;
	std::vector<MapButton>&							mButtons;
	size_t											mNumberOfButtons;

public:
	MapSelector(std::vector<MapButton> &vector);
	void											setSelected(MapButton &button);

private:
	size_t											mIndex;

private:
};