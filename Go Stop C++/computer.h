#pragma once
#include "gostop.h"
#include "player.h"
#include "dealer.h"
// Class for the computer player implementation
// Computer is to be an inhereted class of player so that they could be used 
// as if there was no such thing as a computer, and it was a human v human game.

class Computer : public Player 
{
public:
	Computer();
	//void enterCard(char suit);		// checks the computers cards for the suit and sends the card through the rules

private:
	//!Alec dont need these vectors as they exist in player so computer makes them anyways
	//vector <string> player_cards;
	//vector <string> captured_cards;

};

