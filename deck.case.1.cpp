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

	for(int a=0; a<4; a++)
	{
		for(int b=13*a; b < 13*(1+a); b++)
		{
			if(deck[b].spot != (Spot)(b%13))
			{
				return -1;
			}
			if(deck[b].suit != (Suit) a)
			{
				return -1;
			}
		}
	}
	return 0;
}
