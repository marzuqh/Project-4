#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cassert>
#include "deck.h"
#include "card.h"
#include "hand.h"
#include "player.h"

using namespace std;

int convertCard(const Card a);
//my own function
//REQUIRES: card is well-formed with spot and suit
//EFFECTS: returns the int. values of cards for blackjack


int convertCard(const Card a)
{
	if(a.spot >= TWO && a.spot <= TEN)
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

////////////////////////////*Simple Player*/////////////////////////////

class Simple:public Player

{

int count;

public:

	int bet(unsigned int bankroll, unsigned int minimum);

	bool draw(Card dealer, const Hand &player);

	void expose(Card c);

	void shuffled();
};

int Simple::bet(unsigned int bankroll, unsigned int minimum)
{
	return minimum;
}

bool Simple::draw(Card dealer, const Hand &player)
//simple players draws according to specs
{
	if(player.handValue().soft== false)
	{
		if(player.handValue().count <= 11)
		{
			return true;
		}

		else if(player.handValue().count == 12 &&
			convertCard(dealer) >= 4 && 
			convertCard(dealer) <= 6)
		{
			return false;
		}
		else if(player.handValue().count >= 13 &&
			player.handValue().count <= 16 &&
			(convertCard(dealer) >= 2 && 
			 convertCard(dealer) <= 6))
		{
			return false;
		}
		else if(player.handValue().count >= 17)
		{
			return false;
		}
		else return true;
	}
	else
	{
		if(player.handValue().count == 18 &&
		  (convertCard(dealer) == 2 || 
		   convertCard(dealer) == 7 ||
		   convertCard(dealer) == 8))
		{
		   	return false;
		}
		else if(player.handValue().count >= 19)
		{
			return false;
		}
		else return true;
	}
}

void Simple::expose(Card c)
{
	//Player doesn't use expose()
}

void Simple::shuffled()
{
	//Player doesn't use shuffled()
}

//Global static instance of players
static Simple newPlayerS;

Player *get_Simple()
{
	return &newPlayerS;
}

//////////////////////////*Counting Player*//////////////////////////////

class Counting: public Simple
{
//NOT a subclass of player as it is derived from Simple
//as a result it does not need a new draw function
//because it is the same as in Simple

int counter;

public:

	int bet(unsigned int bankroll, unsigned int minimum);

	void expose(Card c);

	void shuffled();
};

int Counting::bet(unsigned int bankroll, unsigned int minimum)
{
	if(counter >=2 && bankroll >= 2*minimum)
	{
		return 2*minimum;
	}
	else if(counter >= 2 && bankroll < 2*minimum)
	{
		return bankroll;
	}
	else return minimum;
}

void Counting::expose(Card c)
{
	if(c.spot >= TEN && c.spot <= ACE)
	{
		counter--;
	}
	else if(c.spot >= TWO && c.spot <= SIX)
	{
		counter++;
	}
}

void Counting::shuffled()
{
	counter = 0;
}

//global instance

static Counting newPlayerCount;

Player *get_Counting()
{
	return &newPlayerCount;
}

/////////////////////////*Competitive Player*////////////////////////////

class Competitor: public Simple
//Not that great, but it can beat counting in a few instances
//very similar to counting, except for in bet
{
	int acount;
	int bcount;
	unsigned int lastBankRoll;//how much money had last turn
	int losses;//how many times lost in a row

	public:

		int bet(unsigned int bankroll, unsigned int minimum);
		void expose(Card c);
		void shuffled();
};

void Competitor::expose(Card c)
{
	if(c.spot >= TEN && c.spot <= ACE)
	{
		acount++;
	}
	else if(c.spot >= TWO && c.spot <= SIX)
	{
		bcount--;
	}
}

void Competitor::shuffled()
{
	acount = 0;
	bcount = 0;
}

int Competitor::bet(unsigned int bankroll, unsigned int minimum)
{
	int bet;
	
	if((bcount-acount) >= 2 &&
	   (bankroll - minimum)%bankroll < 200 &&
	    losses < 3)
	//a good amount to bet
	//Source: LOTS of testing... >_<
	{
		bet = (bankroll - (bcount - acount)*minimum)%bankroll;
	}
	else if((bcount-acount) >= 2 &&
		bankroll >=2*minimum)
	//otherwise, bet as counting player
	{
		bet = 2*minimum;
	}
	else
	{
		bet = minimum;
	}

	if(bankroll < lastBankRoll)
	//if you've lost, add to counter
	{
		losses++;
	}

	else if(bankroll > lastBankRoll)
	//if you win, you're consec losses are back to 0
	{
		losses = 0;
	}

	lastBankRoll = bankroll;
	//sets the current bankroll for the next round

	return bet;
}

static Competitor newPlayerComp;

Player *get_Competitor()
{
	return &newPlayerComp;
}
