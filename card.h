//card.h

#ifndef CARD_H
#define CARD_H
#include "base.h" //inherit parent

using namespace std;

//class card with void view inheritanted from abstract class parent
class card : public parent   //inherits view method
{
private:
	int value;
	int suit;


public:
	card();
	~card();
	card(int cardValue, int cardSuit); //sets a card with val and suit
	void view(); //print card val and suit
	int getValue(); //access card val
	int getSuit(); //access card suit
};

#endif