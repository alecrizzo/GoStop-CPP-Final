#pragma once
#include "gostop.h"
#include "deck.h"

// Class for Deck
class Deck 
{
public:
	Deck();										// Sets up all 52 cards in order "1C" - "KS"

	int sizeOfDeck();
	void loadDeck(string card);
	string popDeck();					// Gets card off top of deck and removes it
	void shuffleDeck();					// Shuffles deck
	void printDeck();

private:
	vector<string> card_deck;			// Standard deck of 52 cards

};
