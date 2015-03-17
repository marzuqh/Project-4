#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "deck.h"
#include "card.h"
#include "player.h"

using namespace std;

int main()
{
	Player *challenger;
	challenger = get_Counting();

	Card c;
	c.spot = 2;
	c.suit = SPADES;

	challenger->shuffled();

	challenger->expose(c);
	challenger->expose(c);
	challenger->expose(c);

	unsigned int minimum = 5;
	unsigned int bankroll = 100;

	unsigned int wager = challenger->bet(bankroll, minimum);

	if(wager != 2*minimum)
	{
		return -1;
	}

	bankroll = 9;
	wager = challenger->bet(bankroll, minimum);
	
	if(wager != bankroll)
	{
		return -1;
	}

	challenger->shuffled();
	wager = challenger->bet(bankroll, minimum);
	
	if(wager != minimum)
	{
		return -1;	
	}	

	return 0;
}
