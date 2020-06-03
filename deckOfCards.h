//deckOfCards.h

#ifndef deckOfCards_H
#define deckOfCards_H

#include <iostream>
#include "card.h" //for card types
#include "base.h" //for inheritance

using namespace std;

class deckOfCards : public parent //inherits view()
{
public:
	deckOfCards();
	~deckOfCards();
	void shuffle(); //shuffles deck
	//card dealCard(int playernum);
	void view(); //view deck
	card *gimmedeck(); //give shuffled deck pointer


private:
	card *deck; //deck card array
};

#endif