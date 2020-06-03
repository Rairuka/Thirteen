#include <iostream> //cin and cout
#include <stdlib.h>
#include "card.h" //card.h declarations
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define YELLOW  "\033[33m"      /* Yellow */
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"

using namespace std;


card::card(){}

card::~card(){}

card::card(int cardValue, int cardSuit)	//sets card value and suite
{
	value = cardValue;
	suit = cardSuit;
}


void card::view() //prints the cards attributes
{
	switch(value){
		case 11:
			cout << "J";
			break;
		case 12:
			cout << "Q";
			break;
		case 13:
			cout << "K";
			break;
		case 14:
			cout << "A";
			break;
		case 15:
			cout << "2";
			break;
		case 0:
			cout << "***empty hand slot***";
			return;
			break;
		default:
			cout << value;
			break;
	}

	cout << " of ";

	switch(suit){
		case 1:
			cout << "Spades ♠";
			break;
		case 2:
			cout << "Clubs ♣";
			break;
		case 3:
			cout << "Diamonds " << RED << "♦" << RESET;// ♢ spare copy
			break;
		case 4:
			cout << "Hearts " << RED << "♥" << RESET; //♡ spare copy
			break;
		case 0:
			cout << " ";
			return;
			break;


		default:
			break;
	}
	//return (value + " of " + suit);
}


int card::getValue()//to access the card value
{ 
	return value;
}


int card::getSuit()//to access the card suit
{ 
	return suit;
}


