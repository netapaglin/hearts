#ifndef __CARDS_H__
#define __CARDS_H__
#define SUIT(card) card/NUM_OF_RANK
#define RANK(card) card%NUM_OF_RANK

typedef enum suit
{
	CLUB,
	SPADE,
	DIAMOND, 
	HEARTS,
	NUM_OF_SUIT
} suit;

typedef enum rank
{
	TWO,
	THREE,
	FOUR, 
	FIVE,
	SIX,
	SEVEN, 
	EIGHT,
	NINE, 
	TEN,
	PRINCE,
	QUIN,
	KING,
	ACE,
	NUM_OF_RANK
} rank;


#endif /* __CARDS_H__ */
