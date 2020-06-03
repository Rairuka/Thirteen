#include <iostream> //cin and cout
#include <stdlib.h>
#include "window.h" //window header
#include "deckOfCards.h" //deck objects and type
#include "card.h" //card objects and type
#include "player.h" //player objects
#include "tracker.h" //tracker object and header
#include <climits> //for INT_MAX limits


#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* MAGENTA*/
#define YELLOW  "\033[33m"      /* Yellow */
#define CYAN   "\033[36m"      /* CYAN */
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"



using namespace std;


window::window()//window constructor
{
}


void window::start()//game introduction starter
{
    clear();
    cout << endl << endl;
    cout << GREEN << "\t\t--------------------------------------------------" << RESET << endl;
    cout << GREEN << "\t\t ***   Welcome to the card game, THIRTEEN   ***\n" << RESET;
    cout << GREEN << "\t\t--------------------------------------------------" << RESET <<endl;
    cout << "\n\t1. Play\n\t2. Help\n\t3. Quit\n\n";
    cout << "\tPlease type in the number corresponding to the option chosen: ";
    cin >> menuoptionchosen; //records the selected menu option
    
    while (cin.fail()) //when cin detects anything but an int
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
		cout << "\tPlease type in the number corresponding to the option chosen: ";
		cin >> menuoptionchosen;
	}


    switch (menuoptionchosen)//menu switch statement for chosen option
    {
        case 1:
            clear();
            play();
            break;

        case 2:
            clear();
            help();
            break;

        case 3:
            clear();       
            quit();
            break;
        
        default:
            while ((menuoptionchosen < 1) || (menuoptionchosen > 3))
            {
                cout << RED << "\tInvalid menu option\n\n" << RESET;
                cout << "\tPlease type in the number corresponding to the option chosen: ";
                cin >> menuoptionchosen; //records the selected menu option


                while (cin.fail()) //when cin detects anything but an int
                {
                    cin.clear(); // clear input buffer to restore cin to a usable state
                    cin.ignore(INT_MAX, '\n'); // ignore last input
                    cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                    cout << "\tPlease type in the number corresponding to the option chosen: ";
                    cin >> menuoptionchosen;
                }
            }
            break;
        }
    }


void window::play()//option to initialise game
{
    //initialising objects
    deckOfCards deck;
	tracker track;
    
    //start
    cout << GREEN << "\t\t--------------------------------------------------" << RESET  << endl;
    cout << GREEN << "\t\t           *** LETS SEE THE CARDS ***" << endl << RESET ;
    cout << GREEN << "\t\t--------------------------------------------------" << RESET << endl << endl;
    
	cout << YELLOW << "\t\t *** Displaying deck of cards : ***" << RESET << endl;
	deck.view();
	cout << endl << endl;
	deck.shuffle();

	cout << YELLOW <<"\t\t       *** Shuffled deck : ***" << RESET << endl;
	deck.view();
    cout << endl << endl;

    cout << YELLOW << "\t\t The deck will be shuffled again since you saw it ~" << RESET << endl << endl;

    cout << GREEN << "\t\t--------------------------------------------------" << RESET << endl;
    cout << GREEN << "\t\t           ~*** NOW LETS PLAY!!! ***~" << RESET << endl;
    cout << GREEN << "\t\t--------------------------------------------------\n\n" << RESET << endl;

    //Amount of players recorder
    int numPlayersValid=0;
    int numberOfPlayers=0;

    while(numPlayersValid != 1) //run if number of plaers chosen is invalid. Asks for amount of players again
    {
        int numberOfPlayersChosen;
        cout << "How many players? (2 up to 4)" << endl;
        cin >> numberOfPlayersChosen; //input how many players are playing

        while (cin.fail()) //when cin detects anything but an int
        {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
            cout << "How many players? (2 up to 4)" << endl;
            cin >> numberOfPlayersChosen; //input how many players are playing
            cout << endl;
        }

        cout << endl;
        if (numberOfPlayersChosen > 1 && numberOfPlayersChosen < 5) //check for valid amount of player
        {
            numPlayersValid = 1; //setting to valid amount of players
            numberOfPlayers = numberOfPlayersChosen; //setting num of players with num chosen
        }


    }


	//turn decider
    card *deckpointer = deck.gimmedeck(); //setting the deckpointer to shuffled deck address
    card temp = track.findLowestCard(numberOfPlayers, deckpointer); //finds lowest card
    temp.view(); //setting player turn
    track.printWhosTurn(temp,deckpointer, numberOfPlayers); //printing whose turn it is


    //setting up player  objects and their hands with deckpointer
	player PlayerOne;
    player PlayerTwo;
	player PlayerThree;
	player PlayerFour;
	PlayerOne.setupHand(deckpointer,0); //(shuffled deck pointer, index location for the player hand)
	PlayerTwo.setupHand(deckpointer,13);
	PlayerThree.setupHand(deckpointer,26);
	PlayerFour.setupHand(deckpointer,39);
    clear();


    for (int i=0; i<numberOfPlayers;i++)//setting player names loop
    {
        string name="?";
        switch(i)
        {
            case 0:
                cout << "Please enter Player 1's name: ";
                cin >> name;
                PlayerOne.set(name);
                clear();
                break;
            case 1:
                cout << "Please enter Player 2's name: ";
                cin >> name;
                PlayerTwo.set(name);
                clear();
                break;
            case 2:
                cout << "Please enter Player 3's name: ";
                cin >> name;
                PlayerThree.set(name);
                clear();
                break;
            case 3:
                cout << "Please enter Player 4's name: ";
                cin >> name;
                PlayerFour.set(name);
                clear();
                break;
        }


    }
    

    //***player card input while loop***
    int gameFinished=0;
    //function setting the turn count start based on the player with the lowest card
    int turnCount=track.printWhosTurn(temp,deckpointer, numberOfPlayers)-1; 
    

    while (gameFinished!=1) //while game not finished, keep playing
    {
        //these ints will be reset on each time a round ends
        int amountCardsPlayed=0;
        int *cardsPositionPlayed; //card position played array to use for input checker
        int round=3; //setting round. Round (0=continued,1=finished,3=firstTurn)





// if round = 3{call FirstInputCheck}
        while(round!=1)
        {
            bool checkValidInput = false;
            bool checkHvsB = false; //check if the player's hand can keep up with the board
            int skipCount = 0;


                                 //check handsize to set game finished and printing players name that won the game
            for (int i=0; i<numberOfPlayers; i++)
            {
                switch(i)
                {
                    case 0:
                        if (PlayerOne.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerOne.view();
                            
                        }
                        break;
                    case 1:
                        if (PlayerTwo.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerTwo.view();
                        
                        }
                        break;
                    case 2:
                        if (PlayerThree.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerThree.view();
                            
                        }
                        break;
                    case 3:
                        if (PlayerFour.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerFour.view();
                            
                        }
                        break;
                    }
                }



            switch((turnCount%numberOfPlayers)) //this condition will determine the next players turn with modulus
            {       
                case 0:
                    track.viewBoardPile(amountCardsPlayed); //displays last card played
                    cout << endl;
                    cout << CYAN << " >>> ";
                    cout << "Player 1: ";
                    PlayerOne.view(); //printing players name
                    cout << RESET;
                    cout << endl << endl << endl; 
                    PlayerOne.viewHand(); //printing players hand

                    if(round == 3)//first round scenario
                    {   
                        while(checkValidInput !=true)
                        {
                            cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                            cin >> amountCardsPlayed;

                            while (cin.fail()) //when cin detects anything but an int
                            {
                                cin.clear(); // clear input buffer to restore cin to a usable state
                                cin.ignore(INT_MAX, '\n'); // ignore last input
                                cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;
                                cout << endl;
                            }

                            while((amountCardsPlayed < 1 && amountCardsPlayed>13))
                            {
                                cout << "Invalid card amount to be played entered.\n ";
                                cout << "Enter amount of cards to be played(if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;

                                while (cin.fail()) //when cin detects anything but an int
                                {
                                    cin.clear(); // clear input buffer to restore cin to a usable state
                                    cin.ignore(INT_MAX, '\n'); // ignore last input
                                    cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                    cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                    cin >> amountCardsPlayed;
                                    cout << endl;
                                }
                            }

                            if ((amountCardsPlayed > 0) && (amountCardsPlayed < 14)) 
                            {
                                //function scanning into an array based on amount of cards played and returns the array to card position played array
                                cardsPositionPlayed = PlayerOne.PlayCard(amountCardsPlayed);

                                    while (cardsPositionPlayed[0] == 14) //prevents skip first turn of a round
                                    {
                                        cardsPositionPlayed = PlayerOne.PlayCard(amountCardsPlayed);
                                    }

                                    if(cardsPositionPlayed[0] != 14)
                                    {   
                                        checkValidInput = PlayerOne.FirstInputChecker(amountCardsPlayed, cardsPositionPlayed);
                                    }
                                    round = 0; //setting to round not fininshed
                                    if(cardsPositionPlayed[0] != 14)
                                    {
                                        track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerTwo.getHandPointer());
                                    }
                            }
                        }

                        PlayerOne.getHandsize();

                        turnCount++;
                        clear();
                    }
                    else if(round == 0)
                    {
                        while(checkValidInput != true)
                        {
                            //cout << "Enter amount of cards to be played(if repeated then your previous input was invalid):";
                            //cin >> amountCardsPlayed;
                            //function scanning into an array based on amount of cards played and returns the array to card position played array
                            
                            checkHvsB = track.HandvsBoard(PlayerOne.getHandPointer(),amountCardsPlayed,track.getboard());
                            if(checkHvsB == true)
                            {
                                cardsPositionPlayed = PlayerOne.PlayCard(amountCardsPlayed);
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    if(amountCardsPlayed == 1)
                                    {
                                        checkValidInput = PlayerOne.inputCheck(cardsPositionPlayed,track.getboard());
                                    }
                                    else if(amountCardsPlayed > 1)
                                    {
                                        checkValidInput = PlayerOne.inputCheckMulti(amountCardsPlayed,cardsPositionPlayed,track.getboard());
                                    }

                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerOne.getHandPointer());
                                }
                                else if (cardsPositionPlayed[0] == 14) //manual skip
                                {
                                    checkHvsB=false;
                                    //automatic turn skipper
                                    cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                    cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                    cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                    skipCount++;
                                    cin.ignore(); //ignores
                                    cin.get(); //gets any input
                                    round = 1;
                                } 
                            }
                            else //detects that hand cannot keep up with board at the start of a turn
                            {
                                //automatic turn skipper
                                cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                skipCount++;
                                cin.ignore(); //ignores
                                cin.get(); //gets any input
                                round = 1; //setting round to finished
                            }
                        }
                        cout << endl << endl;
                        turnCount++;

                        if (skipCount == numberOfPlayers) //checks if all other players have skipped
                        {
                        round = 1;
                        }
                        clear();
                    }

                    break;


                case 1:
                    track.viewBoardPile(amountCardsPlayed); //displays last card played
                    cout << endl;
                    cout << GREEN << " >>> ";
                    cout << "Player 2: ";
                    PlayerTwo.view(); //printing players name
                    cout << RESET;
                    cout << endl << endl << endl; 
                    PlayerTwo.viewHand(); //printing players hand

                    if(round == 3)//first round scenario
                    {   
                        while(checkValidInput !=true)
                        {
                            cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                            cin >> amountCardsPlayed;

                            while (cin.fail()) //when cin detects anything but an int
                            {
                                cin.clear(); // clear input buffer to restore cin to a usable state
                                cin.ignore(INT_MAX, '\n'); // ignore last input
                                cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;
                                cout << endl;
                            }

                            while((amountCardsPlayed < 1 && amountCardsPlayed>13))
                            {
                                cout << "Invalid card amount to be played entered.\n ";
                                cout << "Enter amount of cards to be played(if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;

                                while (cin.fail()) //when cin detects anything but an int
                                {
                                    cin.clear(); // clear input buffer to restore cin to a usable state
                                    cin.ignore(INT_MAX, '\n'); // ignore last input
                                    cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                    cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                    cin >> amountCardsPlayed;
                                    cout << endl;
                                }
                            }

                            if ((amountCardsPlayed > 0) && (amountCardsPlayed < 14)) 
                            {
                                //function scanning into an array based on amount of cards played and returns the array to card position played array
                                cardsPositionPlayed = PlayerTwo.PlayCard(amountCardsPlayed);

                                while (cardsPositionPlayed[0] == 14) //prevents skip first turn of a round
                                {
                                    cardsPositionPlayed = PlayerTwo.PlayCard(amountCardsPlayed);
                                }

                                if(cardsPositionPlayed[0] != 14)
                                {   
                                    checkValidInput = PlayerTwo.FirstInputChecker(amountCardsPlayed, cardsPositionPlayed);
                                }
                                round = 0; //setting to round not fininshed
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerTwo.getHandPointer());
                                }
                            }
                        }
                        PlayerTwo.getHandsize();

                        turnCount++;
                        clear();
                    }
                    else if(round == 0)
                    {
                        while(checkValidInput != true)
                        {
                            //cout << "Enter amount of cards to be played(if repeated then your previous input was invalid):";
                            //cin >> amountCardsPlayed;
                            //function scanning into an array based on amount of cards played and returns the array to card position played array
                            
                            checkHvsB = track.HandvsBoard(PlayerTwo.getHandPointer(),amountCardsPlayed,track.getboard());
                            if(checkHvsB == true)
                            {
                                cardsPositionPlayed = PlayerTwo.PlayCard(amountCardsPlayed);
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    if(amountCardsPlayed == 1)
                                    {
                                        checkValidInput = PlayerTwo.inputCheck(cardsPositionPlayed,track.getboard());
                                    }
                                    else if(amountCardsPlayed > 1)
                                    {
                                        checkValidInput = PlayerTwo.inputCheckMulti(amountCardsPlayed,cardsPositionPlayed,track.getboard());
                                    }

                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerTwo.getHandPointer());
                                }
                                else if (cardsPositionPlayed[0] == 14) //manual skip
                                {
                                    checkHvsB=false;
                                    //automatic turn skipper
                                    cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                    cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                    cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                    skipCount++;
                                    cin.ignore(); //ignores
                                    cin.get(); //gets any input
                                    round = 1;
                                } 
                            }
                            else //detects that hand cannot keep up with board at the start of a turn
                            {
                                //automatic turn skipper
                                cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                skipCount++;
                                cin.ignore(); //ignores
                                cin.get(); //gets any input
                                round = 1; //setting round to finished
                            }
                        }
                        cout << endl << endl;
                        turnCount++;

                        if (skipCount == numberOfPlayers) //checks if all other players have skipped
                        {
                        round = 1;
                        }
                        clear();
                    }
                    break;

                case 2:
                    track.viewBoardPile(amountCardsPlayed); //displays last card played
                    cout << endl;
                    cout << YELLOW << " >>> ";
                    cout << "Player 3: ";
                    PlayerThree.view(); //printing players name
                    cout << RESET;
                    cout << endl << endl << endl; 
                    PlayerThree.viewHand(); //printing players hand

                    if(round == 3)//first round scenario
                    {   
                        while(checkValidInput !=true)
                        {
                            cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                            cin >> amountCardsPlayed;

                            while (cin.fail()) //when cin detects anything but an int
                            {
                                cin.clear(); // clear input buffer to restore cin to a usable state
                                cin.ignore(INT_MAX, '\n'); // ignore last input
                                cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;
                                cout << endl;
                            }

                            while((amountCardsPlayed < 1 && amountCardsPlayed>13))
                            {
                                cout << "Invalid card amount to be played entered.\n ";
                                cout << "Enter amount of cards to be played(if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;

                                while (cin.fail()) //when cin detects anything but an int
                                {
                                    cin.clear(); // clear input buffer to restore cin to a usable state
                                    cin.ignore(INT_MAX, '\n'); // ignore last input
                                    cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                    cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                    cin >> amountCardsPlayed;
                                    cout << endl;
                                }
                            }

                            if ((amountCardsPlayed > 0) && (amountCardsPlayed < 14)) 
                            {
                                //function scanning into an array based on amount of cards played and returns the array to card position played array
                                cardsPositionPlayed = PlayerThree.PlayCard(amountCardsPlayed);

                                while (cardsPositionPlayed[0] == 14) //prevents skip first turn of a round
                                {
                                    cardsPositionPlayed = PlayerThree.PlayCard(amountCardsPlayed);
                                }

                                if(cardsPositionPlayed[0] != 14)
                                {   
                                    checkValidInput = PlayerThree.FirstInputChecker(amountCardsPlayed, cardsPositionPlayed);
                                }
                                round = 0; //setting to round not fininshed
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerThree.getHandPointer());
                                }
                            }
                        }
                        PlayerThree.getHandsize();

                        turnCount++;
                        clear();
                    }
                    else if(round == 0)
                    {
                        while(checkValidInput != true)
                        {
                            //cout << "Enter amount of cards to be played(if repeated then your previous input was invalid):";
                            //cin >> amountCardsPlayed;
                            //function scanning into an array based on amount of cards played and returns the array to card position played array
                            
                            checkHvsB = track.HandvsBoard(PlayerThree.getHandPointer(),amountCardsPlayed,track.getboard());
                            if(checkHvsB == true)
                            {
                                cardsPositionPlayed = PlayerThree.PlayCard(amountCardsPlayed);
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    if(amountCardsPlayed == 1)
                                    {
                                        checkValidInput = PlayerThree.inputCheck(cardsPositionPlayed,track.getboard());
                                    }
                                    else if(amountCardsPlayed > 1)
                                    {
                                        checkValidInput = PlayerThree.inputCheckMulti(amountCardsPlayed,cardsPositionPlayed,track.getboard());
                                    }

                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerThree.getHandPointer());
                                }
                                else if (cardsPositionPlayed[0] == 14) //manual skip
                                {
                                    checkHvsB=false;
                                    //automatic turn skipper
                                    cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                    cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                    cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                    skipCount++;
                                    cin.ignore(); //ignores
                                    cin.get(); //gets any input
                                    round = 1;
                                } 
                            }
                            else //detects that hand cannot keep up with board at the start of a turn
                            {
                                //automatic turn skipper
                                cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                skipCount++;
                                cin.ignore(); //ignores
                                cin.get(); //gets any input
                                round = 1; //setting round to finished
                            }
                        }
                        cout << endl << endl;
                        turnCount++;

                        if (skipCount == numberOfPlayers) //checks if all other players have skipped
                        {
                        round = 1;
                        }
                        clear();
                    }
                    break;
                
                case 3:
                    track.viewBoardPile(amountCardsPlayed); //displays last card played
                    cout << endl;

                    cout << RED << " >>> ";
                    cout << "Player 4: ";
                    PlayerFour.view(); //printing players name
                    cout << RESET;

                    cout << endl << endl << endl; 
                    PlayerFour.viewHand(); //printing players hand

                    if(round == 3)//first round scenario
                    {   
                        while(checkValidInput !=true)
                        {
                            cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                            cin >> amountCardsPlayed;

                            while (cin.fail()) //when cin detects anything but an int
                            {
                                cin.clear(); // clear input buffer to restore cin to a usable state
                                cin.ignore(INT_MAX, '\n'); // ignore last input
                                cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;
                                cout << endl;
                            }

                            while((amountCardsPlayed < 1 && amountCardsPlayed>13))
                            {
                                cout << "Invalid card amount to be played entered.\n ";
                                cout << "Enter amount of cards to be played(if repeated then your previous input was invalid): ";
                                cin >> amountCardsPlayed;

                                while (cin.fail()) //when cin detects anything but an int
                                {
                                    cin.clear(); // clear input buffer to restore cin to a usable state
                                    cin.ignore(INT_MAX, '\n'); // ignore last input
                                    cout << RED << "\n***You can only enter numbers.***" << RESET << endl; //error reason printed
                                    cout << "Enter amount of cards to be played(* if repeated then your previous input was invalid): ";
                                    cin >> amountCardsPlayed;
                                    cout << endl;
                                }
                            }

                            if ((amountCardsPlayed > 0) && (amountCardsPlayed < 14)) 
                            {
                                //function scanning into an array based on amount of cards played and returns the array to card position played array
                                cardsPositionPlayed = PlayerFour.PlayCard(amountCardsPlayed);

                                while (cardsPositionPlayed[0] == 14) //prevents skip first turn of a round
                                {
                                    cardsPositionPlayed = PlayerFour.PlayCard(amountCardsPlayed);
                                }

                                if(cardsPositionPlayed[0] != 14)
                                {   
                                    checkValidInput = PlayerFour.FirstInputChecker(amountCardsPlayed, cardsPositionPlayed);
                                }
                                round = 0; //setting to round not fininshed
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerFour.getHandPointer());
                                }
                            }
                        }
                        PlayerFour.getHandsize();

                        turnCount++;
                        clear();
                    }
                    else if(round == 0)
                    {
                        while(checkValidInput != true)
                        {
                            //cout << "Enter amount of cards to be played(if repeated then your previous input was invalid):";
                            //cin >> amountCardsPlayed;
                            //function scanning into an array based on amount of cards played and returns the array to card position played array
                            
                            checkHvsB = track.HandvsBoard(PlayerFour.getHandPointer(),amountCardsPlayed,track.getboard());
                            if(checkHvsB == true)
                            {
                                cardsPositionPlayed = PlayerFour.PlayCard(amountCardsPlayed);
                                if(cardsPositionPlayed[0] != 14)
                                {
                                    if(amountCardsPlayed == 1)
                                    {
                                        checkValidInput = PlayerFour.inputCheck(cardsPositionPlayed,track.getboard());
                                    }
                                    else if(amountCardsPlayed > 1)
                                    {
                                        checkValidInput = PlayerFour.inputCheckMulti(amountCardsPlayed,cardsPositionPlayed,track.getboard());
                                    }

                                    track.addtoboard(amountCardsPlayed,cardsPositionPlayed,PlayerFour.getHandPointer());
                                }
                                else if (cardsPositionPlayed[0] == 14) //manual skip
                                {
                                    checkHvsB=false;
                                    //automatic turn skipper
                                    cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                    cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                    cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                    skipCount++;
                                    cin.ignore(); //ignores
                                    cin.get(); //gets any input
                                    round = 1;
                                } 
                            }
                            else //detects that hand cannot keep up with board at the start of a turn
                            {
                                //automatic turn skipper
                                cout << "\n\t *** SKIPPING TURN !!! IT WILL BE THE NEXT PLAYER'S TURN ***"<< endl << endl;
                                cout << "\n*** Your turn is being skipped because you have no valid cards that can be played. ***\n\n";
                                cout << "\t ***          (Press the Enter Key to continue)          ***"<< endl << endl;                                checkValidInput = true;
                                skipCount++;
                                cin.ignore(); //ignores
                                cin.get(); //gets any input
                                round = 1; //setting round to finished
                            }
                        }
                        cout << endl << endl;
                        turnCount++;

                        if (skipCount == numberOfPlayers) //checks if all other players have skipped
                        {
                        round = 1;
                        }
                        clear();
                    }
                    break;


            }


        }




            cout << endl << endl;


            //check handsize to set game finished and printing players name that won the game
            for (int i=0; i<numberOfPlayers; i++)
            {
                switch(i)
                {
                    case 0:
                        if (PlayerOne.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerOne.view();
                            cout << " has won the game!\n";
                        }
                        break;
                    case 1:
                        if (PlayerTwo.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerTwo.view();
                            cout << " has won the game!\n";
                        }
                        break;
                    case 2:
                        if (PlayerThree.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerThree.view();
                            cout << " has won the game!\n";
                        }
                        break;
                    case 3:
                        if (PlayerFour.getHandsize()==0)
                        {
                            gameFinished=1;
                            PlayerFour.view();
                            cout << " has won the game!\n";
                        }
                        break;
                    }
                } 
    }





    cout << GREEN << "\n\t *** GAME HAS ENDED! ***" << RESET << endl << endl;
}



//games help for instructions
void window::help()
{
    cout << YELLOW << "\t\t\t\t***  Help  ***  \n" << RESET;
    cout << "Thirteen is a card based game.\n";
    cout << "The goal of the game is to be the first player without cards in their hand.\n";
    cout << "Each player begins with 13 cards.\n\n\n";

    cout << YELLOW << "\t\t\t  *** Strength of cards ***\n" << RESET;
    cout << "Colour: Black < Red\n";
    cout << "Suite: ♠ Spades < ♣ Clubs < ♢ Diamonds < ♡ Hearts\n";
    cout << "Number: 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < Jack < Queen < King < Ace < 2\n\n\n";

    cout << YELLOW  << "\t\t\t\t*** Playing ***\n" << RESET;
    cout << "1.Player with the 3 of Spades plays first. If no one has it, player with the next lowest cards plays.\n\n";
    cout << "2.Player starting can play a consecutive number of cards starting with their lowest card. Eg, 3,4,5,6. ";
    cout << "else they can also play just a singular card.\n\n";

    cout << "3.Players can play single, double, triple depending on the last card pile.\n\n";
    cout << "4.The card played must be higher than the last card. If consecutive, the lowest of the ";
    cout << "combination must be at least 1 higher\n\n";

    cout << "5.Players who have 4 of the same numbered card can play it anytime and win that round unless another player ";
    cout << "plays 4 higher valued same numbered cards.\n\n";

    cout << GREEN  << "Enter any key to return to menu screen..." << RESET;
    cin.ignore(); //clears cin
    cin.get(); //cin accepts any key entered
    menuoptionchosen = 0; //reseting menu choice
    clear();
    start(); //runs intro again

}

//quit function
void window::quit()
{
    cout << GREEN << "\t\t--------------------------------------------------" << RESET << endl;
    cout << GREEN << "\t\t   ***   Program has quit successfully   ***\n\n" << RESET ;
    cout << GREEN << "\t\t--------------------------------------------------" << RESET << endl;
    exit(1); //forces program to terminate
}

//clears screen with \n lines
void window::clear() 
{
    for (int i=0 ; i<50 ; i++)
    {
        cout << endl; 
    }
}

//destructor
window::~window()
{

}