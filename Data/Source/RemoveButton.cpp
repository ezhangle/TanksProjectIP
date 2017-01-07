#include "RemoveButton.h"
#include "Team.h"


RemoveButton::RemoveButton(sf::Vector2f position, std::string text, size_t charSize, RemoveButton::Action action)
	: mAction(action)
	, TextButton(position, text, charSize, TextButton::Action::none)
{
	mTextRemove.setString("X");
	mTextRemove.setFont(Game::get()->mFonts.get(Font::VanillaExtractRegular));
	mTextRemove.setCharacterSize(charSize);
}

void RemoveButton::triggerAction(team &team, unsigned int index)
{
	switch (mAction)
	{
		case Action::remove:
		{
			team.mTeamMembers.erase(team.mTeamMembers.begin() + index);
			team.mTeamMembers.shrink_to_fit();
			break;
		}

		default:break;
	}
}