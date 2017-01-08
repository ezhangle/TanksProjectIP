#include "RemoveButton.h"
#include "Team.h"

#include <iostream>
#include <algorithm>


RemoveButton::RemoveButton(sf::Vector2f position, std::string text, size_t charSize, RemoveButton::Action action)
	: mAction(action)
	, TextButton(position, text, charSize, TextButton::Action::none)
{
	mTextRemove.setString("X");
	mTextRemove.setFont(Game::get()->mFonts.get(Font::VanillaExtractRegular));
	mTextRemove.setCharacterSize(charSize);
}

void RemoveButton::triggerAction(team &team, unsigned int index, size_t& player1_team, size_t& player2_team)
{
	switch (mAction)
	{
		case Action::remove:

		{
			//team.mTeamMembers.erase(std::remove(team.mTeamMembers.begin(), team.mTeamMembers.end(), team.mTeamMembers.at(index)), team.mTeamMembers.end());

			player1_team = 0;
			player2_team = 0;

			for (unsigned int i = index; i < team.mTeamMembers.size(); i++)
			{
				team.mTeamMembers[i].mRemoveButton->getText().move(0.0f, -30.0f);
				team.mTeamMembers[i].mText.move(0.0f, -30.0f);
			}

			team.mAddPosition.y -= 30.0f;
			team.mAddPosition.y = team.mBorder.getPosition().y + 5.0f;
			team.numberOfMembers = 0;
			team.mTeamMembers.clear();
			break;
		}

		case Action::clear:
		{
			team.mTeamMembers.clear();
			team.numberOfMembers = 0;
			team.mAddPosition.y = team.mBorder.getPosition().y + 5.0f;
			team.mTeamMembers.push_back(teamRecord(nullptr, new RemoveButton(sf::Vector2f(100.0f, 100.0f), "Clear", 20, RemoveButton::Action::clear), sf::Text("", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20), 0));
			break;
		}

		default:break;
	}
}