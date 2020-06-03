//player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> //std namespace
#include <string> //string for name
#include "deckOfCards.h" //deck header for types etc
#include "card.h" //card header for types etc
#include "base.h" //for parent abstract base class annd inheritance

using namespace std;

// MUST HAVE BEFORE MAKING PLAYERS -> THE NUMBER ON THE DECK ARRAY eg. player 1 -> 1-13
// window to have a temporary card played.

class player : public parent //inherits view and set methods
{
    private:
        //***player attributes***
        string playername; //stores player name
        card *hand; //array pointer to shuffled deck range for player 13 cards
        card *ActualHand = new card[13]; //making a card array for the actual hand
        card emptyHand; //when a card is played, this object will replace it in the hand

        //***tracking values***
        int numPlayed; //number of cards to be played in one turn
        int skipvalue; //either 1 or 0, if 1, player has not skipped, if 0 then player has skipped
        int cardtracker=13; //tracks how many cards are left (starts with 13 cards and will minus one per card played)
        int address;//address for cards in deck

    public:
        //***player attributes***
        player(); //constructor
        ~player();
        void view(); //view player name
        void set(string name); //sets player name
        

        //***player hand functions***
        player(card *deckpointer); // sets up player hand of 13 cards from the location of deckpointer
        void setupHand(card *deck, int location); //using the dealCard function from deckOfCards.h file
        int  getHandsize(); //returns size of hand. win condition will be 1 when size is 0
        void viewHand(); //view the player's hand
        card *getHandPointer(); //returns pointer to ActualHand


        //***player input functions***
        int *PlayCard(int numPlay); //inputs cards chosen. Returns an array of card positions chosen in hand 
        bool FirstInputChecker(int CardAmount, int *CardsPlayed); //used to check input on turn 1
        bool inputCheck(int *CardPlayed, card *LastCard); // used in conjunction with an input, checks if the card(s) is eligible for play, LastCard is the last card that was played
        bool inputCheckMulti(int CardAmount, int *CardsPlayed, card *LastCard); //Multiple input checker . 1=true (cards eligible) 0=false
};

#endif