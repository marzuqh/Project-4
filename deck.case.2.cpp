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
	int a;
	
	for(a=0; a < DeckSize; a++)
	{
		d.deal();
	}

	try
	{
		d.deal();
	}

	catch(...)
	{
		return 0;
	}
	
	return -1;
}
