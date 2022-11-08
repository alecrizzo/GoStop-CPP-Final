#include "dealer.h"

/*
====================================================================
								DEALER
====================================================================
*/

vector<string> Dealer::s_combo_deck;
vector<string> Dealer::s_layout_pile;

Dealer::Dealer()
{
	turnVal = ' ';
	prevTurnHtype = " ";
	s_combo_deck.clear();
}// End of Dealer()

// Function Definition for dealing cards to players
void Dealer::dealCards(Player* p) 
 {
	if (s_combo_deck.size() > 0) 
	{
		p->takeCard(popDeck());
	}
	else
	{
		cout << "\nOut of Cards\n";
	}
}// End of dealCards()

// Function to return a string card from the deck and delete it (does it from the end not the front) || Mirror function to popDeck() --> Deck
string Dealer::popDeck()
{
	if (s_combo_deck.size() != 0) 
	{
		string card;
		card = s_combo_deck.back();
		s_combo_deck.pop_back();
		return card;
	}
	else return "error"; //need to change this so players aren't dealt errors

}// End of popDeck()


// Function for swapping member turnVal to alternate between human player and computer player
void Dealer::swapTurns() 
{
	switch (turnVal) 
	{
	case 'h': turnVal = 'c';
		break;
	case 'c': turnVal = 'h';
		break;

	default: cout << "ERROR: Fatal Error in swapping Turn Values - Class Dealer\n";
		break;
	}

}// End of swapTurns

// Takes two Deck(); Objects, shuffles the cards and puts them all into the deck member s_combo_deck
// which will be used as the stockpile after dealing cards
void Dealer::combineDecks(Deck d1, Deck d2) 
{
	d1.shuffleDeck();
	d2.shuffleDeck();

	int size = d1.sizeOfDeck();
	for (int i = 0; i < size; i++)
	{
		s_combo_deck.push_back(d1.popDeck());
		s_combo_deck.push_back(d2.popDeck());
	}
}// End of combineDecks()

// Push back 4 cards to a string vector, ONLY TO BE USED ON s_layout_pile vector at start of a round
void Dealer::dealLayout()
{
	for (int i = 0; i < 4; i++) 
	{
		s_layout_pile.push_back(popDeck());
	}
	sortLayout();
}// End of dealLayout()

void Dealer::displayStockpile() 
{
	for (unsigned int i = 0; i < s_combo_deck.size(); i++)
	{
		cout << s_combo_deck[i] << " ";
	}
}// End of displayStockpile()

void Dealer::displayLayout()
{
	sortLayout(); 
	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		cout << s_layout_pile[i] << " ";
	}
}// End of displayLayout()

void Dealer::displayTurn() 
{
	cout << turnVal;
}// End of displayTurn()

void Dealer::clearComboDeck()
{
	s_combo_deck.clear();
}// End of clearComboDeck

void Dealer::clearLayoutPile()
{
	s_layout_pile.clear();
}// End of clearLayoutPile()

int Dealer::numStock() 
{
	return s_combo_deck.size();
}// End of numStock()

void Dealer::changeTurn(char turn)
{
	turnVal = turn;
}// End of changeTurn

char Dealer::getTurn()
{
	return turnVal;
}// End of getTurn()

void Dealer::sortLayout()
{
	sort(s_layout_pile.begin(), s_layout_pile.end(), greater<string>());
}// End of sortLayout()

void Dealer::addToLayout(string card)
{
	s_layout_pile.push_back(card);
}// End of addToLayout()


//!ALEC might want to rename
// First checks that the card the player uses is in the layout then determines the Htype(H0, H1, etc.) based on the suitcount
// and will pair or not accordingly
void Dealer::checkLayout(Player* p, string card)	// players class and the card they play
{
	char suit = card[0];
	int suitcount = 0;	//tracks the amount of strings that have the same suit
	int paircount = 0;	//variable to track if paircount is an H3
	int layoutval = 0;	//access variable for use after the first for loop 
	string temp = " ";

	int single = 0; //to access card of single suit
	int doubl = 0;	//to access both the above card and the other choice in a case of H2

	int lastcard = 0;

	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		if (suitcount == 3) break;
		// H3 Triplestack, break out of loop and go to the switch with the string
		if (paircount == 2)
		{
			suitcount = 3;
			break;
		}

		// Update string in loop to check its values
		temp = s_layout_pile[i];
		layoutval = i;

		// Check for stacks
		if (suit == temp[0] && temp.length() > 2)
		{
			for (unsigned int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == '-') { paircount++; }
			}
		}
	   	else if((suit == temp[0]) && (temp.length() <= 2)) // Check for standalone cards of matching suit (H1) or (H2)
		{
			suitcount++;
			if (single == 0) { single = i; }
			else { doubl = i; }
		}
	}

	string choice = " ";
	switch(suitcount)
	{
	// H0: no card in the layout, the card is added to the layout.
	case 0:
		addToLayout(card);
		cout << "H0: no card in the layout, the card is added to the layout\n";
		prevTurnHtype = "H0";
		break;

	// H1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout.
	case 1:	
		cout << "H1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout\n";
		prevTurnHtype = "H1";
		H1createPair(card);
		lastcard = single;
		//!TRACK VALUE implement a way to track the value that was just adjusted here for use in stockCaseH12()
		// use s_layout_pile[lastcard] to access the previous card

		break;

	//H2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and the card played from the hand, leaving the stack pair in the layout.
	case 2:
		cout << "H2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and the card played from the hand, leaving the stack pair in the layout.\n";
		prevTurnHtype = "H2";
		do
		{
			cout << "Select the card to make the stack pair with: ";
			cin >> choice;
		} while (H2checkPairs(choice,card) != true);

		if (s_layout_pile[single].length() > 2) { lastcard = single; }
		else if (s_layout_pile[doubl].length() > 2) { lastcard = doubl; }

		//!TRACK VALUE implement a way to track the value that was just adjusted here for use in stockCaseH12()
		// use s_layout_pile[lastcard] to access the adjusted card

		break;

	//H3: three cards in the layout or triple stack, the player captures all four cards, i.e., adds them to their capture pile.
	case 3:		
		cout << "H3: three cards in the layout or triple stack, the player captures all four cards, i.e., adds them to their capture pile. \n";
		prevTurnHtype = "H3";
		if (paircount == 2) // Capture triplestack
		{
			// Add the stack from layout to the players captures and add their card
			p->captureCards(s_layout_pile[layoutval]);

			// Erase the value from the layout pile
			s_layout_pile.erase(s_layout_pile.begin()+layoutval);
		}
		else // Capture three cards in the layout of matching suit
		{
			string cap = card;
			unsigned int size = s_layout_pile.size();
			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				// if there are more than 3 matching cards in layout but we already have a capture of 4 cards we must break out
				if (cap.length() >= 11) 
				{
					break;
				}
				string x = s_layout_pile[i];
				if (suit == x[0] && x.length() <= 2)
				{
					// adds all matching suits 
					cap += "-" + x;
					s_layout_pile.erase(s_layout_pile.begin() + i);
					i--;
				}
			}
			p->captureCards(cap);
		}
		break;

	case 4: 
		cout << "\nERROR - card overflow of same suit - checkLayout() - Dealer Class\n";
		break;

	default: cout << "\nERROR - determining where suit should be after player selection - checkLayout() - Dealer Class\n";
		break;
	}
	
	// Card is played from top of stockpile
	//string topcard = "";
	char num = prevTurnHtype[1];	// uses only the number char from the string, no H
	switch (num)
	{
		case '0': 
			stockCaseH03(p, playStockCard());
			break;
		case '1':
			stockCaseH12(p, playStockCard(), lastcard);	//single to access last adjusted card at s_layout_pile[single]
			break;
		case '2':
			stockCaseH12(p, playStockCard(), lastcard);	//doubl to access last adjusted card at s_layout_pile[doubl]
			break;
		case '3':
			stockCaseH03(p, playStockCard());
			break;

	default:
		cout << "ERROR - unable to determine previous turn in relation to playing stockpile card - checkLayout() - Class Dealer()\n";
		break;
	}
	
}// End of checkLayout()

// Temporary version of check layout to work for computer, need to make work with polymorphism
void Dealer::checkLayoutComputer(Player* p, string card)	// players class and the card they play
{
	char suit = card[0];
	int suitcount = 0;	//tracks the amount of strings that have the same suit
	int paircount = 0;	//variable to track if paircount is an H3
	int layoutval = 0;	//access variable for use after the first for loop 
	string temp = " ";

	int single = 0; //to access card of single suit
	int doubl = 0;	//to access both the above card and the other choice in a case of H2

	int lastcard = 0;

	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		if (suitcount == 3) break;
		// H3 Triplestack, break out of loop and go to the switch with the string
		if (paircount == 2)
		{
			suitcount = 3;
			break;
		}

		// Update string in loop to check its values
		temp = s_layout_pile[i];
		layoutval = i;

		// Check for stacks
		if (suit == temp[0] && temp.length() > 2)
		{
			for (unsigned int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == '-') { paircount++; }
			}
		}
		else if ((suit == temp[0]) && (temp.length() <= 2)) // Check for standalone cards of matching suit (H1) or (H2)
		{
			suitcount++;
			if (single == 0) { single = i; }
			else { doubl = i; }
		}
	}

	string choice = " ";
	switch (suitcount)
	{
		// H0: no card in the layout, the card is added to the layout.
	case 0:
		addToLayout(card);
		cout << "H0: no card in the layout, the card is added to the layout\n";
		prevTurnHtype = "H0";
		break;

		// H1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout.
	case 1:
		cout << "H1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout\n";
		prevTurnHtype = "H1";
		H1createPair(card);
		lastcard = single;
		//!TRACK VALUE implement a way to track the value that was just adjusted here for use in stockCaseH12()
		// use s_layout_pile[lastcard] to access the previous card

		break;

		//H2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and the card played from the hand, leaving the stack pair in the layout.
	case 2:
		cout << "H2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and the card played from the hand, leaving the stack pair in the layout.\n";
		prevTurnHtype = "H2";
		
		H1createPair(card);

		if (s_layout_pile[single].length() > 2) { lastcard = single; }
		else if (s_layout_pile[doubl].length() > 2) { lastcard = doubl; }



		//!TRACK VALUE implement a way to track the value that was just adjusted here for use in stockCaseH12()
		// use s_layout_pile[lastcard] to access the adjusted card

		break;

		//H3: three cards in the layout or triple stack, the player captures all four cards, i.e., adds them to their capture pile.
	case 3:
		cout << "H3: three cards in the layout or triple stack, the player captures all four cards, i.e., adds them to their capture pile. \n";
		prevTurnHtype = "H3";
		if (paircount == 2) // Capture triplestack
		{
			// Add the stack from layout to the players captures and add their card
			p->captureCards(s_layout_pile[layoutval]);

			// Erase the value from the layout pile
			s_layout_pile.erase(s_layout_pile.begin() + layoutval);
		}
		else // Capture three cards in the layout of matching suit
		{
			string cap = card;
			unsigned int size = s_layout_pile.size();
			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				// if there are more than 3 matching cards in layout but we already have a capture of 4 cards we must break out
				if (cap.length() >= 11)
				{
					break;
				}
				string x = s_layout_pile[i];
				if (suit == x[0] && x.length() <= 2)
				{
					// adds all matching suits 
					cap += "-" + x;
					s_layout_pile.erase(s_layout_pile.begin() + i);
					i--;
				}
			}
			p->captureCards(cap);
		}
		break;

	case 4:
		cout << "\nERROR - card overflow of same suit - checkLayout() - Dealer Class\n";
		break;

	default: cout << "\nERROR - determining where suit should be after player selection - checkLayout() - Dealer Class\n";
		break;
	}

	// Card is played from top of stockpile
	//string topcard = "";
	char num = prevTurnHtype[1];	// uses only the number char from the string, no H
	switch (num)
	{
	case '0':
		stockCaseH03Computer(p, playStockCard());
		break;
	case '1':
		stockCaseH12(p, playStockCard(), lastcard);	//lastcard to access last adjusted card at s_layout_pile[lastcard]
		break;
	case '2':
		stockCaseH12(p, playStockCard(), lastcard);	//lastcard to access last adjusted card at s_layout_pile[lastcard]
		break;
	case '3':
		stockCaseH03Computer(p, playStockCard());
		break;

	default:
		cout << "ERROR - unable to determine previous turn in relation to playing stockpile card - checkLayout() - Class Dealer()\n";
		break;
	}

}// End of checkLayoutComputer()


//H0 or H3 - If the card from the stock pile matches:
//no card in the layout, the card is added to the layout.
//one card in the layout, the player captures both the cards : the card played from the stock pile and the card from the layout that matches it.
//two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile.
//three cards in the layout or triple stack, the player captures all four cards.
void Dealer::stockCaseH03Computer(Player* p, string card)
{
	char suit = card[0];
	int suitcount = 0;	//tracks the amount of strings that have the same suit
	int paircount = 0;	//variable to track if paircount is an H3
	int layoutval = 0;	//access variable for use after the first for loop 
	string temp = " ";

	int single = 0; //to access card of single suit
	int doubl = 0;	//to access both the above card and the other choice in a case of H2

	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{

		if (suitcount == 3) { break; }
		// H3 Triplestack, break out of loop and go to the switch with the string
		if (paircount == 2)
		{
			suitcount = 3;
			break;
		}

		// Update string in loop to check its values
		temp = s_layout_pile[i];
		layoutval = i;

		// Check for stacks/pairs
		if (suit == temp[0] && temp.length() > 2)
		{
			for (unsigned int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == '-') { paircount++; }
			}
		}
		else if ((suit == temp[0]) && (temp.length() <= 2)) // Check for standalone cards of matching suit (H1) or (H2)
		{
			suitcount++;
			if (single == 0) { single = i; }
			else { doubl = i; }
		}
	}

	string choice = "";
	cout << "Playing Stockpile card: " << card << endl;
	switch (suitcount)
	{
	case 0: //no card in the layout, the card is added to the layout.
		cout << "S0: Card matches no card in the layout, the card is added to the layout\n";
		addToLayout(card);
		break;
	case 1: //one card in the layout, the player captures both the cards : the card played from the stock pile and the card from the layout that matches it.
		cout << "S1: Card matches one card in the layout, the player captures both the cards\n";
		p->captureCards(s_layout_pile[single] + "-" + card);
		s_layout_pile.erase(s_layout_pile.begin() + single);
		break;
	case 2://two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile.
		cout << "S2: Card matches two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile\n";

		//Adjusted to pick the first one for the Computer
			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				temp = s_layout_pile[i];
				if ((s_layout_pile[i].length() <= 2) && (card[0] == temp[0]))
				{
					p->captureCards(s_layout_pile[i] + "-" + card);
					s_layout_pile.erase(s_layout_pile.begin() + i);
				}
			}

		break;
	case 3://three cards in the layout or triple stack, the player captures all four cards.
		cout << "S3: Card matches three cards in the layout or triple stack, the player captures all four cards\n";
		prevTurnHtype = "";
		if (paircount == 2) // Capture triplestack
		{
			// Add the stack from layout to the players captures and add their card
			p->captureCards(s_layout_pile[layoutval]);

			// Erase the value from the layout pile
			s_layout_pile.erase(s_layout_pile.begin() + layoutval);
		}
		else // Capture three cards in the layout of matching suit
		{
			string cap = card;
			unsigned int size = s_layout_pile.size();
			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				// if there are more than 3 matching cards in layout but we already have a capture of 4 cards we must break out
				if (cap.length() >= 11)
				{
					break;
				}
				string x = s_layout_pile[i];
				if (suit == x[0] && x.length() <= 2)
				{
					// adds all matching suits 
					cap += "-" + x;
					s_layout_pile.erase(s_layout_pile.begin() + i);
					i--;
				}
			}
			p->captureCards(cap);
		}
		break;

	default:
		cout << "ERROR - suitcount error in playing stockpile card - stockCaseH03()- Class Dealer()\n";
		break;
	}

	prevTurnHtype = "";
}// End of stockCaseH03Computer()

// Function to pair when player gets an H2: and must pick a like card to pair with
bool Dealer::H2checkPairs(string lcard, string pcard)	// layout card, player card
{
	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		if ((lcard == s_layout_pile[i]) && (pcard[0] == lcard[0]))
		{
			s_layout_pile[i] = s_layout_pile[i] + "-" + pcard;
			return true;
		}
	}

	return false;
}// End of H2checkPairs()

void Dealer::H1createPair(string pcard)
{
	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		string temp = s_layout_pile[i];
		if(temp[0] == pcard[0])
		{
			s_layout_pile[i] = s_layout_pile[i] + "-" + pcard;
		}
	}
}// End of H1createPair()

string Dealer::playStockCard()
{
	string temp = s_combo_deck[0];
	s_combo_deck.erase(s_combo_deck.begin());
	return temp;
}// End of playStockCard()

//H0 or H3 - If the card from the stock pile matches:
//no card in the layout, the card is added to the layout.
//one card in the layout, the player captures both the cards : the card played from the stock pile and the card from the layout that matches it.
//two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile.
//three cards in the layout or triple stack, the player captures all four cards.
void Dealer::stockCaseH03(Player* p, string card)
{
	char suit = card[0];
	int suitcount = 0;	//tracks the amount of strings that have the same suit
	int paircount = 0;	//variable to track if paircount is an H3
	int layoutval = 0;	//access variable for use after the first for loop 
	string temp = " ";

	int single = 0; //to access card of single suit
	int doubl = 0;	//to access both the above card and the other choice in a case of H2

	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{

		if (suitcount == 3) { break; }
		// H3 Triplestack, break out of loop and go to the switch with the string
		if (paircount == 2)
		{
			suitcount = 3;
			break;
		}

		// Update string in loop to check its values
		temp = s_layout_pile[i];
		layoutval = i;

		// Check for stacks/pairs
		if (suit == temp[0] && temp.length() > 2)
		{
			for (unsigned int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == '-') { paircount++; }
			}
		}
		else if ((suit == temp[0]) && (temp.length() <= 2)) // Check for standalone cards of matching suit (H1) or (H2)
		{
			suitcount++;
			if (single == 0) { single = i; }
			else { doubl = i; }
		}
	}

	string choice = "";
	cout << "Playing Stockpile card: " << card << endl;
	switch (suitcount)
	{
	case 0: //no card in the layout, the card is added to the layout.
		cout << "S0: Card matches no card in the layout, the card is added to the layout\n";
		addToLayout(card);
		break;
	case 1: //one card in the layout, the player captures both the cards : the card played from the stock pile and the card from the layout that matches it.
		cout << "S1: Card matches one card in the layout, the player captures both the cards\n";
		p->captureCards(s_layout_pile[single] + "-" + card);
		s_layout_pile.erase(s_layout_pile.begin() + single);
		break;
	case 2://two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile.
		cout << "S2: Card matches two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile\n";
		do
		{
			cout << "Select the a card of same suit as " << card << " to capture as a stacked pair: ";
			cin >> choice;
		} while (takePair(p, choice, card) != true);

		break;
	case 3://three cards in the layout or triple stack, the player captures all four cards.
		cout << "S3: Card matches three cards in the layout or triple stack, the player captures all four cards\n";
		prevTurnHtype = "";
		if (paircount == 2) // Capture triplestack
		{
			// Add the stack from layout to the players captures and add their card
			p->captureCards(s_layout_pile[layoutval]);

			// Erase the value from the layout pile
			s_layout_pile.erase(s_layout_pile.begin() + layoutval);
		}
		else // Capture three cards in the layout of matching suit
		{
			string cap = card;
			unsigned int size = s_layout_pile.size();
			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				// if there are more than 3 matching cards in layout but we already have a capture of 4 cards we must break out
				if (cap.length() >= 11)
				{
					break;
				}
				string x = s_layout_pile[i];
				if (suit == x[0] && x.length() <= 2)
				{
					// adds all matching suits 
					cap += "-" + x;
					s_layout_pile.erase(s_layout_pile.begin() + i);
					i--;
				}
			}
			p->captureCards(cap);
		}
		break;

	default:
		cout << "ERROR - suitcount error in playing stockpile card - stockCaseH03()- Class Dealer()\n";
		break;
	}

	prevTurnHtype = "";
}// End of stockCaseH03()

//H1 or H2: If the card from the stock pile matches :
//no card in the layout, the card is added to the layout.The pair of cards stacked in H1 / H2 are captured.
//three cards in the layout or triple stack, the player captures all four cards.The pair of cards stacked in H1 / H2 are also captured.
//any card in the layout other than the stack pair from H1 / H2, the player captures both the pairs - the stacked pair and the current pair.
//only the stack pair from H1 / H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout.
void Dealer::stockCaseH12(Player* p, string card, int last)
{
	char suit = card[0];
	int suitcount = 0;	//tracks the amount of strings that have the same suit
	int paircount = 0;	//variable to track if paircount is an H3
	int layoutval = 0;	//access variable for use after the first for loop 
	string temp = "";

	int single = 0; //to access card of single suit
	int doubl = 0;	//to access both the above card and the other choice in a case of H2

	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{

		if (suitcount == 3) { break; }
		// H3 Triplestack, break out of loop and go to the switch with the string
		if (paircount == 2)
		{
			suitcount = 3;
			break;
		}

		// Update string in loop to check its values
		temp = s_layout_pile[i];
		layoutval = i;

		// Check for stacks/pairs
		if (suit == temp[0] && temp.length() > 2)
		{
			for (unsigned int i = 0; i < temp.length(); i++)
			{
				if (temp[i] == '-') { paircount++; }
			}
		}
		else if ((suit == temp[0]) && (temp.length() <= 2)) // Check for standalone cards of matching suit (H1) or (H2)
		{
			suitcount++;
			single = i;
		}
	}

	// if card matches only the stack pair from H1 / H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout.
	// if card matches any card in the layout other than the stack pair from H1 / H2, the player captures both the pairs - the stacked pair and the current pair.

	// keeps track of matches without adjusting suitcount because that is our upcoming switch condition
	int matchcount = 0;
	
	if (suitcount == 1 || suitcount == 2)
	{
		paircount = 0;
		for (unsigned int i = 0; i < s_layout_pile.size(); i++)
		{
			temp = s_layout_pile[i];
			// if suit matches and i != the last card played (the H1 or H2)
			if (temp[0] == suit && i != last && temp.length() <= 2) 
			{ 
				// set doubl equal to i to use in case 2 of switch to access a matching single card
				doubl = i;
				matchcount++;
			}
			else if (temp[0] == suit && i == last && temp.length() > 2) 
			{
				paircount++; 
				matchcount++;
			}
		}

		if (matchcount >= 1 && paircount < 1)
		{
			// matches a card in the layout other than the stack pair
			suitcount = 2;
		}
		else if (paircount == 1 && matchcount == 1)
		{
			// only matches stack pair the player had
			suitcount = 1;
		}
	}

	string choice = "";
	cout << "Playing Stockpile card: " << card << endl;
	switch (suitcount)
	{
	case 0:// if matches no card in the layout, the card is added to the layout.The pair of cards stacked in H1 / H2 are captured.
		cout << "S0: Card matches no card in the layout, the card is added to the layout. The pair of cards stacked in H1 / H2 are captured.\n";
		addToLayout(card);
		p->captureCards(s_layout_pile[last]);
		s_layout_pile.erase(s_layout_pile.begin() + last);
		break;

	case 1:// if matches only the stack pair from H1 / H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout.
		cout << "S2: Card matches only the stack pair from H1 / H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout\n";
		s_layout_pile[last] += "-" + card;
		break;

	case 2:// if matches any card in the layout other than the stack pair from H1 / H2, the player captures both the pairs - the stacked pair and the current pair.
		cout << "S1: Card matches cards in the layout other than the stack pair from H1 / H2, the player captures both the pairs - the stacked pair and the current pair\n";
		s_layout_pile[doubl] += "-" + card;
		p->captureCards(s_layout_pile[doubl]);
		p->captureCards(s_layout_pile[last]);

		if(doubl > last)	//determines deletion order to avoid bounds errors
		{
			s_layout_pile.erase(s_layout_pile.begin() + doubl);
			s_layout_pile.erase(s_layout_pile.begin() + last);
		}
		else
		{
			s_layout_pile.erase(s_layout_pile.begin() + last);
			s_layout_pile.erase(s_layout_pile.begin() + doubl);
		}
		break;

	case 3://if matches three cards in the layout or triple stack, the player captures all four cards.The pair of cards stacked in H1 / H2 are also captured.
		cout << "S3: Card matches three cards in the layout or triple stack, the player captures all four cards. The pair of cards stacked in H1 / H2 are also captured.\n";
		if (paircount == 2) // Capture triplestack
		{
			// Add the stack from layout to the players captures and add their card along with previous played pair
			p->captureCards(s_layout_pile[layoutval]);
			p->captureCards(s_layout_pile[last]);

			// Erase the values from the layout pile 
			s_layout_pile.erase(s_layout_pile.begin() + layoutval);
			s_layout_pile.erase(s_layout_pile.begin() + last);
		}
		else // Capture three cards in the layout of matching suit
		{
			string cap = card;
			unsigned int size = s_layout_pile.size();

			// Captures the previous hand before the loop so the accessors don't get all messed up or go out of scope
			p->captureCards(s_layout_pile[last]);
			s_layout_pile.erase(s_layout_pile.begin() + last);


			for (unsigned int i = 0; i < s_layout_pile.size(); i++)
			{
				// if there are more than 3 matching cards in layout but we already have a capture of 4 cards we must break out
				if (cap.length() >= 11)
				{
					break;
				}
				string x = s_layout_pile[i];
				if (suit == x[0] && x.length() <= 2)
				{
					// adds all matching suits 
					cap += "-" + x;
					s_layout_pile.erase(s_layout_pile.begin() + i);
					i--;
				}
			}
			p->captureCards(cap);
		}

		break;

	default:
		cout << "ERROR - suitcount error in playing stockpile card - stockCaseH12()- Class Dealer()\n";
		break;
	}

	prevTurnHtype = "";
}// End of stockCaseH12()

// gives stockpile values to the reference vector
void Dealer::getStockpile(vector<string> & stock)
{
	stock = s_combo_deck;
}// End of getStockpile()

// gives layout values to the reference vector
void Dealer::getLayout(vector<string> & layout)
{
	layout = s_layout_pile;
}// End of getLayout()

// Function to pair when stockpile has 2 choices from the layout, captures the choice with the stockpile card
bool Dealer::takePair(Player* p, string lcard, string scard)	// layout card, stockpile card
{
	for (unsigned int i = 0; i < s_layout_pile.size(); i++)
	{
		if ((lcard == s_layout_pile[i]) && (scard[0] == lcard[0]))
		{
			p->captureCards(s_layout_pile[i] + "-" + scard);
			s_layout_pile.erase(s_layout_pile.begin() + i);
			return true;
		}
	}

	return false;
}// End of takePair()

void Dealer::writeLayout(vector<string> layout)
{
	s_layout_pile.clear();
	s_layout_pile = layout;
}// End of writeLayout()

void Dealer::writeStockpile(vector<string> stockpile)
{
	s_combo_deck.clear();
	s_combo_deck = stockpile;
}// End of writeStockpile()