#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "card.h"
#include "hand.h"

using namespace std;

int convCard(const Card a);
//my own function
//REQUIRES: card is well-formed with spot and suit
//EFFECTS: returns the int. values of cards for blackjack

Hand::Hand()
{
	discardAll();
}

void Hand::discardAll()
{
	curValue.count = 0;
	curValue.soft = false;
}

int convCard(const Card a)
{
	if(a.spot >= TWO && a.spot <= NINE)
	{
		return a.spot+2;
		//off by two for enum vals compared to act. vals
		//so does an adjustment of two
	}
	else if(a.spot == ACE)
	{
		return 11;
	}
	else return 10;
}

void Hand::addCard (Card c)
{
	int cardValue = convCard(c);
	if(c.spot == ACE)
	{
		if(curValue.count + cardValue > 21)
		{
			//if adding soft ACE puts hand over 21, make it a 1
			//instead before adding it into the handValue
			cardValue = 1;
			curValue.count += cardValue;
			curValue.soft = false;
		}
		else
		{
			//Otherwise ACE value is 11
			curValue.count += cardValue;
			curValue.soft = true;
		}
	}
	else if(curValue.soft == true)
	//if there's an ACE in the hand
	{
		if (curValue.count + cardValue > 21)
		{
			//if the card in hand makes you over 21, make the
			//ace in your hand a 1 before adding new card

			curValue.count -= 10;
			curValue.count += cardValue;
			curValue.soft = false;
		}
		else //otherwise add new card
			curValue.count += cardValue;
	}
	else
	{
		//if it's not an ACE just add card
		curValue.count = curValue.count + cardValue;
		curValue.soft = false;
	}	
}

HandValue Hand::handValue() const
{
	return curValue;
}
