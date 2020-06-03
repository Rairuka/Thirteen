#compiles all files into one executable


thirteen: card.o deckOfCards.o tracker.o main.o window.o player.o 
	g++	player.o card.o deckOfCards.o tracker.o main.o window.o -o thirteen

card.o:	card.cpp card.h 
	g++ -c card.cpp card.h 

deckOfCards.o: deckOfCards.cpp 
	g++ -c deckOfCards.cpp 

tracker.o: tracker.cpp 
	g++ -c tracker.cpp 

main.o: main.cpp
	g++ -c main.cpp

window.o: window.cpp
	g++ -c window.cpp

player.o: player.cpp
	g++	-c player.cpp


clean:
	rm *.o thirteen *.gch
