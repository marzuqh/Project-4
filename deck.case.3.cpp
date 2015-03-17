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
	d.shuffle(26);

	if(d.deal().spot != TWO && d.deal().suit != CLUBS)
	{
		return -1;
	}
	else return 0;
}
