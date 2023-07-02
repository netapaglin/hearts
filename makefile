VECTOR_PATH = ../homeWork/vector
TARGET= hearts.out
CC= gcc
CFLAGS= -ansi -g -pedantic -I $(VECTOR_PATH)
OBJS= main.o game.o round.o player.o ui.o  deck.o  vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c round.h player.h game.h ui.h 
	$(CC) $(CFLAGS) -c main.c

deck.o: deck.h deck.c cards.h round.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c deck.c
	
ui.o: ui.c ui.h round.h player.h game.h cards.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c ui.c
	
player.o: player.c player.h game.h ui.h cards.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c player.c
	
round.o: round.c round.h player.h game.h deck.h ui.h cards.h 
	$(CC) $(CFLAGS) -c round.c
	
game.o: game.c round.h player.h game.h ui.h main.h cards.h 
	$(CC) $(CFLAGS) -c game.c
	
vector.o: $(VECTOR_PATH)/vector.c $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c $(VECTOR_PATH)/vector.c
	
clean:
	rm -f $(TARGET) $(OBJS)
	
	
deck.out : deck.o deckTest.o
	$(CC) -o deck.out deck.o deckTest.o vector.o
	
deckTest.o: deck.h deckTest.c  cards.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c deckTest.c
	
player.out : player.o playerTest.o
	$(CC) -o player.out player.o playerTest.o vector.o ui.o
	
playerTest.o: player.h playerTest.c ui.h round.h cards.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c playerTest.c
	
round.out : round.o roundTest.o
	$(CC) -o round.out round.o roundTest.o ui.o player.o deck.o vector.o
	
roundTest.o: round.h roundTest.c ui.h player.h cards.h deck.h $(VECTOR_PATH)/vector.h 
	$(CC) $(CFLAGS) -c roundTest.c



