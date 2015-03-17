#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "deck.h"
#include "card.h"

using namespace std;

int main()
{
	Deck d;
	d.reset();
	d.deal();
	d.deal();

	if(50 != d.cardsLeft())
	{
		return -1;
	}

	d.reset();

	if(52 != d.cardsLeft())
	{
		return -1;
	}
	
	else return 0;
}
