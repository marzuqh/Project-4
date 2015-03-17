#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "deck.h"
#include "card.h"

using namespace std;

Deck::Deck()
{
	reset();
}

void Deck::reset()
{
	for(int a=0; a<4; a++)//assigns suits
	{
		for(int b=13*a; b < 13*(1+a);b++)//assign spots
		{
			deck[b].spot = (Spot)(b%13);
			deck[b].suit = (Suit) a;
		}
	}

	next = 0;
}

void Deck::shuffle(int c)
{
	Card leftDeck[c];
	Card rightDeck[DeckSize - c];
	int leftCount = 0;
	int rightCount = 0;

	for(int a = 0; a < c; a++)//builds right deck
	{
		leftDeck[a].spot = deck[a].spot;
		leftDeck[a].suit = deck[a].suit;
		leftCount++;
	}

	for(int a = c; a < DeckSize; a++)//builds left deck
	{
		rightDeck[rightCount].spot = deck[a].spot;
		rightDeck[rightCount].suit = deck[a].suit;
		rightCount++;
	}

	int l;
	int m = 0;
	int n = 0;

	for(l=0; l < DeckSize && m < leftCount && n < rightCount; l++)
	//assigns cards to the deck in a right-left manner
	{
		if(l%2==0)
		{
			deck[l].spot = rightDeck[n].spot;
			deck[l].suit = rightDeck[n].suit;
			n++;
		}

		else
		{
			deck[l].spot = leftDeck[m].spot;
			deck[l].suit = leftDeck[m].suit;
			m++;
		}
	}

	int far = l;//declared so -O1 can work

	if(leftCount >= rightCount)
	//checks for larger sub-deck and places the rest at the end
	{
		for(int z = far; z < DeckSize; z++)
		{
			deck[z].spot = leftDeck[m].spot;
			deck[z].suit = leftDeck[m].suit;
			m++;
		}
	}

	else
	{
		for(int x = far; x < DeckSize; x++)
		{
			deck[x].spot = rightDeck[n].spot;
			deck[x].suit = rightDeck[n].suit;
			n++;
		}
	}

	next = 0;
}

Card Deck::deal()
{
	if(next == DeckSize)
	{
		//throws exception
		throw DeckEmpty();
	}

	Card currentCard;
	currentCard.spot = deck[next].spot;
	currentCard.suit = deck[next].suit;
	next++;

	return currentCard;
}

int Deck::cardsLeft()
{
	return DeckSize - next;
}
