#pragma once
#include "gostop.h"
#include "dealer.h"
#include "player.h"
#include "deck.h"
#include "computer.h"
#include "help.h"
#include <fstream>
#include <sstream>

using namespace std;

// Class for Game
class Game 
{
public:
	Game();
	void display();
	Player* getPlayerID(int id);			// Function to get the required playerID (human or computer)
	void selectCard(Dealer scam);			// user picks card to send through all the gostop rules 
	void scanCard(Dealer scam);				// computer scans and decides a card to play

private:
	friend class Save;

	//static Player playerType[];			// did not work for setting up computer with player
	static vector<Player*> player_type;		// does work for setting up computer with player

	char gameName;							// Variable for use with the function gameType() (might not need depending on implementation)
	int roundNum = 0;						// Variable to keep track of round number
	string lastCard = " ";					

	Dealer scammer;							// card dealer (named scammer because dealers cheat)
	Help helper;

	char gameType();						// For user to select the game type game or round
	void playRound();						// Function to start one round based on user input from gameType 
	void playMatch();						// Function to start a match based on user input from gameType 
	void menu();							// Menu after every turn for player options
	void endGame();							// Simply to end the game on a whim (from user selection menu())
	char whoFirst();						// Determines first players turn by checking both their cards, returns char for 'c' or 'h'

	void writeSave();						// Writes savegame to a .txt file
	void readSave();						// Reads savegame file and sets up to the current executable
	void printWinner();						// Prints out player with highest score
};