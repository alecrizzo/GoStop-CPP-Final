#include "deck.h"

/*
====================================================================
								DECK
====================================================================
*/

// Member object for the 52 cards which will be combined and dealt by Dealer();
//vector<string> Deck::card_deck;

// Constructor to setup deck of 52 cards in order
Deck::Deck() 
{	
	string card[] = 
	{ 
	"1C", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "XC", "JC", "QC", "KC",				// Clubs
	"1D", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "XD", "JD", "QD", "KD",				// Diamonds
	"1H", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "XH", "JH", "QH", "KH",				// Hearts
	"1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "XS", "JS", "QS", "KS"				// Spades
	};
	card_deck.clear();
	card_deck.insert(card_deck.end(), begin(card), end(card));
}// End of Deck()


// Function to create a deck from a loaded save file
void Deck::loadDeck(string card) 
{	//corresponding function needs to remember to card_deck.clear()
	//set up like in constructor but use iss to get all the values
	card_deck.clear();
}// End of loadDeck()

// Function to return a string card from the deck and delete it (does it from the end not the front)
string Deck::popDeck() 
{
	if (card_deck.size() != 0) 
	{
		string card;
		card = card_deck.back();
		card_deck.pop_back();
		return card;
	}
	else return "ERR!"; // !ALEC might need to change this so players aren't dealt errors

}// End of popDeck()

// Function to shuffle all the values in the Deck "randomly"
void Deck::shuffleDeck() // Got help from: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
{	
	// Time based seed to shuffle cards
	unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rng(time);
	shuffle(begin(card_deck), end(card_deck), rng);
}// End of shuffleDeck()

// Function returns amount of cards in card_deck as an integer
int Deck::sizeOfDeck() 
{
	return card_deck.size();
}// End of sizeOfDeck()

// Prints all values in deck
void Deck::printDeck() 
{
	for (unsigned int i = 0; i < card_deck.size(); i++) {
		cout << card_deck[i] << endl;
	}
}// End of printDeck()