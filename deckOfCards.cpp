#include <iostream> //cin cout and left
#include <ctime> //time
#include "card.h" //for card type
#include "deckOfCards.h" //deck.h file


//builds the deck of cards
deckOfCards::deckOfCards()
{
	int value[] = {3,4,5,6,7,8,9,10,11,12,13,14,15}; //vars values from 3 to 2 increasing strength
	int suit[] = {1,2,3,4}; //spades>clovers>diamonds>hearts
	deck = new card[52]; //makes deck unshuffled array

	for(int count = 0; count < 52; count++)  //52 cards -> deck
		{
			deck[count] = card(value[count % 13], suit[count/13]);

		}
}

//deconstructor
deckOfCards::~deckOfCards(){}


//returns shuffled deck as a pointer
card *deckOfCards::gimmedeck()
{
	return deck;
}


//prints out the deck
void deckOfCards::view()
{
	cout << left; // modify adjustfield using manipulators
	
	for(int i = 0; i < 52; i++) //prints out all cards in deck
	{
		deck[i].view();  //prints specific card
		cout << "    "; //fills with blanks

		if	((i + 1) % 4 == 0) //condition for new line
		{
			cout<<endl;//prints 4 cards per line
		}
	}
}


//shuffles the deck using rand and time
void deckOfCards::shuffle()
{
	for(int first = 0; first < 52; first++) //shuffles deck
	{
		//rand()   % : second card is random, modulus the '52' cards in the deck. gives a number between 0 to 51.
		//+ time(0) : time(0) is the local time on the machine. adding this to the rand() % will shuffle the 
		//numbers even more randomly depending on the local time
		int second = (rand() + time(0)) % 52; 

		//card temp: temporary variable of the card, it is assigned to deck[first]. 
		//deck[first] becomes deck[second]
		//deck[second] stored back into temp
		//eg. first iteration. first = 0, card temp = deck[0], deck[0] = deck[second], 
		// the deck[second] (this one gets randomised) and this goes back to temp, and the process starts again up to 52 (the cards in the deck)
		card temp = deck[first]; //making a temp card based on deck[i]
		deck[first] = deck[second];
		deck[second] = temp;
	}
}