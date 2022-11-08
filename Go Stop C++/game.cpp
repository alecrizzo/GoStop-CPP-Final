#include "game.h"

/*
====================================================================
							Game
====================================================================
*/

vector<Player*> Game::player_type;

// Clears and prepares values for game, then asks the game type and begins in the corresponding mode.
Game::Game() 
{
	player_type.clear();
	player_type.push_back(new Player());
	player_type.push_back(new Computer());
	
	gameName = gameType();
	if (gameName == '1') { playRound(); }
	else if (gameName == '2') { playMatch(); }
	else { cout << "ERROR: Fatal Error in Game Type Selection - Class Game\n"; }

}// End of Game()

// Displays the current values of the game to the user
void Game::display() 
{
	// might want to change formatting to be more appropriate for gameplay (this is serialization format)
	cout << "====================================================================\n";
	cout << "Round: " << roundNum << endl << endl;

	cout << "Computer: " << endl;
		cout << "\tScore: ";
		player_type[1]->displayScore();
		cout << endl;
		cout << "\tHand: ";
		player_type[1]->displayCards();
		cout << endl;
		cout << "\tCapture Pile: ";
		player_type[1]->displayCaptured();
		cout << endl << endl;

		cout << "Layout: ";
		scammer.displayLayout();
		cout << endl << endl << endl;

		cout << "Human: " << endl;
		cout << "\tScore: ";
		player_type[0]->displayScore();
		cout << endl;
		cout << "\tHand: ";
		player_type[0]->displayCards();
		cout  << endl;
		cout << "\tCapture Pile: ";
		player_type[0]->displayCaptured();

		cout << "\n\nStock Pile: "; //<< scammer.numStock() << " cards\n";	//if you only want to show the amount of cards left (face down stockpile)
		scammer.displayStockpile(); 
		cout << endl;

		cout << "====================================================================\n";

		cout << "Current Player: "; 
		char tempTurn = scammer.getTurn();
		if (tempTurn == 'c') { cout << "Computer"; }
		else if (tempTurn == 'h') { cout << "Human"; }
		else if (tempTurn == 's') { cout << "Modulo suit, very cool"; }	// This line should be impossible to get because modulo is handled in order hierarchy
		
		cout << endl;

}// End of display()

void Game::printWinner()
{
	display();
	if (player_type[0]->getScore() > player_type[1]->getScore())
	{
		cout << "The winner is the Human!\n";
	}
	else if (player_type[0]->getScore() < player_type[1]->getScore())
	{
		cout << "The winner is the Computer!\n";
	}
	else if (player_type[0]->getScore() == player_type[1]->getScore())
	{
		cout << "The game is a tie?!\n";
	}
	else { cout << "ERROR - Could not determine winner - printWinner() - Class Game()\n"; }

}// End of printWinner()

char Game::gameType() 
{
	char userSelection = ' ';

	cout << "Select the type of game you would like to play.\n";
	while (!(userSelection == '1' || userSelection == '2'))
	{
		cout << "(1) Round - (2) Match \n";
		cout << "Select an option: ";
		cin >> userSelection;
	}
	
	return userSelection;
}// End of gameType

Player* Game::getPlayerID(int id) 
{ 
	return player_type[id]; 
}// End of getPlayerID


void Game::playRound() 
{
	// Increase the round counter
	roundNum++;

	// Create Deck objects to have 2 operating decks
	Deck d1;
	Deck d2;

	// Combine both deck 1 and deck 2 classes which are shuffled together
	scammer.combineDecks(d1, d2);

	// Deal the players 5 cards, computer 5 cards, then layout 4 cards then repeat
	for (int i = 0; i < 5; i++) { scammer.dealCards(player_type[0]); }
	for (int i = 0; i < 5; i++) { scammer.dealCards(player_type[1]); }
	scammer.dealLayout();
	for (int i = 0; i < 5; i++) { scammer.dealCards(player_type[0]); }
	for (int i = 0; i < 5; i++)	{ scammer.dealCards(player_type[1]); }
	scammer.dealLayout();

	// Changes turn based on the heirarchy of cards to determine first player
	if(roundNum == 1)
	{ 
		if (whoFirst() == 's')
		{
			cout << "\n == Players have modulo suit(same cards), restarting round == \n";

			// Empty all card contents and reset the round
			player_type[0]->emptyHand();
			player_type[1]->emptyHand();
			scammer.clearLayoutPile();
			scammer.clearComboDeck();

			playRound();
		}
		else
		{
			scammer.changeTurn(whoFirst());
		}
	}
	else if (roundNum > 1)
	{
		if (player_type[0]->getScore() > player_type[1]->getScore())		// if player score higher let player go first
		{
			scammer.changeTurn('h');
		}
		else if (player_type[0]->getScore() < player_type[1]->getScore())	// if computer score higher let computer go first
		{
			scammer.changeTurn('c');
		}
		else if (player_type[0]->getScore() == player_type[1]->getScore())	// if both scores are equal use the first run method
		{
			if (whoFirst() == 's')
			{
				cout << "\n == Players have modulo suit(same cards), restarting round == \n";

				// Empty all card contents and reset the round
				player_type[0]->emptyHand();
				player_type[1]->emptyHand();
				scammer.clearLayoutPile();
				scammer.clearComboDeck();

				playRound();
			}
			else
			{
				scammer.changeTurn(whoFirst());
			}
		}
	}

	// Loop turns for gameplay
	while(!(player_type[0]->getHandSize() == 0 && player_type[1]->getHandSize() == 0))
	{
		// Update display for the player
		display();

		if (scammer.getTurn() == 'c')
		{
			//scammer.computerTurn();
			menu();
			scanCard(scammer);
			scammer.changeTurn('h');

		} //!ALEC needs the computers decision to be output so the player understands the logic
		else if (scammer.getTurn() == 'h') 
		{
			menu(); // Changes turn to 'c' after playing card
		}
	}

	printWinner();

}// End of playRound()

void Game::playMatch() 
{
	char choice = ' ';

	do {
		playRound();

		// Input validation for playing another round
		while (choice != '1' && choice != '2')
		{
			cout << "Would you like to play another round?\n";
			cout << "(1) Yes - (2) No \n";
			cout << "Select an option: ";
			cin >> choice;
		}

		// Clear all of the assets that will be used for next round
		if (choice == '1') 
		{ 
			scammer.clearComboDeck();
			scammer.clearLayoutPile();
			player_type[0]->emptyHand();
			player_type[1]->emptyHand();
			player_type[0]->emptyCaptured();
			player_type[1]->emptyCaptured();

			choice = ' ';
		}
	} while (!( choice == '2'));

	// Delete players and clear the array that held them
	endGame();

}// End of playMatch()

void Game::menu()
{
	char select = ' ';

	if (scammer.getTurn() == 'c') 
	{
		do
		{
			cout << "(1) Save game - (2) Continue - (3) Get help - (4) Quit game \n";
			cout << "Select an option: ";
			cin >> select;

		} while (!(select == '1' || select == '2' || select == '3' || select == '4'));

		switch (select)
		{
		case '1': // Save game implementation (write a file to save game)
			select = ' ';
			do
			{
				cout << "(1) Save and Quit - (2) Load a game file\n";
				cout << "Select an option: ";
				cin >> select;
			} while (!(select == '1' || select == '2'));
			if (select == '1') { writeSave(); }
			if (select == '2') { readSave(); }

			break;
		case '2': // Move implementation
			break;
		case '3': // Help implementation
			helper.giveAdvice(player_type[0], scammer);
			break;
		case '4': endGame();
			break;

		default: cout << "ERROR IN OPTION SELECTION";
			break;
		}
	}
	else if (scammer.getTurn() == 'h')
	{
		do
		{
			cout << "(1) Save game - (2) Make a move - (3) Get help - (4) Quit game \n";
			cout << "Select an option: ";
			cin >> select;

		} while (!(select == '1' || select == '2' || select == '3' || select == '4'));

		switch (select)
		{
		case '1': // Save game implementation (write a file to save game)
			select = ' ';
			do
			{
				cout << "(1) Save and Quit - (2) Load a game file\n";
				cout << "Select an option: ";
				cin >> select;
			} while (!(select == '1' || select == '2'));
			if (select == '1') { writeSave(); }
			if (select == '2') { readSave(); }

			break;
		case '2': // Move implementation
			selectCard(scammer);
			scammer.changeTurn('c');
			break;
		case '3': // Help implementation
			helper.giveAdvice(player_type[0], scammer);
			scammer.changeTurn('h');
			break;
		case '4': // Quit game implementation
			endGame();
			break;

		default: cout << "ERROR IN OPTION SELECTION";
			break;
		}
	}

}// End of menu()

// Function to delete players and clear the array that held them, then exit(0)
void Game::endGame()
{
	delete player_type[0];
	delete player_type[1];
	player_type.clear();
	scammer.clearLayoutPile();
	scammer.clearComboDeck();
	exit(0);
	system("PAUSE");
}// End of endGame()

// Determines the first player of a game based on who has the most out of the hierarchy of cards
char Game::whoFirst()
{
	char turn = ' ';
	int player_suits[13] = {};
	int computer_suits[13] = {};

	for (int i = 0; i < 10; i++) 
	{
		// Players suits
		switch (player_type[0]->suitType(i))
		{
		case 'K': player_suits[12]++;
			break;
		case 'Q': player_suits[11]++;
			break;
		case 'J': player_suits[10]++;
			break;
		case 'X': player_suits[9]++;
			break;
		case '9': player_suits[8]++;
			break;
		case '8': player_suits[7]++;
			break;
		case '7': player_suits[6]++;
			break;
		case '6': player_suits[5]++;
			break;
		case '5': player_suits[4]++;
			break;
		case '4': player_suits[3]++;
			break;
		case '3': player_suits[2]++;
			break;
		case '2': player_suits[1]++;
			break;
		case '1': player_suits[0]++;
			break;
		}
	}
	// Computers suits
	for (int i = 0; i < 10; i++)
	{
		switch (player_type[1]->suitType(i))
		{
		case 'K': computer_suits[12]++;
			break;
		case 'Q': computer_suits[11]++;
			break;
		case 'J': computer_suits[10]++;
			break;
		case 'X': computer_suits[9]++;
			break;
		case '9': computer_suits[8]++;
			break;
		case '8': computer_suits[7]++;
			break;
		case '7': computer_suits[6]++;
			break;
		case '6': computer_suits[5]++;
			break;
		case '5': computer_suits[4]++;
			break;
		case '4': computer_suits[3]++;
			break;
		case '3': computer_suits[2]++;
			break;
		case '2': computer_suits[1]++;
			break;
		case '1': computer_suits[0]++;
			break;
		}
	}

	// Compare the arrays to find out who goes first
	for (int i = 12; i > -1; i--) 
	{
		if (player_suits[i] > computer_suits[i]) { return turn = 'h'; }							// Human wins turn selection
		else if (player_suits[i] < computer_suits[i]) { return turn = 'c'; }					// Computer wins turn selection
		else if ((player_suits[i] == computer_suits[i]) && i == 0) { return turn = 's'; }		// Nobody wins, shuffle
	}	

	return turn = 's';
}// End of whoFirst()

// Lets player select the card they want to play 
void Game::selectCard(Dealer scam)
{
	bool success = false;
	string card = " ";
	do
	{
		cout << "Enter a card you have that you would like to play: ";
		cin >> card;

		for (int i = 0; i < player_type[0]->getHandSize(); i++)
		{
			// if players cards at i == card
			if (player_type[0]->getCardAt(i) == card)
			{
				// Sets players variable for last card equal to card
				lastCard = card;

				// Adds the card to the layout and checks the outcome of its play
				scam.checkLayout(player_type[0], card);

				// Erases the card from players hand
				player_type[0]->eraseCard(i);

				success = true;
			}
		}

		if (player_type[0]->getHandSize() == 0) { success = true; }
	} while (success == false);

}// End of selectCard()

// Computer finds the option it wants to do
// similar to giveAdvice() - Class Help() but has different logic to the actions at the end
// will play for triple stacks and if it's not possible on the turn it will decide to send out its first card

void Game::scanCard(Dealer scam)
{
	int matches[13] = { 0 };		//keeps track of the amount of cards that match in the layout to the players hand
	int suits[13] = { 0 };		//keeps track of the suit types in player hand

	vector<string> layout;
	vector<string> hand;
	vector<string> humanhand;

	scam.getLayout(layout);
	player_type[1]->getHand(hand);
	player_type[0]->getHand(humanhand);

	string selected = "";

	// Sets up all the computers values for what suits they have
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		string temp = hand[i];
		if (temp[0] != ' ') 
		{
			switch (temp[0])
			{
			case '1':
				suits[0]++;
				break;
			case '2':
				suits[1]++;
				break;
			case '3':
				suits[2]++;
				break;
			case '4':
				suits[3]++;
				break;
			case '5':
				suits[4]++;
				break;
			case '6':
				suits[5]++;
				break;
			case '7':
				suits[6]++;
				break;
			case '8':
				suits[7]++;
				break;
			case '9':
				suits[8]++;
				break;
			case 'X':
				suits[9]++;
				break;
			case 'J':
				suits[10]++;
				break;
			case 'Q':
				suits[11]++;
				break;
			case 'K':
				suits[12]++;
				break;

			default:
				cout << "ERROR - scanCard() - Class Game()\n";
				break;
			}
		}

	}


	for (unsigned int i = 0; i < layout.size(); i++)
	{
		string temp = layout[i];

		if (temp[0] == '1' && suits[0] > 0)
		{
			if (temp.length() == 8)
			{
				matches[0] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[0]++;
		}
		else if (temp[0] == '2' && suits[1] > 0)
		{
			if (temp.length() == 8)
			{
				matches[1] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[1]++;

		}
		else if (temp[0] == '3' && suits[2] > 0)
		{
			if (temp.length() == 8)
			{
				matches[2] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[2]++;
		}
		else if (temp[0] == '4' && suits[3] > 0)
		{
			if (temp.length() == 8)
			{
				matches[3] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[3]++;
		}
		else if (temp[0] == '5' && suits[4] > 0)
		{
			if (temp.length() == 8)
			{
				matches[4] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[4]++;
		}
		else if (temp[0] == '6' && suits[5] > 0)
		{
			if (temp.length() == 8)
			{
				matches[5] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[5]++;
		}
		else if (temp[0] == '7' && suits[6] > 0)
		{
			if (temp.length() == 8)
			{
				matches[6] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[6]++;
		}
		else if (temp[0] == '8' && suits[7] > 0)
		{
			if (temp.length() == 8)
			{
				matches[7] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[7]++;
		}
		else if (temp[0] == '9' && suits[8] > 0)
		{
			if (temp.length() == 8)
			{
				matches[8] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[8]++;
		}
		else if (temp[0] == 'X' && suits[9] > 0)
		{
			if (temp.length() == 8)
			{
				matches[9] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[9]++;
		}
		else if (temp[0] == 'J' && suits[10] > 0)
		{
			if (temp.length() == 8)
			{
				matches[10] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[10]++;
		}
		else if (temp[0] == 'Q' && suits[11] > 0)
		{
			if (temp.length() == 8)
			{
				matches[11] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[11]++;
		}
		else if (temp[0] == 'K' && suits[12] > 0)
		{
			if (temp.length() == 8)
			{
				matches[12] += 3;
				continue;
			}
			else if (temp.length() == 5)
			{
				// can't do anything to a stacked pair
				continue;
			}

			matches[12]++;
		}
	}// End of gauntlet

	int most = 0;
	int index = 0;

	for (int i = 0; i <= 12; i++)
	{
		if (matches[i] > most)
		{
			index = i;
			most = matches[i];
		}
	}

	if (most >= 3)
	{
		string recc = "";
		cout << "Computer played a: ";
		switch (index)
		{
		case 0:
			recc = "1";
			break;
		case 1:
			recc = "2";
			break;
		case 2:
			recc = "3";
			break;
		case 3:
			recc = "4";
			break;
		case 4:
			recc = "5";
			break;
		case 5:
			recc = "6";
			break;
		case 6:
			recc = "7";
			break;
		case 7:
			recc = "8";
			break;
		case 8:
			recc = "9";
			break;
		case 9:
			recc = "X";
			break;
		case 10:
			recc = "J";
			break;
		case 11:
			recc = "Q";
			break;
		case 12:
			recc = "K";
			break;

		default:
			cout << "ERROR - scanCard() - Class Game()\n";
			break;
		}


		// Computer enters its card to capture triple stack
		int here = player_type[1]->computerSelection(recc[0]);
		if (here == -1) { cout << "\nERROR - could not obtain computer card scanCard() - Class Game()"; }
		else
		{
			selected = player_type[1]->getCardAt(here);
			player_type[1]->eraseCard(here);
			cout << selected << " to capture a triple stack\n";
			scammer.checkLayoutComputer( player_type[1] ,selected );
		}

	}
	else
	{
		int here = 0;
		selected = player_type[1]->getCardAt(here);
		player_type[1]->eraseCard(here);

		cout << "Computer played: ";
		cout << selected;
		cout << " because there were no triple stacks to capture" << endl;
		scammer.checkLayoutComputer( player_type[1], selected) ;
	}
}// End of scanCard()


// Writes a save game to a .txt file (user chooses name as input, file extension is included automatically)
void Game::writeSave()
{	
	// Vector for saving stockpile and layout
	vector<string> tempv;

	ofstream sfile;
	string filename = "";
	while(filename == "")
	{
		cout << "Enter a name for the file, afterwards the program will terminate: ";
		cin >> filename;
	}

	filename += ".txt";
	sfile.open(filename);

	sfile << "Round: ";
	sfile << roundNum << endl << endl;

	sfile << "Computer: " << endl;
	sfile << "\tScore: ";
	sfile << player_type[1]->getScore();
	sfile << endl;
	sfile << "\tHand: ";
	player_type[1]->getHand(tempv);
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl;		// needs computers hand vector
	sfile << "\tCapture Pile: ";
	player_type[1]->getCaptured(tempv);
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl << endl;

	sfile << "Human: " << endl;
	sfile << "\tScore: ";
	sfile << player_type[0]->getScore();
	sfile << endl;

	sfile << "\tHand: ";
	player_type[0]->getHand(tempv);
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl;

	sfile << "\tCapture Pile: ";
	player_type[0]->getCaptured(tempv);
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl << endl;

	sfile << "Layout: ";
	scammer.getLayout(tempv);
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl << endl;
	
	sfile << "Stock Pile: "; 
	scammer.getStockpile(tempv); 
	for (unsigned int i = 0; i < tempv.size(); i++)
	{
		sfile << tempv[i] + " ";
	}
	sfile << endl << endl;

	sfile << "Next Player: ";
	if (scammer.getTurn() == 'h') 
	{
		sfile << "Human" << endl;
	}
	else if (scammer.getTurn() == 'c') 
	{
		sfile << "Computer" << endl;
	}	

	sfile.close();
	endGame();
}// End of writeSave()

// Reads a users save game from a .txt file and puts all the values into the current game
void Game::readSave()
{
	vector<string> tvec;
	string filename = "";
	do
	{
		cout << "Enter the name of the file you would like to read: ";
		cin >> filename;
	}while (filename == "");

	filename += ".txt";
	ifstream sfile(filename);

	string temp = "";
	string line = "";
	int i = 0;
	int t = 0;

	if (sfile.is_open())
	{
		while( getline(sfile, line) )
		{
			switch (i)
			{
			case 0://Round:
				for (int z = line.length(); z > 5; z--)
				{
					// reads if no space is with the first character read
					if (z == line.length() && line[z] != ' ')
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						continue;
					}
					if (line[z] == ':') { break; }
					// gathers string between 2 space characters
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
					}
				}
				roundNum = stoi(temp);	// convert string to int
				temp = "";

				break;
			case 1://endl
				break;
			case 2://Computer:
				break;
			case 3://Score:
				for (int z = line.length(); z > 6; z--)
				{
					// reads if no space is with the first character read
					if (z == line.length() && line[z] != ' ')
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						continue;
					}
					if (line[z] == ':') { break; }
					// gathers string between 2 space characters
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
					}
				}
				t = stoi(temp);
				player_type[1]->writeScore(t);
				temp = "";

				break;
			case 4://Hand:
				for (int z = line.length(); z > 5; z--)
				{
					// reads if no space is with the first character read
					if (z == line.length() && line[z] != ' ') 
					{ 
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue;
					}
					if (line[z] == ':') { break; }
					// gathers string between 2 space characters
 					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				player_type[1]->writeHand(tvec);
				tvec.clear();
				break;
			case 5://Capture Pile:
				for (int z = line.length(); z > 14; z--)
				{
					if (z == line.length() && line[z] != ' ') 
					{ 
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue; 
					}
					if (line[z] == ':') { break; }
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				player_type[1]->writeCaptures(tvec);
				tvec.clear();
				break;
			case 6://endl
				break;
			case 7://Human:
				break;
			case 8://Score:
				for (int z = line.length(); z > 6; z--)
				{
					// reads if no space is with the first character read
					if (z == line.length() && line[z] != ' ')
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						continue;
					}
					if (line[z] == ':') { break; }
					// gathers string between 2 space characters
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
					}
				}
				t = stoi(temp);
				player_type[0 ]->writeScore(t);
				temp = "";
				break;
			case 9://Hand:
				for (int z = line.length(); z > 5; z--)
				{
					// reads if no space is with the first character read
					if (z == line.length() && line[z] != ' ')
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue;
					}
					if (line[z] == ':') { break; }
					// gathers string between 2 space characters
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				player_type[0]->writeHand(tvec);
				tvec.clear();
				break;
			case 10://Capture Pile:
				for (int z = line.length(); z > 14; z--)
				{
					if (z == line.length() && line[z] != ' ')
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue;
					}
					if (line[z] == ':') { break; }
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				player_type[0]->writeCaptures(tvec);
				tvec.clear();
				break;
			case 11://endl
				break;
			case 12://Layout:
				for (int z = line.length(); z > 7; z--)
				{
					if (line[z] == ' ' && z == line.length()) 
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue;
					}
					if (line[z] == ':') { break; }
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				scammer.writeLayout(tvec);
				tvec.clear();
				break;
			case 13://endl
				break;
			case 14://Stock Pile:
				for (int z = line.length(); z > 10; z--)
				{
					if (line[z] == ' ' && z == line.length())
					{
						temp = line[z];
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
						continue;
					}
					if (line[z] == ':') { break; }
					if (line[z] == ' ')
					{
						int r = 1;
						while (line[z - r] != ' ' && line[z - r] != ':')
						{
							temp = line[z - r] + temp;
							r++;
						}
						tvec.push_back(temp);
						temp = "";
					}
				}
				reverse(tvec.begin(), tvec.end());
				while(tvec[0] == " " || tvec[0] == "\0")
				{
					tvec.erase(tvec.begin());
				}
				scammer.writeStockpile(tvec);
				tvec.clear();
				break;
			case 15://endl
				break;
			case 16://Next Player:
				
				if (line[13] == 'C')
				{
					scammer.changeTurn('c');
				}
				else if (line[13] == 'H')
				{
					scammer.changeTurn('h');
				}
				break;

			default:
				cout << "ERROR - Reading save file failed - readSave() - Class Game()\n";
				break;
			}
			i++;
		}
	}

	player_type[0]->sortCaptured();
	player_type[0]->sortHand();
	player_type[1]->sortCaptured();
	player_type[1]->sortHand();

	cout << "====================================================================\n";
	cout << "   File Loaded: All cards sorted with like cards except Stock Pile\n";

	sfile.close();
}// End of readSave()