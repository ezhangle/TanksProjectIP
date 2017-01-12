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
			if (team.numberOfMembers == 0)
				return;

			if (team.numberOfMembers == 1)
			{
				
				if ((team.mTeamMembers.begin() + index)->mText.getString() == "Player 1" && player1_team != 0)
					player1_team = 0;

				else if ((team.mTeamMembers.begin() + index)->mText.getString() == "Player 2" && player2_team != 0)
					player2_team = 0;

				team.mTeamMembers.clear();
				team.numberOfMembers = 0;
				team.mAddPosition.y -= 30.0f;

				return;
			}


			if ((team.mTeamMembers.begin() + index)->mText.getString() == "Player 1" && player1_team != 0)
				player1_team = 0;

			else if ((team.mTeamMembers.begin() + index)->mText.getString() == "Player 2" && player2_team != 0)
				player2_team = 0;

			team.mTeamMembers.erase(team.mTeamMembers.begin() + index);
			team.numberOfMembers--;
			for (unsigned int i = index; i < team.numberOfMembers; i++)
			{
				team.mTeamMembers[i].mRemoveButton->getText().move(0.0f, -30.0f);
				team.mTeamMembers[i].mText.move(0.0f, -30.0f);
				team.mTeamMembers[i].index--;
			}
			
		
			team.mAddPosition.y -= 30.0f;
			break;
		}

		case Action::clear:
		{
			team.mTeamMembers.clear();
			team.numberOfMembers = 0;
			team.mAddPosition.y = team.mBorder.getPosition().y + 5.0f;
			break;
		}

		default:break;
	}
}