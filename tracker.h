//tracker.h

#ifndef TRACKER_H
#define TRACKER_H

#include "card.h" //card header for card type etc
#include "base.h" //abstract class parent and inheritance


class tracker : public parent
{
    private: 
        int currentPlayerTurn; //used to track player turn
        card *board = new card[13]; //making the card array for board

    public:
        ~tracker();
        tracker();
        //players will be numbered 0-3 p(1-4)
        card findLowestCard(int amountPlayers, card *shuffledDeck); //returns the lowest card
        int printWhosTurn(card temp, card *shuffledDeck, int numPlayers); //uses findLowestCard return val and finds player holding it
        void view(); //viewing board
        
        //board methods
        bool addtoboard(int cardAmount,int *cardsPositions,card *ActualHand);  //adds cards played to board and puts empty hand slot
        card *getboard(); //returns pointer to board
        void viewBoardPile(int amountCardsPlayed); //shows what cards are on the board
        bool HandvsBoard(card *ActualHand, int cardAmount, card *boardPointer); //checks to see if players hand can keep up with current board
        
};

#endif

