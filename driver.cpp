#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "deck.h"
#include "card.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

void shuffle(Deck &d);
//REQUIRES: a well formed deck
//EFFECTS: randomly cut deck at 7 spots
//MODIFIES: the deck


extern int get_cut();
extern Player *get_Simple();
extern Player *get_Counting();
extern Player *get_Competitor();

void shuffle(Deck &d)
{
	int cutPoint;

	for(int i = 0; i < 7; i++)
	{
		cutPoint = get_cut();
		cout << "cut at " << cutPoint << endl;
		d.shuffle(cutPoint);
	}
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		exit(-1);
	}

	unsigned int bankroll = atoi(argv[1]);
	int hand = atoi(argv[2]);
	int thishand = 0;//hand being played

	string player = argv[3];//player type that is playing

	Player *challenger;
	unsigned int minimum = 5;

	if(player == "simple")
	{
		//get the right player to play from player.cpp
		//default is competitor, if not one of the three
		challenger = get_Simple();
	}

	else if(player == "counting")
	{
		challenger = get_Counting();
	}

	else challenger = get_Competitor();

	cout << "Shuffling the deck" << endl;

	Deck a;
	Hand playerz;
	Hand dealer;
	Card dealersUpCard;//dealer's face up card
	Card playersCard;
	Card holeCard;//dealer's face down card

	shuffle(a);
	challenger->shuffled();//tells player deck has been shuffled

	while(bankroll >= minimum && hand > thishand)
	{
		//while player has money and there are hands to played
		cout << "Hand " << thishand + 1 << " bankroll ";
		cout << bankroll << endl;

		if(a.cardsLeft() < 20)
		{
			//shuffles the deck if there are less than 20 cards
			cout << "Shuffling the deck" << endl;
			shuffle(a);
			challenger->shuffled();
		}

		unsigned int wager = challenger->bet(bankroll,minimum);
		//asks challenger for his between

		cout << "Player bets " << wager << endl;

		//Deals the initial four cards to player and dealer and
		//shows the face up card to player

		//player's first card
		playersCard = a.deal();
		challenger->expose(playersCard);
		playerz.addCard(playersCard);
		cout << "Player dealt " << SpotNames[playersCard.spot];
		cout << " of " << SuitNames[playersCard.suit] << endl;

		//dealer's first card
		dealersUpCard = a.deal();
		challenger->expose(dealersUpCard);
		dealer.addCard(dealersUpCard);
		cout << "Dealer dealt " << SpotNames[dealersUpCard.spot];
		cout << " of " << SuitNames[dealersUpCard.suit] << endl;

		//player's second card
		playersCard = a.deal();
		challenger->expose(playersCard);
		playerz.addCard(playersCard);
		cout << "Player dealt " << SpotNames[playersCard.spot];
		cout << " of " << SuitNames[playersCard.suit] << endl;

		//dealer's second card
		holeCard = a.deal();
		dealer.addCard(holeCard);

		bool gameIs_On = true;

		while(gameIs_On)
		{
			if(playerz.handValue().count == 21)
			{
				//if player gets natural 21, hand ends
				//then payment occurs
				cout << "Player dealt natural 21" << endl;
				bankroll += ((wager*3)/2);
				gameIs_On = false;
			}
			else
			{
				while(challenger->draw(dealersUpCard,playerz))
				{
					//draws cards and shows to player

				playersCard = a.deal();
				challenger->expose(playersCard);
				playerz.addCard(playersCard);

				//cout player dealt such and such statement
				cout << "Player dealt ";
				cout << SpotNames[playersCard.spot];
				cout << " of ";
				cout << SuitNames[playersCard.suit];
				cout << endl;
				}

				cout << "Player's total is ";
				cout << playerz.handValue().count << endl;

				if(playerz.handValue().count > 21)
				{
					cout << "Player busts" << endl;
					bankroll -= wager;
					gameIs_On = false;
				}
			}

			if(gameIs_On)
			{
				cout << "Dealer's hole card is ";
				cout << SpotNames[holeCard.spot];
				cout << " of ";
				cout << SuitNames[holeCard.suit] << endl;
				challenger->expose(holeCard);
				//reveals hole card to player

				while(dealer.handValue().count < 17)
				{
					//dealer has to draw until his handval
					//reaches 17 or more and reveals card 
					//to player

					dealersUpCard = a.deal();
					challenger->expose(dealersUpCard);
					dealer.addCard(dealersUpCard);
					cout << "Dealer dealt ";
					cout << SpotNames[dealersUpCard.spot];
					cout << " of ";
					cout << SuitNames[dealersUpCard.suit];
					cout << endl;
				}

				cout << "Dealer's total is ";
				cout << dealer.handValue().count << endl;

				if(dealer.handValue().count > 21)
				{
					//when dealer busts
					cout << "Dealer busts" << endl;
					bankroll += wager;
					gameIs_On = false;
				}
				else if(playerz.handValue().count >
					dealer.handValue().count)
				{
					//when players hand > dealer's
					bankroll += wager;
					cout << "Player wins" << endl;
					gameIs_On = false;
				}
				else if(dealer.handValue().count >
					playerz.handValue().count)
				{
					//when player's hand < dealer's
					bankroll -= wager;
					cout << "Dealer wins" << endl;
					gameIs_On = false;
				}
				else
				//when both player and dealer tie
				cout << "Push" << endl;
				gameIs_On = false;
			}
		}
		//tosses current hands away

		playerz.discardAll();
		dealer.discardAll();
		thishand++;
	}
	cout << "Player has " << bankroll << " after " << thishand;
	cout << " hands" << endl;

	return 0;	
}
