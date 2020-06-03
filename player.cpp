#include <iostream> //cin and cout
#include <stdlib.h>
#include "deckOfCards.h" //deck header file
#include "card.h" //card header file
#include "player.h" //player header file
#include <string> //stoi
#include <climits> //for INT_MAX limits


#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* MAGENTA*/
#define YELLOW  "\033[33m"      /* Yellow */
#define CYAN   "\033[36m"      /* CYAN */
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"


//sets player name in attributes
void player::set(string name)
{
	playername = name; //sets player name
}


//prints player name
void player::view()
{
	cout << playername; //prints player names
}


//sets up a hand to point to deck location for certain player and also makes a copy as a separate array called actual hand
void player::setupHand(card *deck, int location)
{
	hand = &deck[location]; //setting hand to specific part in deck location. from location as start and the next 12 cards
	
	for (int i=0; i<13; i++) //copying deck hand locations into a hand arr
	{
		ActualHand[i]=deck[location+i]; //making an actual hand as a copy from deck location to avoid changeing the shuffled deck
	}
}


//displays hand
void player::viewHand()
{
	for(int a = 0 ; a < 13 ; a++) //prints out 13 cards in hand
	{
		cout << (a+1) << ". "; //prints out cards positions for input reference
		ActualHand[a].view(); //displays card
		cout << endl;
	}
	cout<<endl<<endl<<endl;
}


//returns pointer to actual hand
card *player::getHandPointer()
{
	card *CardPointer = &ActualHand[0];//retursn pointer to players actual hand
	return CardPointer;
}


// ~***~//FOR WINDOW/WIN CONDITION CHECK -> if this value is equal to zero, they win. 
//Returns int for size of hand. Will have a if condition where size==0 end game
int player::getHandsize()
{ 
	//HandPlayer variable... card hand  ? //Shows how many cards are in are currently in he Player's hands
	//maybe switch statement to grab each player's actual hand?
	//add eg PlayerOne.getHandSize() before PlayerOne.viewHand() ?
	// need this --> # define my_sizeof(type) ((char *)(&type+1)-(char*)(&type)) //my_sizeof macro
	//int numberOfCardsInHand = my_sizeof(array)/my_sizeof(array[0]);  //n is the number of 'cards' in the player's hands

	card *hand = ActualHand; //pointer to actual hand of player

	int index=0; //for newhand indexer
	int size = 0; //starting the amount of cards at 0

	//loop makes a new hand based on missing cards in old hand
	for (int i = 0; i < 13; i++) //goes through 13 hand array
	{ 
		if(hand[i].getValue() > 0) //if cards are not empty slots
		{ //going every iteration in hand, if the number is bigger than 0, the card is not empty
			size++; //increase card size count, because the place is not empty, and has a number bigger than 0
		}
	}


	cout << playername << " has " << MAGENTA << size << RESET << " cards left in their hands!" << endl; //prints how many cards left in hand
	return size ; // returns hand size
}


//takes in num of cards to play and creates an arr of card positions of players (int) from actual hand arr
int *player::PlayCard(int numPlay)
{
	int *cardsChosen = new int[numPlay];//makes a pointer to an int array

	for(int a = 0 ; a < numPlay ; a++) //iterates the amount of cards to be played
	{
		//int placeholderint=0; //used to offset values by -1
		int placeholderint;

		cout << YELLOW << "\nIf multiple duplicates are in last played pile and you don't have a higher amount same duplicates played. Type in 14 for skip\n";;
		cout << YELLOW << "Please input the a card position to be played (repeat in order and press enter): \n" << RESET;
		
		cin >> placeholderint;

		while (cin.fail()) //when cin detects anything but an int
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\n\nIf multiple duplicates are in last played pile and you don't have a higher amount same duplicates played. Type in 14 for skip\n";
			cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
			cout << RED << "Please input the a card position to be played (repeat in order and press enter): \n" << RESET;
			cin >> placeholderint;
		}

		cout << endl << endl;
		
		if (placeholderint == 14) //returns 14 for manual skip
			{
				cardsChosen[0]=placeholderint; //sets cardsChosen as 14
				return cardsChosen; //returns 14
			}
		
		if ((placeholderint < 1)  && (placeholderint > 14)) //if card position to be played is not valid
		{
			cout <<  RED << "\n*** Invalid. Enter a number between 1 and 13 based on the cards above. ***" << RESET << endl;

			while ((placeholderint < 1) && (placeholderint > 14)) //keep asking till a valid card position is entered
			{	
				cout << BLUE << "Please input the card position to be played (in order): \n" << RESET;
				cin >> placeholderint;
			}   
			cardsChosen[a] = placeholderint-1;
			//return cardsChosen; //card that has the position of the cards
		}
		cardsChosen[a] = placeholderint-1; //card that has the position of the cards
	}
	return cardsChosen; //returns pointer to cards chosen with positions as content
}


//first input check for start of round
bool player::FirstInputChecker(int CardAmount, int *CardsPlayed)
{
	int InputType;


	if(ActualHand[CardsPlayed[0]].getValue() == 0)
		{
			cout << RED << "\n *** Card slot is EMPTY and is invalid. Choose another card slot!" << RESET << endl << endl;
			return false;
		}

	if(CardAmount==1) //one card played
	{
		InputType=0;
	}
	else if(ActualHand[CardsPlayed[0]].getValue() == ActualHand[CardsPlayed[1]].getValue()) //if initial val card is equal to next card
	{
		InputType = 1; //duplicates detected
	}
	else if((ActualHand[CardsPlayed[0]].getValue() - ActualHand[CardsPlayed[1]].getValue()) == -1) //decks actual hand cards for ascending
	{		
		cout << (ActualHand[CardsPlayed[0]].getValue() - ActualHand[CardsPlayed[1]].getValue());
		InputType = 2; //ascending detected
	}
	else
	{
		cout << RED << "\n *** Card input invalid ***\n" << RESET;
		return false;
	}

	int PlaceHolder1, PlaceHolder2; //holds card

	//cout << "inputtype integer" << InputType <<endl; debugging code for checking input type

	switch(InputType) //switch to check depending on input type
	{
		case 0:
			if (CardsPlayed[0]==-1)
			{
				return false; //returns false if invalid -1 position is detected.
			}
			else
			{
				return true; //valid single card position
			}
			break;

		//checks if cards in hand entered are duplicates
		case 1:
			for(int i = 0 ; i < CardAmount-2 ; i++) //checks cards input with an offset of two since it starts at 0
			{ 
				//setting up place holders with cards card[0] and card[1] from hand
				PlaceHolder1 = ActualHand[CardsPlayed[i]].getValue(); //checks if the duplicates are matching
				cout << PlaceHolder1 << " ";
				
				PlaceHolder2 = ActualHand[CardsPlayed[i+1]].getValue();
				cout << PlaceHolder2 << endl;
				
				if(PlaceHolder1 != PlaceHolder2) //if first card doesn't equal second card in value
				{
					cout << RED << "\n *** Cards played are NOT ASCENDING ***" << RESET << endl; //debugging code
					return false; //fails duplicate input check
				}
			}
			break;

		//checks if it actually is in ascending order
		case 2:
			for(int i = 0 ; i < CardAmount -2 ; i++)//checks cards input with an offset of two since it starts at 0
			{   
				//setting up place holders with cards card[0] and card[1] from hand
				
				PlaceHolder1 = ActualHand[CardsPlayed[i]].getValue(); //setting card [0] in place holder
				cout<< PlaceHolder1 << " " << ActualHand[CardsPlayed[i]].getValue() << endl; //

				PlaceHolder2 = ActualHand[CardsPlayed[i+1]].getValue();//setting card [1] in place holder
				cout<< PlaceHolder2 << " " << ActualHand[CardsPlayed[i+1]].getValue() << endl;

				if(PlaceHolder1 != PlaceHolder2-1) //if the cards do not ascend
				{
					cout << RED << "*** Cards played are NOT ASCENDING ***" << RESET <<endl;
					return false;//fails ascend input check
				}
			}
			break;
	}
	return true; //passes input check
}


//singular input checker
//checks inputs if only one card is played by player. Board will be passed into last card
bool player::inputCheck(int *CardPlayed, card *LastCard)
{
	/*first if statement checks for the value if it is larger, if it is then suit doesn't matter and it returns true
	Second if statements check for the value if it is the same, then it checks the suit, if it is larger then it returns true.
	in all iterations of returning true, it reduces the cardtracker (no. of cards in hand) by 1
	*/
	


    if(ActualHand[CardPlayed[0]].getValue() >= LastCard[0].getValue() && LastCard[0].getValue() != 0) 
		{ //Comparing the card's value
			cardtracker = cardtracker - 1;

		

			if(ActualHand[CardPlayed[0]].getValue() == LastCard[0].getValue() && ActualHand[CardPlayed[0]].getValue() !=0 && LastCard[0].getValue() != 0)
			{

				if( (ActualHand[CardPlayed[0]].getSuit() > LastCard[0].getSuit()) && ActualHand[CardPlayed[0]].getSuit() !=0 && LastCard[0].getSuit() != 0)
				{ //Comparing the card's suit
					cardtracker = cardtracker - 1;
					return true; //return TRUE
				}
				else
				{
					cout << RED << "\n *** Card SUIT PLAYED isn't HIGHER than the card last played *** " << RESET << endl;

					cout << RED << "Remember from the rules:\n\t\t Suit: ♠ Spades < ♣ Clubs < ♢ Diamonds < ♡ Hearts" << endl;

					return false; //return FALSE
				}
			}

			return true;
		}

		//when 'card value' is 0 (no value) = empty slot
		if(ActualHand[CardPlayed[0]].getValue() == 0)
		{
			cout << RED << "\n *** Card slot is EMPTY or you have selected this option before and is invalid. Choose another card slot!" << RESET << endl << endl;
			return false;
		}
		

	cout << RED << "\n *** Card VALUE PLAYED isn't HIGHER than the card last played ***" << RESET << endl;

	cout << RED << "Remember from the rules: \n\t\t Number: 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < Jack < Queen < King < Ace < 2" << endl;

	return false; //return FALSE

}


//multiple inputs checker
//checks input if multiple cards are played by player. Board will be passed into last card
bool player::inputCheckMulti(int CardAmount, int *CardsPlayed, card *LastCard)
{ //CardsPlayed is a pointer to an int array of cards chosen

	//this if statement checks if the last card to be played is larger than last card on the board
	if(ActualHand[CardsPlayed[CardAmount-1]].getValue() > LastCard[CardAmount-1].getValue() && ActualHand[CardsPlayed[CardAmount-1]].getSuit() !=0 && LastCard[CardAmount-1].getSuit() != 0)
	{
		cardtracker = cardtracker - 1;
		return true;
	}
	else if(ActualHand[CardsPlayed[CardAmount-1]].getValue() == LastCard[CardAmount - 1].getValue() && ActualHand[CardsPlayed[CardAmount-1]].getSuit() !=0 && LastCard[CardAmount-1].getSuit() != 0)
	{
		if(ActualHand[CardsPlayed[CardAmount-1]].getSuit() > LastCard[CardAmount-1].getSuit() && ActualHand[CardsPlayed[CardAmount-1]].getSuit() !=0 && LastCard[CardAmount-1].getSuit() != 0)
		{
			cardtracker = cardtracker - CardAmount;
			return true;
		}
		else if(ActualHand[CardsPlayed[CardAmount-1]].getSuit() < LastCard[CardAmount-1].getSuit() && ActualHand[CardsPlayed[CardAmount-1]].getSuit() !=0 && LastCard[CardAmount-1].getSuit() != 0)
		{
			cout << RED << "\n *** Invalid card input: SUIT *** " << RESET << endl;
			return false;
		}
	}
	//test
	cout<< RED << "\n *** Invalid card input: VALUE ***" << RESET <<endl;
	return false;


	int InputType;// checks if the LastCards played are duplicates or ascending flushes, 1 or duplicates, 2 for flushes


	if((LastCard[0].getValue() == LastCard[1].getValue()) && LastCard[0].getValue() != 0 && LastCard[1].getValue() != 0)
	{	//checks for duplicates
		InputType = 1;
	}
	else if( ((LastCard[0].getValue() - LastCard[1].getValue()) == -1) && LastCard[0].getValue() != 0 && LastCard[1].getValue() != 0) // lower - higher = -1
	{ 	//checks for ascending
		InputType = 2;
	}
	else
	{
		cout << RED << "\n *** Cards are either NOT DUPLICATES or in ASCENDING order or NOT ONE VALUE HIGHER/LOWER than last card played ***" << endl;
		return false;
	}
	
	
	int PlaceHolder1, PlaceHolder2; //place to start value ints

	//switch statement to see which for loop to use to check, both cases return false to check if it doesn't meet
	//the criteria for ascending flush or duplicates
	switch(InputType)
	{
		case 1:
			for(int i = 0 ; i < CardAmount-1 ; i++)
			{ //checks if the duplicates are matching
				PlaceHolder1 = ActualHand[CardsPlayed[i]].getValue();
				//cout << PlaceHolder1 << " ";
				PlaceHolder2 = ActualHand[CardsPlayed[i+1]].getValue();
				//cout << PlaceHolder2 << endl;

				if(PlaceHolder1 != PlaceHolder2)
				{
					cout << RED <<"\n *** Cards played are NOT DUPLICATES ***" << RESET << endl;
					return false;
				}
			}
			break;


		case 2:
			for(int i = 0 ; i < CardAmount -1 ; i++)
			{ //checks if it actually is in ascending order
				PlaceHolder1 = ActualHand[CardsPlayed[i]].getValue();
				PlaceHolder2 = ActualHand[CardsPlayed[i+1]].getValue();

				if((PlaceHolder1 - PlaceHolder2) != -1) //if difference isn't 1
				{
					cout<< RED << "\n *** Cards played are NOT in ASCENDING order ***" << RESET << endl;
					return false;
				}
			}
	}


	
}


//constructor
player::player()
{
	playername = "???";
};


//deconstructor
player::~player(){};



