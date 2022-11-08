#include "gostop.h"

/*
====================================================================
							  *OTHER*
====================================================================
*/
// Print function to allow player to choose if they want to see the rules
void printRules()
{
	char rulechoice = ' ';
	cout << "Welcome to the game Go Stop, would you like to see the rules?\n";
	while (!(rulechoice == '1' || rulechoice == '2'))
	{
		cout << "(1) Yes - (2) No \n";
		cout << "Select an option: ";
		cin >> rulechoice;
	}

	if (rulechoice == '1')
	{
		cout << "BASICS:\n";
		cout << "\t Go Stop is a card game played by 2 players\n";
		cout << "\t The objective of this game is to score the most points after all the rounds\n";
		cout << "\t The players consist of a human player (you), and the computer\n\n";

		cout << "SETUP:\n";
		cout << "\t Two standard 52-card decks are used\n";
		cout << "\t Each player has a hand and a capture pile\n";
		cout << "\t In addition, a layout and stock pile are part of the game shared between players\n\n";

		cout << "ROUNDS:\n";
		cout << "\t The two decks are shuffled together\n";
		cout << "\t The cards are dealt in the following order:\n";
		cout << "\t\t 5 cards are dealt to the human player\n";
		cout << "\t\t 5 cards are dealt to the computer player\n";
		cout << "\t\t 4 cards are placed face up in the layout\n";
		cout << "\t\t 5 cards are dealt to the human player\n";
		cout << "\t\t 5 cards are dealt to the computer player\n";
		cout << "\t\t 4 cards are placed face up in the layout\n";
		cout << "\t The remaining cards are left in the stock pile, face down\n";
		cout << "\n \t The first player is determined by whoever has the most of the higher ranking card:\n";
		cout << "\t\t (At the start of subsequent rounds the player with the most points goes first)\n";
		cout << "\t The two players take alternate turns thereafter till the round ends\n";
		cout << "\t The round ends when both players have played all the cards in their hands\n\n";

		cout << "TURNS: \n";
		cout << "\t During their turn, a player plays as follows:\n\n";

		cout << "\t\t Plays a card from their hand. If the card matches:\n";
		cout << "\t\t\t H0: no card in the layout, the card is added to the layout\n";
		cout << "\t\t\t H1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout\n";
		cout << "\t\t\t H2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and the card played from the hand, leaving the stack pair in the layout\n";
		cout << "\t\t\t H3: three cards in the layout or triple stack, the player captures all four cards, i.e., adds them to their capture pile\n\n";

		cout << "\t\t Plays the top card from the stock pile. If this follows:\n";
		cout << "\t\t\t H0 or H3 - If the card from the stock pile matches:\n";
		cout << "\t\t\t\t no card in the layout, the card is added to the layout\n";
		cout << "\t\t\t\t one card in the layout, the player captures both the cards: the card played from the stock pile and the card from the layout that matches it\n";
		cout << "\t\t\t\t two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile\n";
		cout << "\t\t\t\t three cards in the layout or triple stack, the player captures all four cards\n\n";

		cout << "\t\t\t H1 or H2: If the card from the stock pile matches:\n";
		cout << "\t\t\t\t no card in the layout, the card is added to the layout. The pair of cards stacked in H1/H2 are captured\n";
		cout << "\t\t\t\t three cards in the layout or triple stack, the player captures all four cards\n";
		cout << "\t\t\t\t any card in the layout other than the stack pair from H1/H2, the player captures both the pairs - the stacked pair and the current pair\n";
		cout << "\t\t\t\t only the stack pair from H1/H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout\n\n";

		cout << "\t Two cards match if they have the same face (A-K)\n\n";

		cout << "CONTROLS: \n";
		cout << "\t To play a card, just type it as it appears on the Game (ex: 3H which is 3 of hearts)\n";
		cout << "\t If you would like to save the game, quit or ask for help, simply type 's', 'q', or 'h' respectively\n";
		cout << "====================================================================\n";
	}
	else
	{
		cout << "====================================================================\n";
	}
}// End of printRules()