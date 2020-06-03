#include <iostream> //cin and cout
#include "tracker.h" //track header declarations
#include "card.h" //card header
#include "deckOfCards.h" //deck header
#include "player.h"


//tracker constructor
tracker::tracker()
{
    currentPlayerTurn = 0;
};


//lowest card finder for tracker::whosturn
card tracker::findLowestCard(int amountPlayers, card *shuffledDeck)
{
    //testing to check first card
    //card firstCard = shuffledDeck[0];
    //firstCard.view();
    cout << endl << endl;

    int indexnum = 0;

    for (int i=0; i<(amountPlayers*13); i++) //for loop checks through based on amount of players
    {
        if (shuffledDeck[i].getValue() < shuffledDeck[indexnum].getValue()) //if card is less in value index is recorded
        {
            //testing code
            //shuffledDeck[i].printCard();
            //cout << endl;
            //shuffledDeck[count].printCard();
            //cout << endl;
            //cout << "card is lower" << endl;
            indexnum = i;
        }
        else if(shuffledDeck[i].getValue() == shuffledDeck[indexnum].getValue())
        { //if equal value then move on to checking suit
            if(shuffledDeck[i].getSuit() < shuffledDeck[indexnum].getSuit())
            {   
                //tesing code
                //cout << "suit is lower" << endl;
                indexnum = i;
            }
        }
    }
    return shuffledDeck[indexnum]; //return lowest card information
}


//prints whose turn it is by checking where the lowest card is in the shuffled deck arr
int tracker::printWhosTurn(card temp, card *shuffledDeck, int numPlayers)
{
    int index;

    //searches deck to find where lowest card found matches in shuffled deck and records the index value
    for (int i=0;i<52;i++)
    {
        if (temp.getValue() == shuffledDeck[i].getValue())
        {
            if(temp.getSuit() == shuffledDeck[i].getSuit())
            {
                index = i+1; //for offsetting by one since arr starts at 0
            }
        }
    }
    
    //player number decider
    int player=0;
    for(int k = 0 ; k < numPlayers ; k++)
    {
        if (index > (k)*13)
        {
            if(index < (k+1)*13)
            {
                player = k+1; //for offsetting by one since arr starts at 0
            }
        }
    }
    std::cout << "The starting player is player:  " << player << "\n\n\n"; //print player number
    return player; //return player number, used for other functions
}


//view the board
void tracker:: view()
{
    cout << board;
}


bool tracker::addtoboard(int cardAmount,int *cardsPositions,card *ActualHand)
{   
    /*
    delete[] board; //deletes old board
    card *board = new card[cardAmount]; //new board for cards played and amount of it
    */

    if (ActualHand[cardsPositions[0]].getValue() != 0 && ActualHand[cardsPositions[0]].getSuit() != 0)
    {

            for (int i=0;i<cardAmount;i++)
            {

                if (ActualHand[cardsPositions[i]].getValue() != 0 && ActualHand[cardsPositions[i]].getSuit() != 0)
                {
                    if(ActualHand[cardsPositions[i]].getValue() > 0 && ActualHand[cardsPositions[i]].getSuit() > 0)
                    {
                        
                        board[i]=ActualHand[cardsPositions[i]]; //adds cards played from actual hand
                         //setting cards played values to 0
                        ActualHand[cardsPositions[i]] = card(0,0);
                        
                    
                    }
                }
            }
    }

    return 1;
}


void tracker::viewBoardPile(int amountCardsPlayed)
{   
    cout << endl << "Last card(s) played: ";


    for (int i=0;i<amountCardsPlayed;i++)
    {


            board[i].view();
            cout << " ;  ";
        

    }
    cout << endl << endl;
}


card *tracker::getboard()
{
    card *boardpointer = board;
    return boardpointer;
}


bool tracker::HandvsBoard(card *ActualHand, int cardAmount, card *Boardpointer)
{
    //first check for ascending or multiple
    //input type check not being used anywhere

    int InputType;
    if(Boardpointer[0].getValue() == Boardpointer[1].getValue())
    {	//checks for duplicates
		InputType = 1;
        //cout << "hvb1\n"; //testing
	}
    else if(Boardpointer[0].getValue()+1 == Boardpointer[1].getValue())
    { 	//checks for ascending
		InputType = 2;
        //cout << "hvb2\n"; //testing
	}
    else
    {   //checks single card only
        InputType = 3;
        //cout << "hvb3\n"; //testing
    }

    card *newPoint = Boardpointer;



    for(int a = 0 ; a < 13 ; a++) //checks if there is a higher single card in hand that is greater than last highest card on board
    {

        if(ActualHand[a].getValue() == newPoint[cardAmount -1].getValue()) //checks hand to see if any card is higher than last highest card in the board
        {
            if(ActualHand[a].getSuit() > newPoint[cardAmount -1].getSuit()) //checks to see if suit is greater
            return true;
        }
        else if (ActualHand[a].getValue() > newPoint[cardAmount -1].getValue()) //checks to see if value is greater
        {
            return true;
        }
        
    }

    return false;
}


//deconstructor
tracker::~tracker(){};


