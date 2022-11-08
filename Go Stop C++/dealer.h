#pragma once
#include "player.h"
#include "gostop.h"
#include "deck.h"


// Class for Dealer
class Dealer 
{
public:
	Dealer();

	void combineDecks(Deck d1, Deck d2);
	static string popDeck();
	void dealCards(Player* p);			
	void dealLayout();								// deals 4 cards to layout
	void displayStockpile();						// displays the vector s_combo_deck aka stockpile
	void displayTurn();								// displays the current players turn

	
	void clearComboDeck();							// used to clear combo deck for a new round in match mode
	void clearLayoutPile();							// used to clear layout pile for use in new game
	void displayLayout();							// displays the vector s_layout_pile aka layout
	void sortLayout();								// sorts layout cards in order of face value
	void addToLayout(string card);					// pushes card onto layout

	int numStock();									// gives num of cards in stockpile/s_combo_deck
	void changeTurn(char turn);						// changes turn to the character given in parameter
	char getTurn();									// returns char turnVal
	void checkLayout(Player* p, string s);			// checks if there matches in the layout for the players choice
	void checkLayoutComputer(Player* p, string s);	// temp version for computer, should use polymorphism instead

	void getStockpile( vector<string> & stock);
	void getLayout(vector<string> & layout);
	void writeLayout(vector<string> layout);
	void writeStockpile(vector<string> stockpile);

private:
	friend class Player;

	static vector<string> s_layout_pile;			// the layout for use in gameplay
	static vector<string> s_combo_deck;				// the combination of the 2 decks, becomes the stockpile	

	char turnVal;									// 'h' for human turn, 'c' for computer turn
	string prevTurnHtype;							// keeps track of H0, H1, H2, and H3 for use with the stockpiles turn

	bool H2checkPairs(string lcard, string pcard);								
	void H1createPair(string pcard);
	string playStockCard();
	void stockCaseH03(Player* p, string card);			// determines outcome of cases H0 or H3
	void stockCaseH03Computer(Player* p, string card);	// temp version of the above for computer

	void stockCaseH12(Player* p, string card, int last);// determines outcome of cases H1 or H2
	bool takePair(Player* p, string lcard, string scard);

	void swapTurns();
};