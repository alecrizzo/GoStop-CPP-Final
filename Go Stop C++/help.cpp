#include "help.h"

/*
====================================================================
								HELP
====================================================================
*/

Help::Help()
{
	
}// End of Help()

void Help::giveAdvice(Player* p, Dealer d)
{
	int matches[13] = {0};		//keeps track of the amount of cards that match in the layout to the players hand
	int suits[13] = {0};		//keeps track of the suit types in player hand

	vector<string> layout;
	vector<string> hand;

	d.getLayout(layout);
	p->getHand(hand);

	// Sets up all the players values for what suits they have
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		string temp = hand[i];
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
			cout << "ERROR - giveAdvice() - Class Help()\n";
			break;
		}
	}

	// Compare player suits to layouts
	// nested if elses to determine the amount of matches by ignoring pairs and adding 3 for triple stacks
	// reccommend not reading
	for(unsigned int i = 0; i < layout.size(); i++)
	{
		string temp = layout[i];

		if (temp[0] == '1' && suits[0] > 0)
		{
			if (temp.length() == 8)
			{
				matches[0]+= 3;
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
				matches[1]+= 3;
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
				matches[2]+= 3;
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
				matches[3]+= 3;
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
				matches[4]+= 3;
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
				matches[5]+= 3;
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
				matches[6]+= 3;
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
				matches[7]+= 3;
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
				matches[8]+= 3;
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
				matches[9]+= 3;
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
				matches[10]+= 3;
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
				matches[11]+= 3;
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
				matches[12]+= 3;
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
		cout << "There are 3 matching cards, you should play a ";
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
			cout << "ERROR - giveAdvice() - Class Help()\n";
			break;
		}
		cout << recc;
		cout << " to capture a triple stack\n";
	}
	else if (most >= 1)
	{
		string recc = "";
		cout << "There's a matching card, you should play a ";
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
			cout << "ERROR - giveAdvice() - Class Help()\n";
			break;
		}
		cout << recc;
		cout << " to make a stacked pair\n";
	}else
	{
		cout << "Not many options, play any card to add it to the layout\n";
	}

}// End of giveAdvice()
