#include <stdio.h>/* for prints*/
#include<stdlib.h>/* size_t malloc*/
#include "player.h"
#include "round.h"
#include "ui.h"
#include "deck.h"
#include "cards.h"
#define SUIT(card) card/NUM_OF_RANK
#define RANK(card) card%NUM_OF_RANK
#define MAGIC_NUM 14369852
#define NUM_OF_PLAYERS 4
#define CARDS_TO_SHIFT 3
#define BLOCK_SIZE  0
#define NUM_OF_CARDS 52
#define ERROR -1
#define START_CARD 0
#define FLAG_ON 1
#define FLAG_OFF 0
#define QUIN_SPADE 23
#define CLUB 0
#define SPADE 1
#define DIAMOND 2
#define HEARTS 3


static RoundResult CardsShift(Round * _round ,Parameters* parameters, size_t _roundCounter );
static DeckResult DealCards(Round * _round);
static int FindTwoClub(Round * _round);
static RoundResult Trick(Round * _round, Parameters *parameters  , int* _startTurn);
static RoundResult PutCardOnTable(Round * _round, Parameters * parameters , int *_startTurn);
static RoundResult PlayerLost(Round * _round , int *_startTurn ,  int * _lostTheTrick);
static RoundResult CalculateTrickScore(Round * _round , int _lostTheTrick);
static RoundResult CalculateGameScore(Round * _round );
static RoundResult ChooseCardToPass(Round * _round ,Parameters* _parameters  , int* temp);
static RoundResult 	InsertCardToNextPlayer(Round * _round , size_t _roundCounter, int* temp);

static int RulesPutCard(Vector * _vec , int _cardIndex, void* _context );
static int RulesShiftCard(Vector * _vec , int _cardIndex, void* _context );
static int StrategyPutCard(int* _validCards , int _length , void* _context );
static int StrategyShiftCard(int* _validCards , int _length , void* _context );
static int StrategyHumanCard(int* _validCards , int _length , void* _context );


static int SearchForLowestRank(int* _validCards , int _length , void* _context);
static int SearchForHighestRank(int* _validCards , int _length , void* _context);
static int SearchForQuinSpade(int* _validCards , int _length , void* _context);
static int SearchForHighestHeart(int* _validCards , int _length , void* _context);
static int SearchForLowSpade(int* _validCards , int _length , void* _context);
static int SearchForHighSpade(int* _validCards , int _length , void* _context);
static int OnlyHearts(Vector * _hand ,int _length, int _card);
static int CheckLeadingSuit(Vector * _hand , int _length , int _card,  void* _context);

struct Parameters
{
	int m_heartsFlag;
	int m_onlyHeatrs;
	size_t m_roundCounter;
	int m_shiftStage;
	int m_firstInTrick;
	int m_suit;
	int m_suitExists;
	int m_human;
};

struct Round
{
	size_t m_numOfPlayers; 
	Player ** m_players;
	Deck * m_deck;
	size_t* m_trickScore;
	size_t* m_gameScore;
	size_t* m_table;
	int m_magicNum;
};

Round* RoundCreate ( const size_t _numOfPlayers , Player ** _players, size_t* _score)
{
	Round * round;
	size_t * tableArr;
	if (_players == NULL || _score == NULL )
	{
		return NULL;
	}
	round = (Round*)malloc (sizeof(Round));
	if (round == NULL)
	{
		return NULL;
	}
	round-> m_numOfPlayers = _numOfPlayers;
	round-> m_magicNum = MAGIC_NUM;
	round-> m_players = _players; 
	round -> m_gameScore = _score;
	tableArr = (size_t*)malloc (round-> m_numOfPlayers * sizeof(size_t*));
	if (tableArr == NULL)
	{
		free(round);
		return NULL;
	}
	round-> m_table = tableArr;
	return round;
}

RoundResult RunRound(Round * _round , size_t _roundCounter )
{
	Deck * createDeck;
	Parameters * parameters;
	size_t * scoreArr;
	int startTurn , index;
	PrintRoundNumber(_roundCounter);
	if (_round == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	parameters= (Parameters*)malloc (sizeof(Parameters));
	if (parameters == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	parameters -> m_roundCounter = _roundCounter;
	parameters -> m_shiftStage = FLAG_ON;
	parameters -> m_firstInTrick = FLAG_ON;
	scoreArr = (size_t*)calloc (_round-> m_numOfPlayers , _round-> m_numOfPlayers  * sizeof(size_t*));
	if (scoreArr == NULL)
	{
		return ROUND_UNITIALIZED_ERROR ;
	}
	_round-> m_trickScore = scoreArr;
	createDeck = DeckCreate (NUM_OF_CARDS, BLOCK_SIZE);
	_round -> m_deck = createDeck;
	DealCards(_round);
	CardsShift(_round ,parameters, _roundCounter );	
	startTurn = FindTwoClub(_round);
	printf("\n\n");
	for(index= 0; index < _round-> m_numOfPlayers ; ++index)
	{	
		PrintPlayerInfo(_round -> m_players[index]);
		PrintHand( _round -> m_players[index]);
	}
	printf("\n\n");
	parameters -> m_heartsFlag = FLAG_OFF;
	for (index = 0 ; index < NUM_OF_CARDS/ NUM_OF_PLAYERS; ++index)
	{
		PrintSeperateLine();
		PrintTrickNumber( index+1);
		Trick(_round ,parameters, &startTurn);
	}
	CalculateGameScore(_round );
	free(_round-> m_trickScore);
	free(parameters);
	DeckDestroy(_round->m_deck);
	return ROUND_SUCCESS;
}

int CheckWin(Round * _round)
{
	int index;
	if(_round == NULL)
	{
		return ERROR;
	}
	for (index = 0 ; index < NUM_OF_PLAYERS; ++index)
	{
		if(_round -> m_gameScore[index] >= 100)
		{
			return 1;
		}
	}
	return 0;
}

static RoundResult CalculateGameScore( Round * _round )
{
	int index;
	if(_round == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	for (index = 0 ; index < NUM_OF_PLAYERS; ++index)
	{
		_round -> m_gameScore[index] += _round -> m_trickScore[index]; 
	}
	PrintGameScore( _round -> m_gameScore , NUM_OF_PLAYERS);
	return  ROUND_SUCCESS;
}

static RoundResult Trick(Round * _round, Parameters *parameters  , int* _startTurn)
{
	int lostTheTrick, index;
	if(_round == NULL || _startTurn == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	for(index = 0; index< _round-> m_numOfPlayers ; ++index)
	{
		SortCards(_round -> m_players[index]);
	}
	parameters-> m_firstInTrick = FLAG_ON;
	PutCardOnTable(_round ,parameters,  _startTurn);
	
	PrintTable(_round-> m_table , _round ->m_numOfPlayers);
	PlayerLost( _round , _startTurn, &lostTheTrick);
	PrintWhoLostTrick(lostTheTrick);
	*_startTurn = lostTheTrick;
	CalculateTrickScore(_round , lostTheTrick);
	return  ROUND_SUCCESS;
}

static RoundResult CalculateTrickScore(Round * _round , int _lostTheTrick)
{
	size_t score =0;
	int index;
	if(_round == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	for (index = 0 ; index < NUM_OF_PLAYERS ; ++index)
	{
		if(_round -> m_table [index] >= HEARTS * NUM_OF_CARDS / NUM_OF_PLAYERS)
		{
			++score;
		}
		if(_round -> m_table [index] == (SPADE * NUM_OF_CARDS / NUM_OF_PLAYERS)+10)
		{
			score = score + 13;
		}
	}
	_round-> m_trickScore[_lostTheTrick] += score;
	PrintTrickScore(_round-> m_trickScore ,_round -> m_numOfPlayers);
	return ROUND_SUCCESS;
}

static RoundResult PlayerLost(Round * _round , int *_startTurn ,  int * _lostTheTrick)
{
	int index,  turn, card;
	int lostCard=_round-> m_table[*_startTurn ];
	int lostCardSuit = SUIT(lostCard);
	if(_round == NULL || _startTurn == NULL || _lostTheTrick == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	*_lostTheTrick = *_startTurn ;
	turn = *_startTurn ;
	for(index = 0 ; index < NUM_OF_PLAYERS-1 ; ++index)
	{
		turn = (turn+ 1)% NUM_OF_PLAYERS;
		card = _round -> m_table [turn];
		if(card > lostCard && card < (lostCardSuit + 1) * NUM_OF_CARDS / NUM_OF_PLAYERS)
		{
			lostCard = card;
			*_lostTheTrick = turn;
		}
	}
	return ROUND_SUCCESS;
}

static RoundResult PutCardOnTable(Round * _round, Parameters * parameters , int *_startTurn)
{
	int index,  turn, chosenCard , putCardResult;
	if(_round == NULL || _startTurn == NULL)
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	turn = *_startTurn -1;
	for(index = 0 ; index < NUM_OF_PLAYERS ; ++index)
	{
		turn = (turn+ 1)% NUM_OF_PLAYERS;
		putCardResult = PutCard(_round -> m_players[turn], parameters, _round -> m_table, RulesPutCard, StrategyPutCard);
		if (putCardResult == ERROR)
		{
			return ROUND_DEPENDECIES_ERROR;
		}
    	 PrepareCard(_round -> m_players[turn] , putCardResult);  

		chosenCard = RemoveCard(_round -> m_players[turn]);
		_round-> m_table[turn] = chosenCard;
		if (parameters -> m_firstInTrick == FLAG_ON)
		{
			 parameters-> m_firstInTrick = FLAG_OFF;
			parameters-> m_suit = SUIT(putCardResult) ;
		}
	}
	return ROUND_SUCCESS;
}

static int FindTwoClub(Round * _round )
{
	size_t numOfElements = NUM_OF_CARDS/_round-> m_numOfPlayers;
	size_t index;
	int found;
	if(_round == NULL)
	{
		return ERROR;
	}
	for (index = 0 ; index < _round -> m_numOfPlayers ; ++index)
	{
		found = FindCard(_round -> m_players[index] , numOfElements , START_CARD);
		if (found == ERROR)
		{
			return ROUND_DEPENDECIES_ERROR;
		}
		if( found > -1)
		{
			return index;
		}
	}
}

static DeckResult DealCards(Round * _round)
{
	int i = 0 , j , card;
	if(_round == NULL)
	{
		return DECK_UNITIALIZED_ERROR;
	}
	printf("\n");
	while(i < NUM_OF_CARDS)
	{
		card = GetCard(_round -> m_deck);
		if (card == ERROR)
		{
			return ROUND_DEPENDECIES_ERROR;
		}
		InsertCard(_round -> m_players[i % NUM_OF_PLAYERS] , card );
		++i;
	}
	for(i = 0; i< _round-> m_numOfPlayers ; ++i)
	{
		SortCards(_round -> m_players[i]);
	}
	for(j = 0; j < _round-> m_numOfPlayers ; ++ j)
	{
		PrintPlayerInfo(_round -> m_players[j]);
		PrintHand( _round -> m_players[j]);
	}
}

static RoundResult CardsShift(Round * _round ,Parameters* _parameters, size_t _roundCounter )
{
	int i , j , tempIndex = 0 , card, countCalc = 0 , putCardResult;
	int temp[NUM_OF_PLAYERS * CARDS_TO_SHIFT];
	if (_round == NULL) 
	{
		return ROUND_UNITIALIZED_ERROR;
	}
	if (_roundCounter % NUM_OF_PLAYERS == 0)
	{
		return ROUND_SUCCESS;
	}
	ChooseCardToPass(_round , _parameters, temp);
	InsertCardToNextPlayer(_round ,  _roundCounter, temp);
	for(i = 0; i< _round-> m_numOfPlayers ; ++i)
	{
		SortCards(_round -> m_players[i]);
	}
	return ROUND_SUCCESS;
}

void RoundDestroy(Round* _round)
{
	if (_round != NULL &&  _round -> m_magicNum != 0)
	{
		free(_round-> m_table );
		free(_round-> m_trickScore);
		DeckDestroy(_round -> m_deck);
		free(_round);
		_round -> m_magicNum =0;
	}
}

static RoundResult 	InsertCardToNextPlayer(Round * _round , size_t _roundCounter, int* temp)
{
	int i , j , tempIndex , card , countCalc = 0;
	for(i = _round-> m_numOfPlayers-1 ; i >= 0 ; --i)
	{
		 for (j=2 ; j >= 0 ; --j)
		 {
		 	tempIndex = ((i ) % NUM_OF_PLAYERS) * CARDS_TO_SHIFT + j;
		 	card = temp[tempIndex];
		 	countCalc = (_roundCounter)% NUM_OF_PLAYERS;
		 	switch (countCalc) 
		 	{
       	    case 1:
            	InsertCard(_round -> m_players[(i+1) % NUM_OF_PLAYERS]  , card);
            break;
            case 2:
           		InsertCard(_round -> m_players[(i+3) % 4] , card);	
            break;
            case 3:
            	InsertCard(_round -> m_players[(i+2) % NUM_OF_PLAYERS], card );	
            break;
   			}
		}
	}

}

static RoundResult ChooseCardToPass(Round * _round ,Parameters* _parameters  , int* temp)
{
	int i , j , tempIndex = 0 , card , putCardResult;
	for(i = 0; i < _round-> m_numOfPlayers ; ++i)
	{
		 for (j=0 ; j < CARDS_TO_SHIFT ; ++j)
		 {
			 tempIndex = i * CARDS_TO_SHIFT + j;
			 putCardResult = PutCard(_round -> m_players[i], _parameters, _round -> m_table, RulesShiftCard, StrategyShiftCard);
			 if (putCardResult == ERROR)
			{
				return ROUND_DEPENDECIES_ERROR;
			}
			PrepareCard(_round -> m_players[i] , putCardResult);
	    	card = RemoveCard(_round -> m_players[i]);
		    temp[tempIndex]= card;
		 }
	} 

}

/***********************************    RULES FRUNCTIONS  **************************************/

static int RulesPutCard(Vector * _hand , int _card, void* _context )
{
	int card , vectorLength, index, x, y;
	VectorItemsNum(_hand,  &vectorLength);
	((Parameters*)_context) -> m_onlyHeatrs =FLAG_ON;
	((Parameters*)_context) -> m_suitExists =FLAG_OFF;
	/**check if only hearts **/
	x = OnlyHearts(_hand , vectorLength, _card);
	if(x == FLAG_ON)
	{
		((Parameters*)_context) -> m_onlyHeatrs = FLAG_OFF;
	}
		/**if only hearts all legit **/
	if(((Parameters*)_context) -> m_onlyHeatrs == FLAG_ON)
	{
		return 1;
	}
	/**check if there is a card from the leading suit in the hand **/
	if(((Parameters*)_context) -> m_firstInTrick == FLAG_OFF)
	{	
		y = CheckLeadingSuit(_hand , vectorLength, _card, _context);
		if(y == FLAG_ON)
		{
			((Parameters*)_context) -> m_suitExists = FLAG_ON;
		}
			/**if there are not cards from the leading suit hearts are legit **/
		if(((Parameters*)_context) -> m_suitExists == FLAG_OFF)
		{
			return 1;
		}
	}
		/**check if hearts fllag off and not only hearts- dont put hearts **/
	if (((Parameters*)_context) -> m_heartsFlag == FLAG_OFF )
	{
		if(_card >=39)
		{
			return 0;
		}
	}
		/**if there is a card from the leading suit all the other suit are not legit **/
	if (((Parameters*)_context) -> m_firstInTrick == FLAG_OFF &&
		((Parameters*)_context) -> m_suitExists == FLAG_ON)
	{
		if (((Parameters*)_context) -> m_suit != SUIT(_card) )
		{
			return 0;
		}
	}
	return 1;	
}

static int RulesShiftCard(Vector * _hand , int _card, void* _context )
{
		return 1;	
}

static int OnlyHearts(Vector * _hand ,int _length, int _card)	
{
	int card , index;
	for(index = 0 ; index < _length; ++index)
	{
		VectorGet(_hand, index , &card);
		if (card < 39)
		{
			return FLAG_ON;
		}
	}
	return FLAG_OFF;
}

static int CheckLeadingSuit(Vector * _hand , int _length , int _card,  void* _context)
{
	int card , index;
	for(index = 0 ; index < _length; ++index)
	{
		VectorGet(_hand, index , &card);
		if (SUIT(card) ==  ((Parameters*)_context) -> m_suit)
		{
			return FLAG_ON;
		}
	}
	return FLAG_OFF;
}
/***********************************    STRATEGY FRUNCTIONS  **************************************/

static int StrategyHumanCard(int* _validCards , int _length , void* _context )
{
	if (((Parameters*)_context) -> m_firstInTrick == FLAG_ON)
	{
		 ((Parameters*)_context) -> m_firstInTrick = FLAG_OFF;
		((Parameters*)_context) -> m_suit = SUIT(_length) ;
	}
	return 1;
}

static int StrategyPutCard(int* _validCards , int _length , void* _context )
{
	int putCard, heartCard , highSpade, lowSpade;
	int leadingSuit;
	if (((Parameters*)_context) -> m_firstInTrick == FLAG_ON)
	{
		 putCard= SearchForLowestRank(_validCards, _length , _context);
		return putCard;
	}
	leadingSuit = ((Parameters*)_context) -> m_suit;
	switch (leadingSuit) {
    	case HEARTS:
        	if (((Parameters*)_context) -> m_suitExists == FLAG_ON)
        	{
        		putCard= SearchForLowestRank(_validCards, _length , _context);
        	}else
        	{
        		if(SearchForQuinSpade(_validCards, _length , _context) == 1)
        		{
        			putCard = QUIN_SPADE;
        			break;
        		}
        		putCard= SearchForHighestRank(_validCards, _length , _context);
        	}
            break;
    	case CLUB:
    	case DIAMOND:
        	if (((Parameters*)_context) -> m_suitExists == FLAG_ON)
        	{
        		putCard= SearchForLowestRank(_validCards, _length , _context);
        	}else
        	{
        		if(SearchForQuinSpade(_validCards, _length , _context) == 1)
        		{
        			printf( "\nQUIN_SPADE  \n ");
        			putCard = QUIN_SPADE;
        			break;
        		}
        		heartCard = SearchForHighestHeart(_validCards, _length , _context);
        		printf( "\nheartCard %d \n ", heartCard);
        		if(heartCard != 0)
        		{
        			putCard = heartCard;
        			break;
        		}             
        		putCard= SearchForLowestRank(_validCards, _length , _context);
        	}        
            break;
       	case SPADE:
       		if (((Parameters*)_context) -> m_suitExists == FLAG_ON)
        	{
        		lowSpade = SearchForLowSpade(_validCards, _length , _context);
        		if(lowSpade != 0)
        		{
        			printf( "\nlowSpade %d  \n ", lowSpade);
        			putCard = lowSpade;
        			break;
        		}
        		highSpade = SearchForHighSpade(_validCards, _length , _context);
        		if(highSpade != 0)
        		{
        			printf( "\nhighSpade  %d\n ", highSpade);
        			putCard = highSpade;
        			break;
        		}
        		putCard= SearchForLowestRank(_validCards, _length , _context);
        		break;
        	}else
        		{
        			heartCard = SearchForHighestHeart(_validCards, _length , _context);
        			printf( "\nheartCard %d \n ", heartCard);
        			if(heartCard != 0)
        			{
        			putCard = heartCard;
        			break;
        		}             
        		putCard= SearchForHighestRank(_validCards, _length , _context);
        	}        
            break;
   		}
	if (SUIT(putCard) == HEARTS)
	{
		((Parameters*)_context) -> m_heartsFlag = FLAG_ON;
	}
	return putCard;
}

static int SearchForHighSpade(int* _validCards , int _length , void* _context)
{
	int index;
	int highestSpade = QUIN_SPADE;
	for(index = 0; index < _length ;  ++index)
	{
		if (_validCards[index]  > highestSpade)
		{
			highestSpade = _validCards[index] ;
		}
	}
	if (highestSpade > QUIN_SPADE)
	{
		return highestSpade;
	}
	return 0;
}


static int SearchForLowSpade(int* _validCards , int _length , void* _context)
{
	int index;
	int lowestSpade = QUIN_SPADE;
	for(index = 0; index < _length ;  ++index)
	{
		if (_validCards[index]  < lowestSpade)
		{
			lowestSpade = _validCards[index] ;
		}
	}
	if (lowestSpade < QUIN_SPADE)
	{
		return lowestSpade;
	}
	return 0;
}


static int SearchForLowestRank(int* _validCards , int _length , void* _context)
{
	int index;
	int lowestRank = 60;
	int lowest = 80;
	for(index = 0; index < _length ;  ++index)
	{
		if(_validCards[index] == 0)
		{
			((Parameters*)_context) -> m_firstInTrick = FLAG_OFF;
			((Parameters*)_context) -> m_suit = SUIT(0);
			return _validCards[index] ;
		}
		if (RANK(_validCards[index]) < lowestRank)
		{
			lowestRank = RANK(_validCards[index]);
			lowest =_validCards[index] ;
		}
	}
	return lowest;
}

static int SearchForHighestRank(int* _validCards , int _length , void* _context)
{
	int index;
	int highestRank = -1;
	int highest = -1;
	for(index = 0; index < _length ;  ++index)
	{
		if (RANK(_validCards[index]) > highestRank)
		{
			highestRank = RANK(_validCards[index]);
			highest =_validCards[index] ;
		}
	}
	return highest;
}

static int SearchForHighestHeart(int* _validCards , int _length , void* _context)
{
	int index;
	int highestHeart = 38;
	for(index = 0; index < _length ;  ++index)
	{
		if (_validCards[index] > highestHeart)
		{
			highestHeart =_validCards[index] ;
		}
	}
	if (highestHeart > 38)
	{
		return highestHeart;
	}
	return 0;
}

static int SearchForQuinSpade(int* _validCards , int _length , void* _context)
{
	int index;
	for(index = 0; index < _length ;  ++index)
	{
		if (_validCards[index]  == QUIN_SPADE)
		{
			return 1;
		}
	}
	return 0;
}

static int StrategyShiftCard(int* _validCards , int _length , void* _context )
{
	int index;
	int highestRank = 0;
	int highest = -1;
	for(index = 0; index < _length ;  ++index)
	{
		if(_validCards[index] == QUIN_SPADE)
		{
			return _validCards[index] ;
		}
		if (RANK(_validCards[index]) > highestRank)
		{
			highestRank = RANK(_validCards[index]);
			highest =_validCards[index] ;
		}
	}
	return highest;
}








