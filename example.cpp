// This is an example test case which runs a simple test involving
// your shuffle and deal functions.

#include <iostream>
#include "card.h"
#include "deck.h"

using namespace std;

int main()
{
    Deck d;
    Card before, after;
    int result = 0;

    before = d.deal();
    d.shuffle(26); // Should replace the dealt card before shuffling

    d.deal(); // Throw one away
    after = d.deal(); // Should be the same as before.

    cout << "First card in new deck: " << SpotNames[before.spot]
	 << " of " << SuitNames[before.suit] << endl;
    cout << "Second card in shuffled deck: " << SpotNames[after.spot]
	 << " of " << SuitNames[after.suit] << endl;

    if ((before.spot != after.spot) || (before.suit != after.suit)) {
	cout << "Cards don't match: TEST FAILED\n";
	result = -1;
    }

    return result;
}
