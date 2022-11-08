#pragma once
#include "gostop.h"
#include "deck.h"


// Class for a player (to be inhereted by the computer)
class Player 
{
public:
	Player();

	template <typename T>
	void drawCard(T d);
	void takeCard(string card);
	void captureCards(string cards);	// Capture cards and increase score

	void displayCards();				// prints players hand
	void displayCaptured();				// prints captured cards
	void displayScore();				// prints score

	int getScore();								// returns score
	int getHandSize();							// Returns int amount of cards in the player_cards vector
	void getHand(vector<string> & hand);		// assigns the values of player hand to a vector 
	void getCaptured(vector<string> & captured);// assigns the values of captured cards to vector
	string getCardAt(int i);					//returns a string card at i in the player_cards vector

	void emptyCaptured();
	void emptyHand();					// empties the users hand
	void eraseCard(int i);				// erases a card at in player cards

	void sortHand();					// sorts the cards in hand (player_cards)
	void sortCaptured();				// sorts the cards captured (captured_cards)

	int totalCards();					// returns size of the player card vector

	char suitType(int i);				// gets the suit of a card at i in the players hand

	void writeScore(int points);
	void writeHand(vector<string> hand);
	void writeCaptures(vector<string> captures);

	int computerSelection(char suit);	//returns an int to access the card the computer will play
	

private:
	friend class Dealer;

	vector <string> player_cards;		// players hand
	vector <string> captured_cards;		// players captures

	int score;

};