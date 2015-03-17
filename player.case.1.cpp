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
	Hand player;
	Hand dealer;
	Card dealersUpCard;

	player.handValue().count = 17;
	player.handValue().soft = false;
	dealersUpCard.spot = 2;
	dealersUpCard.suit = SPADES;

	Player *challenger;
	challenger = get_Counting();

	if(challenger->draw(dealersUpCard,player))
	{
		return -1;
	}

	player.handValue().count = 11;
	
	if(!(challenger->draw(dealersUpCard,player)))
	{
		return -1;
	}

	player.handValue().count = 12;
	dealersUpCard.spot = 4;

	if(challenger->draw(dealersUpCard,player))
	{
		return -1;
	}

	player.handValue().count = 13;
	dealersUpCard.spot = 4;

	if(challenger->draw(dealersUpCard,player))
	{
		return -1;
	}

	player.handValue().soft = true;
	player.handValue().count = 18;
	dealersUpCard.spot = 7;

	if(challenger->draw(dealersUpCard,player))
	{
		return -1;
	}

	player.handValue().count = 19;

	if(challenger->draw(dealersUpCard,player))
	{
		return -1;
	}

	else return 0;
}
