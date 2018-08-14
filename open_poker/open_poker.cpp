/****************************************************************************
*                A simple Texas Hold'em Poker simulartion.                 *
*                Program runs fine, but gameplay still has some bugs.      *
****************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#ifdef __linux__ 
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

const int suits_count = 4;
const int ranks_count = 13;
const int sleep_time = 1;
// Player index
const int player_index = 4;

std::string suits[suits_count];
std::string ranks[ranks_count];

void press_Enter()
{
	printf("\nPress Enter to continue.\n");
	while (getchar() != '\n');
}

void _sleep(int time)
{
#ifdef __linux__ 
	sleep(time);
#elif _WIN32
	Sleep(time);
#endif
}

class Card
{
	public:
		int suit;
		int rank;
};

int compareCards(const void *card1, const void *card2)
{
	return (*(Card *)card1).rank - (*(Card *)card2).rank;
}

class Deck
{
	private:
		int top;
		static const int card_tally = 52;

		Card cards[card_tally];

	public:
		Deck()
		{
			for (int i = 0; i < suits_count; i++)
			{
				for (int j = 0; j < ranks_count; j++)
				{
					cards[i * ranks_count + j].suit = i;
					cards[i * ranks_count + j].rank = j;
				}
			}
			suits[0] = "D";
			suits[1] = "S";
			suits[2] = "H";
			suits[3] = "C";

			ranks[0] = "2";
			ranks[1] = "3";
			ranks[2] = "4";
			ranks[3] = "5";
			ranks[4] = "6";
			ranks[5] = "7";
			ranks[6] = "8";
			ranks[7] = "9";
			ranks[8] = "T";
			ranks[9] = "J";
			ranks[10] = "Q";
			ranks[11] = "K";
			ranks[12] = "A";
		}

		void print()
		{
			std::cout << "Printing the deck..." << std::endl;
			_sleep(1);
			for (int i = 0; i < card_tally; i++)
				std::cout << ranks[cards[i].rank] << suits[cards[i].suit] << std::endl;
			printf("\n");
		}

		void shuffle()
		{
			top = card_tally - 1;

			for (int i = 0; i < suits_count; i++)
			{
				for (int j = 0; j < ranks_count; j++)
				{
					cards[i * ranks_count + j].suit = i;
					cards[i * ranks_count + j].rank = j;
				}
			}

			int x;
			Card tempCard;
			for (int i = 0; i < card_tally; i++)
			{
				x = rand() % card_tally;
				tempCard = cards[i];
				cards[i] = cards[x];
				cards[x] = tempCard;
			}
		}

		Card hitme()
		{
			top--;
			return cards[top + 1];
		}
};

class Player
{
	public:
		std::string name;
		int money;
		Card cards[2];
		bool playing;
		int round;
		int goodToGo;
};

class PokerGame
{
	public:
		void start(const std::string &name)
		{
			for (int i = 0; i < players_count; i++)
			{
				players[i].money = 1000;
				players[i].playing = true;
			}

			players[0].name = "Wojciech";
			players[1].name = "Tristan";
			players[2].name = "Michal";
			players[3].name = "Edyta";
			players[player_index].name = name;
			players[5].name = "Kamil";

			startGame();
		}


		void deal()
		{
			for (int i = 0; i < players_count; i++)
				for (int j = 0; j < 2; j++)
					if (players[i].playing)
						players[i].cards[j] = deck1.hitme();
						
			for (int i = 0; i < 5; i++)
				tableCards[i].rank = -1;
		}

		void flop()
		{
			for (int i = 0; i < 3; i++)
				tableCards[i] = deck1.hitme();
		}

		void turn()
		{
			tableCards[3] = deck1.hitme();
		}

		void river()
		{
			tableCards[4] = deck1.hitme();
		}

		void printTable()
		{
			using std::cout;
			using std::endl;
			using std::setw;

			cout << "------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "  " << ((players[0].playing) ? (players[0].name) : "      ") << "         " << ((players[1].playing) ? (players[1].name) : "     ") << "           "
				<< ((players[2].playing) ? (players[2].name) : "    ") << endl;
			cout << "   $" << setw(4) << ((players[0].playing) ? (players[0].money) : 0) << "         $" << setw(4) << ((players[1].playing) ? (players[1].money) : 0)
				<< "           $" << setw(4) << ((players[2].playing) ? (players[2].money) : 0) << endl;
			cout << "     _____________________________" << endl;
			cout << "    / " << ((bind == 0) ? "@" : " ") << "            " << ((bind == 1) ? "@" : " ") << "            " << ((bind == 2) ? "@" : " ") << " \\" << endl;
			cout << "   /  ___   ___   ___   ___   ___  \\" << endl;
			cout << "   | | " << ((tableCards[0].rank) >= 0 ? ranks[tableCards[0].rank] : " ") << " | | " << ((tableCards[1].rank) >= 0 ? ranks[tableCards[1].rank] : " ") << " | | " << ((tableCards[2].rank) >= 0 ? ranks[tableCards[2].rank] : " ") << " | | "
				<< ((tableCards[3].rank) >= 0 ? ranks[tableCards[3].rank] : " ") << " | | " << ((tableCards[4].rank) >= 0 ? ranks[tableCards[4].rank] : " ") << " | |" << endl;
			cout << "   | | " << ((tableCards[0].rank) >= 0 ? suits[tableCards[0].suit] : " ") << " | | " << ((tableCards[1].rank) >= 0 ? suits[tableCards[1].suit] : " ") << " | | " << ((tableCards[2].rank) >= 0 ? suits[tableCards[2].suit] : " ") << " | | "
				<< ((tableCards[3].rank) >= 0 ? suits[tableCards[3].suit] : " ") << " | | " << ((tableCards[4].rank) >= 0 ? suits[tableCards[4].suit] : " ") << " | |" << endl;
			cout << "   | |___| |___| |___| |___| |___| |" << endl;
			cout << "   |                               |" << endl;
			cout << "   |	       Pot = $" << setw(4) << pot << "         |" << endl;
			cout << "   \\                               /" << endl;
			cout << "    \\_" << ((bind == 5) ? "@" : "_") << "_____________" << ((bind == 4) ? "@" : "_") << "___________" << ((bind == 3) ? "@" : "_") << "_/" << endl;
			cout << endl;
			cout << "  " << ((players[5].playing) ? (players[5].name) : "      ") << "          " << ((players[player_index].playing) ? (players[player_index].name) : "      ") << "         "
				<< ((players[3].playing) ? (players[3].name) : "    ") << endl;
			cout << "   $" << setw(4) << ((players[5].playing) ? (players[5].money) : 0) << "          $" << setw(4) << ((players[player_index].playing) ? (players[player_index].money) : 0)
				<< "         $" << setw(4) << ((players[3].playing) ? (players[3].money) : 0) << endl;
			cout << endl;
			if (players[player_index].round)
			{
				cout << "   Your hand:" << endl;
				cout << "    ___    ___" << endl;
				cout << "   | " << ranks[players[player_index].cards[0].rank] << " |  | " << ranks[players[player_index].cards[1].rank] << " |" << endl;
				cout << "   | " << suits[players[player_index].cards[0].suit] << " |  | " << suits[players[player_index].cards[1].suit] << " |" << endl;
				cout << "   |___|  |___|" << endl << endl;
			}

			_sleep(3);
		}

	private:
		static const int players_count = 6;
		Player players[players_count];
		Deck deck1;
		int bind;
		Card tableCards[5];
		int pot, action, bet, rational, betOn, winner, maxPoints, roundWinner;
		enum poker_action {FLOP = 1, CHECK = 2, BET_or_CALL = 3};
		int handPoints[6];
		int bestHand[6][3];

		int playersLeft()
		{
			int count = 0;
			for (int i = 0; i < players_count; i++)
				if (players[i].money > 0)
					count++;
			return count;
		}

		int computerAction(int playerNum)
		{
			if (players[playerNum].cards[0].rank < 8 && players[playerNum].cards[1].rank < 8)
			{
				if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
					return 0;
				else
					return 1;
			}

			else if (players[playerNum].cards[0].rank < 10 && players[playerNum].cards[1].rank < 10)
			{
				if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
					return 1;
				else
					return 2;
			}
			else
				return 2;
		}

		/*checks if someone still got bet/call*/
		bool playersToBet()
		{
			for (int i = 0; i < players_count; i++)
				if (players[i].round == 1 && players[i].goodToGo == 0)
					return true;

			return false;
		}
		
		// Computer random action
		int computer_random(int options)
		{
			/* Options argument describe range from zero to given value
			 * eg options = 3 -> values from range 0-2, +1 makes it human friendly
			 * so range becomes 1-3 */
			int chosen_option = (rand() % options) + 1;
			return chosen_option;
		}
		
		// Handles bets from human player
		void human_bet(int current_player)
		{
			using std::cout;
			using std::cin;
			using std::endl;
			
			cout << "How much do you want to bet: ";
			cin >> bet;

			while (bet > players[current_player].money || bet < 1)
			{
				cout << "Invalid number to bet." << endl;
				cout << "How much do you want to bet: ";
				cin >> bet;
				cout << endl << endl;
			}
		
			pot += bet;
			players[current_player].money -= bet;
			betOn = bet;
			players[current_player].goodToGo = 1;

			cout << "\t+ " << players[current_player].name << " bets " << bet << "$\n";
		}
		
		// Handles bets from computer players
		void computer_bet(int current_player)
		{
			using std::cout;
			using std::cin;
			using std::endl;
			
			bet = (rand() % (players[current_player].money / 3) + 10);
			pot += bet;
			players[current_player].money -= bet;
			cout << '\a';
			cout << "\t+ " << players[current_player].name << " bets " << bet << "$" << endl;
			betOn = bet;
			players[current_player].goodToGo = 1;
		}
		
		// Handle player's action
		void handle_action(int action, int current_player)
		{
			using std::cout;
			using std::cin;
			using std::endl;
			
			bool human;
			// Check if player is human or computer player
			if (current_player == player_index)
				human = true;
			else
				human = false;
			
			switch (action)
			{
				case FLOP:
					players[current_player].round = 0;
					cout << "\t- " << players[current_player].name << " flops...\n";
					break;
				case CHECK:
					cout << "\t+ " << players[current_player].name << " checks.\n";
					break;
				case BET_or_CALL:
					if (betOn)
					{
						pot += betOn;
						players[current_player].money -= betOn;
						players[current_player].goodToGo = 1;
						cout << "\t++ " << players[current_player].name << " calls!" << endl;
					}
					else
					{
						// If current player is human player prompt user for bet
						if (human)
							human_bet(current_player);
						// Else get random bet from computer
						else
							computer_bet(current_player);
					}
					break;
			}
		}

		void takeBets()
		{
			using std::cout;
			using std::cin;
			using std::endl;

			int current_player;

			betOn = 0;
			for (int k = 0; k < players_count; k++)
				players[k].goodToGo = 0;

			for (int k = bind + 1; k < bind + 7; k++)
			{
				current_player = k % players_count;
				/* human player actions */
				if (current_player == player_index && players[player_index].round)
				{
					// Player can FLOP or CALL
					if (betOn)
					{
						// Player has money and it's more or equal to current bet on the table
						if (players[player_index].money != 0 && players[player_index].money >= betOn)
						{
							cout << "\t\t\t\t\tYour action: (1) FLOP (3) CALL ";
							cin >> action;
							while (action != FLOP && action != BET_or_CALL)
							{
								cout << "Invalid number pressed." << endl;
								cout << "\t\t\t\t\tYour action: (1) FLOP (3) CALL ";
								cin >> action;
							}
						}
						// Else player can only pass
						else
						{
							cout << "\t\t\t\t\tYour action: (1) FLOP ";
							cin >> action;
							while (action != FLOP)
							{
								cout << "Invalid number pressed." << endl;
								cout << "\t\t\t\t\tYour action: (1) FLOP ";
								cin >> action;
							}
						}
					}
					// Else player can bet, check or flop.
					else
					{
						if (players[player_index].money > 0)
						{
							cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK (3) BET ";
							cin >> action;
							// Action is outside 1 - 3 range
							while (action < FLOP || action > BET_or_CALL)
							{
								cout << "Invalid number pressed." << endl;
								cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK (3) BET ";
								cin >> action;
							}
						}
						else
						{
							cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK ";
							cin >> action;
							while (action != FLOP && action != CHECK)
							{
								cout << "Invalid number pressed." << endl;
								cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK ";
								cin >> action;
							}
						}
					}
					cout << endl;
					
					// Handle player's action
					handle_action(action, player_index);
				}
				/* computers actions */
				else
				{
					if (players[current_player].round == 0)
						continue;
					
					// 0 - not rational, 1 - rational
					rational = rand() % 2;
					
					// Computer is rational
					if (rational)
					{
						action = computerAction(current_player) + 1;
						if (players[current_player].money < betOn)
							action = FLOP;
						while (betOn && action == CHECK)
							action = computer_random(3);
					}
					// Computer is not rational
					else
					{
						// Choose from range 1-3, FLOP = 1, CHECK = 2, BET/CALL = 3
						action = computer_random(3);
						
						// Computer can only flop if it doesn't have enough money
						if (betOn && players[current_player].money < betOn)
							action = FLOP;
						while (betOn != 0 && action == CHECK)
							action = computer_random(3); // Computer cannot CHECK if bet is on
					}
					// Handle computer's action
					handle_action(action, current_player);
					_sleep(1);
				}
			}

			if (betOn && playersToBet())
			{
				for (int k = bind + 1; k < bind + 7; k++)
				{
					// Player's action
					if (current_player == player_index)
					{
						if (players[player_index].round && players[player_index].goodToGo == 0)
						{
							// Player has money and it's more or equal to current bet on the table
							if (players[player_index].money != 0 && players[player_index].money >= betOn)
							{		
								cout << "\t\t\t\t\tYour action: (1) FLOP (3) CALL ";
								cin >> action;
								while (action != FLOP && action != BET_or_CALL)
								{
									cout << "Invalid number pressed." << endl;
									cout << "\t\t\t\t\tYour action: (1) FLOP (3) CALL ";
									cin >> action;
								}	
							}
							// Else player can only pass
							else
							{
								cout << "\t\t\t\t\tYour action: (1) FLOP ";
								cin >> action;
								while (action != FLOP)
								{
									cout << "Invalid number pressed." << endl;
									cout << "\t\t\t\t\tYour action: (1) FLOP ";
									cin >> action;
								}
							}
							// Handle player's action
							handle_action(action, player_index);
						}
					}
					// Computer's action
					else
					{
						if (players[current_player].round == 0 || players[current_player].goodToGo == 1)
							continue;
						// Choose from range 1-3, FLOP = 1 BET/CALL = 3
						action = computer_random(3);
						
						while (action == CHECK)
							action = computer_random(3); // Computer cannot CHECK if bet is on
							
						// Do not let computer to BET if it doesn't have enough of money
						if (action == BET_or_CALL && players[current_player].money < betOn)
							action = FLOP; // Computer has no other option other than to FLOP

						// Handle computer's action
						handle_action(action, current_player);
					}
				}
			}
		}

		bool oneLeft()
		{
			int count = 0;
			for (int k = 0; k < players_count; k++)
				if (players[k].round)
					count++;
			if (count == 1)
				return true;
			else
				return false;
		}

		int getWinner()
		{
			int winner;
			for (int k = 0; k < players_count; k++)
				if (players[k].round)
					winner = k;
			return winner;
		}

		int getScore(Card hand[])
		{
			qsort(hand, 5, sizeof(Card), compareCards);
			int straight, flush, three, four, full, pairs, high;
			int k;

			straight = flush = three = four = full = pairs = high = 0;
			k = 0;

			/*checks for flush*/
			while (k < 4 && hand[k].suit == hand[k + 1].suit)
				k++;
			if (k == 4)
				flush = 1;

			/* checks for straight*/
			k = 0;
			while (k < 4 && hand[k].rank == hand[k + 1].rank - 1)
				k++;
			if (k == 4)
				straight = 1;

			/* checks for fours */
			for (int i = 0; i < 2; i++)
			{
				k = i;
				while (k < i + 3 && hand[k].rank == hand[k + 1].rank)
					k++;
				if (k == i + 3)
				{
					four = 1;
					high = hand[i].rank;
				}
			}

			/*checks for threes and fullhouse*/
			if (!four)
			{
				for (int i = 0; i < 3; i++)
				{
					k = i;
					while (k < i + 2 && hand[k].rank == hand[k + 1].rank)
						k++;
					if (k == i + 2)
					{
						three = 1;
						high = hand[i].rank;
						if (i == 0)
						{
							if (hand[3].rank == hand[4].rank)
								full = 1;
						}
						else if (i == 1)
						{
							if (hand[0].rank == hand[4].rank)
								full = 1;
						}
						else
						{
							if (hand[0].rank == hand[1].rank)
								full = 1;
						}
					}
				}
			}

			if (straight && flush)
				return 170 + hand[4].rank;
			else if (four)
				return 150 + high;
			else if (full)
				return 130 + high;
			else if (flush)
				return 110;
			else if (straight)
				return 90 + hand[4].rank;
			else if (three)
				return 70 + high;

			/* checks for pairs*/
			for (k = 0; k < 4; k++)
				if (hand[k].rank == hand[k + 1].rank)
				{
					pairs++;
					if (hand[k].rank>high)
						high = hand[k].rank;
				}

			if (pairs == 2)
				return 50 + high;
			else if (pairs)
				return 30 + high;
			else
				return hand[4].rank;
		}

		int tryHand(int array[], int player)
		{
			Card hand[5];

			/* get cards from table and player */
			for (int i = 1; i < 4; i++)
				hand[i - 1] = tableCards[array[i]];

			for (int i = 0; i < 2; i++)
				hand[i + 3] = players[player].cards[i];

			return getScore(hand);

		}

		void evaluateHands()
		{
			int stack[10], k;
			int currentPoints;

			for (int q = 0; q < players_count; q++)
			{
				if (players[q].round)
				{
					stack[0] = -1; /* -1 is not considered as part of the set */
					k = 0;
					while (1) {
						if (stack[k] < 4)
						{
							stack[k + 1] = stack[k] + 1;
							k++;
						}

						else
						{
							stack[k - 1]++;
							k--;
						}

						if (k == 0)
							break;

						if (k == 3)
						{
							currentPoints = tryHand(stack, q);
							if (currentPoints > handPoints[q])
							{
								handPoints[q] = currentPoints;
								for (int x = 0; x < 3; x++)
									bestHand[q][x] = stack[x + 1];
							}
						}
					}
				}
			}
		} /*end of evaluateHands() */

		void printWinningHand(int winner)
		{
			using std::cout;
			using std::endl;

			// Best cards for each of players
			Card playerBestHand[5];
			// Fetch best cards from the table
			for (int i = 0; i < 3; i++)
				playerBestHand[i] = tableCards[bestHand[winner][i]];
			// Fetch cards from the winner's hand
			for (int i = 0; i < 2; i++)
				playerBestHand[i + 3] = players[winner].cards[i];

			// Sort them and print them
			qsort(playerBestHand, 5, sizeof(Card), compareCards);

			cout << "   The winning hand:" << endl;
			cout << "   ___   ___   ___   ___   ___" << endl;
			cout << "  | " << ranks[playerBestHand[0].rank] << " | | " << ranks[playerBestHand[1].rank] << " | | " << ranks[playerBestHand[2].rank] << " | | " << ranks[playerBestHand[3].rank] << " | | " << ranks[playerBestHand[4].rank] << " |" << endl;
			cout << "  | " << suits[playerBestHand[0].suit] << " | | " << suits[playerBestHand[1].suit] << " | | " << suits[playerBestHand[2].suit] << " | | " << suits[playerBestHand[3].suit] << " | | " << suits[playerBestHand[4].suit] << " |" << endl;
			cout << "  |___| |___| |___| |___| |___|" << endl;
			cout << endl << endl;
			_sleep(3);
			
			// Print best cards combination for players who were still in the round
			for (int i = 0; i < players_count; i++)
			{
				// Skip printing winner's hand and players who flopped
				if (i != winner && players[i].round != 0)
				{
					// Fetch best cards 3 from the table
					for (int j = 0; j < 3; j++)
						playerBestHand[j] = tableCards[bestHand[i][j]];
					// Fetch cards from the other players' hand
					for (int j = 0; j < 2; j++)
						playerBestHand[j + 3] = players[i].cards[j];

					// Sort them and print them
					qsort(playerBestHand, 5, sizeof(Card), compareCards);
					
					cout << "    " << players[i].name << "'s hand:" << endl;
					cout << "   ___   ___   ___   ___   ___" << endl;
					cout << "  | " << ranks[playerBestHand[0].rank] << " | | " << ranks[playerBestHand[1].rank] << " | | " << ranks[playerBestHand[2].rank] << " | | " << ranks[playerBestHand[3].rank] << " | | " << ranks[playerBestHand[4].rank] << " |" << endl;
					cout << "  | " << suits[playerBestHand[0].suit] << " | | " << suits[playerBestHand[1].suit] << " | | " << suits[playerBestHand[2].suit] << " | | " << suits[playerBestHand[3].suit] << " | | " << suits[playerBestHand[4].suit] << " |" << endl;
					cout << "  |___| |___| |___| |___| |___|" << endl;
					cout << endl << endl;
					_sleep(3);
				}
			}
		}

		/* main gameplay function*/
		void startGame()
		{
			int i = 0;

			while (playersLeft() > 1)
			{
				/* starting default values*/
				for (int z = 0; z < players_count; z++)
					if (players[z].money<1)
					{
						players[z].playing = 0;
						players[z].round = 0;
					}
				
				for (int z = 0; z < players_count; z++)
				{
					if (players[z].playing)
						players[z].round = 1;
					handPoints[z] = -1;
				}

				for (int x = 0; x < players_count; x++)
					for (int y = 0; y<3; y++)
						bestHand[x][y] = -1;

				/* checking for game over*/
				if (players[player_index].playing == 0)
				{
					std::cout << "You are out of money, sorry." << std::endl;
					std::cout << "Game over." << std::endl;
					break;
				}

				bind = i % players_count;

				/* paying bind */
				pot = 20;
				if (players[bind].money >= 20)
					players[bind].money -= 20;
				else
					players[bind].playing = 0;

				std::cout << "\n\n\n\n\n\n\n";
				std::cout << "\t\t\t\t\t ------ ROUND " << i + 1 << " ------\n\n\n";
				_sleep(1);
				deck1.shuffle();

				/* pre-flop */
				deal();
				_sleep(sleep_time);
				printTable();
				takeBets();
				if (oneLeft())
				{
					winner = getWinner();
					std::cout << players[winner].name << " wins $" << pot << "\n\n";
					players[winner].money += pot;
					i++;
					continue;
				}

				/* flop */
				flop();
				std::cout << std::endl;
				_sleep(sleep_time);
				printTable();
				takeBets();
				if (oneLeft())
				{
					winner = getWinner();
					std::cout << players[winner].name << " wins $" << pot << "\n\n";
					players[winner].money += pot;
					i++;
					continue;
				}

				/* turn */
				turn();
				std::cout << std::endl;
				_sleep(sleep_time);
				printTable();
				takeBets();
				if (oneLeft())
				{
					winner = getWinner();
					std::cout << players[winner].name << " wins $" << pot << "\n\n";
					players[winner].money += pot;
					i++;
					continue;
				}

				/* river */
				river();
				std::cout << std::endl;
				_sleep(sleep_time);
				printTable();
				takeBets();

				evaluateHands();

				/* find and declare round winner */
				maxPoints = 0;
				for (int q = 0; q < players_count; q++)
				{
					if (players[q].round)
					{
						if (handPoints[q] > maxPoints)
						{
							maxPoints = handPoints[q];
							roundWinner = q;
						}
					}
				}
				std::cout << std::endl;
				std::cout << players[roundWinner].name << " wins $" << pot << " with ";
				if (maxPoints < 30)
					std::cout << "HIGH CARD";
				else if (maxPoints < 50)
					std::cout << "SINGLE PAIR";
				else if (maxPoints < 70)
					std::cout << "TWO PAIRS";
				else if (maxPoints < 90)
					std::cout << "THREE OF A KIND";
				else if (maxPoints < 110)
					std::cout << "STRAIGHT";
				else if (maxPoints < 130)
					std::cout << "FLUSH";
				else if (maxPoints < 150)
					std::cout << "FULL HOUSE";
				else if (maxPoints < 170)
					std::cout << "FOUR OF A KIND";
				else
					std::cout << "STRAIGHT FLUSH";
				std::cout << "\n\n";

				printWinningHand(roundWinner);

				players[roundWinner].money += pot;

				i++;
			}
	}
};


int main()
{
	std::string name;
	PokerGame game1;

	srand(time(NULL));

	using std::cout;
	using std::endl;

	cout << "Welcome to..." << endl << endl;
	cout << "#######                        ###### " << endl;
	cout << "   #    ###### #    # #####    #     #  ####  #    # ###### #####" << endl;
	cout << "   #    #       #  #    #      #     # #    # #   #  #      #    #" << endl;
	cout << "   #    #####    ##     #      ######  #    # ####   #####  #    #" << endl;
	cout << "   #    #        ##     #      #       #    # #  #   #      #####" << endl;
	cout << "   #    #       #  #    #      #       #    # #   #  #      #   #" << endl;
	cout << "   #    ###### #    #   #      #        ####  #    # ###### #    #" << endl << endl;

	cout << "Please type your name: ";
	std::cin >> name;

	cout << "OK " << name << " let's play some poker!" << endl << endl;

	game1.start(name);

	return 0;
}
