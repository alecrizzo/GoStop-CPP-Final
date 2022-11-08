#include "player.h"

/*
====================================================================
								PLAYER
====================================================================
*/

// Constructor for class Player(): sets up the vectors for hand, captures and the score
Player::Player() 
{
	player_cards.clear();
	captured_cards.clear();
	score = 0;
}// End of Player()

// Function to take card from the deck and add to player_cards 
template <typename T>	// Templated to work with both Deck(); and Dealer();
void Player::drawCard(T d) 
{
	player_cards.push_back(d.popDeck());
}// End of drawCard

// Amount of cards player has
int Player::totalCards() 
{
	return player_cards.size();
}// End of totalCards()

// Pushes the string card into the back of the players cards vector
void Player::takeCard(string card) 
{
	player_cards.push_back(card);
}// End of takeCard()

// Pushes the string card into the back of the captured cards vector (paired cards)
void Player::captureCards(string cards)	
{
	captured_cards.push_back(cards);
	score++;
}// End of pairCards()

// Displays the cards in hand the player has
void Player::displayCards()
{
	sortHand();
	for (unsigned int i = 0; i < player_cards.size(); i++) 
	{
		cout << player_cards[i] << " ";
	}
}// End of displayCards()

// Outputs the captured cards the player has
void Player::displayCaptured()
{
	sortCaptured();
	for (unsigned int i = 0; i < captured_cards.size(); i++)
	{
		cout << captured_cards[i] << " ";
	}
}// End of displayCaptured()

// Displays current players score
void Player::displayScore() 
{
	cout << score;
}// End of displayScore()

// Function to clear a players hand
void Player::emptyHand()
{
	player_cards.clear();
}// End of emptyHand()

char Player::suitType(int i)
{
	string temp = " ";
	temp = player_cards[i];
	char suit = temp[0];
	return suit;
}// End of suitType

int Player::getScore()
{
	return score;
}// End of getScore()

int Player::getHandSize() 
{
	return player_cards.size();
}// End of getHandSize()

// Sort hand using std::sort http://www.cplusplus.com/reference/algorithm/sort/
void Player::sortHand()
{
	sort(player_cards.begin(), player_cards.end(), greater<string>());
}// End of sortHand()

// Sort captured using std::sort
void Player::sortCaptured()
{
	sort(captured_cards.begin(), captured_cards.end(), greater<string>());
}// End of sortCaptured()

string Player::getCardAt(int i)
{
	return player_cards[i];
}// End of getCardAt()

void Player::eraseCard(int i)
{
	player_cards.erase(player_cards.begin() + i);
}// End of eraseCard()

void Player::getHand(vector<string> & hand)
{
	hand = player_cards;
}// End of getHand()

void Player::getCaptured(vector<string> & captured)
{
	captured = captured_cards;
}// End of getCaptured()

void Player::emptyCaptured()
{
	captured_cards.clear();
}// End of emptyCaptured()

void Player::writeScore(int points)
{
	score = points;
}// End of writeScore()

void Player::writeHand(vector<string> hand)
{
	player_cards.clear();
	player_cards = hand;
}// End of writeHand()

void Player::writeCaptures(vector<string> captures)
{
	captured_cards.clear();
	captured_cards = captures;
}// End of writeCaptures()

int Player::computerSelection(char suit)
{
	for (unsigned int i = 0; i < player_cards.size(); i++)
	{
		string temp = player_cards[i];
		if (suit == temp[0])
		{
			return i;
		}
	}

	return -1;
}// End of computerSelection()