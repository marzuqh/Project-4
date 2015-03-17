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

	unsigned int minimum = 5;
	unsigned int bankroll = 100;

	Card c;
	c.spot = 2;
	c.suit = SPADES;

	for(int i = 2; i < 7; i++)
	{
		c.spot = i;
		challenger->shuffled();
		challenger->expose(c);
		challenger->expose(c);
		challenger->expose(c);

		unsigned int wager = challenger->bet(bankroll, minimum);

		if(wager != 2*minimum)
		{
			return -1;
		}	
	}

	return 0;
}
