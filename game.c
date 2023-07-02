#include <stdio.h>/* for prints*/
#include<stdlib.h>/* size_t malloc*/
#include <time.h>
#include "player.h"
#include "game.h"
#include "round.h"
#include "ui.h"
#define BLOCK_SIZE  0
#define SIZE  13
#define HUMAN 1
#define COMPUTER 2
#define MAGIC_NUM 98251436

static GameResult PrintWinnerLoser(Game* _game);

struct Game
{
	size_t m_realPlayer; 
	size_t m_mashinPlayer; 
	size_t m_numPlayer; 
	Player ** m_players;
	size_t* m_score;
	size_t m_roundCount;
	Round * m_round;
	int m_magicNum;
};

Game* GameCreate (size_t _realPlayer , size_t _mashinPlayer)
{
	Game * game;
	Player ** players;
	Player * p;
	Round * round;
	size_t* scores;
	int index , i ;
	if (_realPlayer == 0 && _mashinPlayer == 0 || _realPlayer < 0 || _mashinPlayer < 0)
	{
		return NULL;
	}
	game = (Game*)malloc (sizeof(Game));
	if (game == NULL)
	{
		return NULL;
	}
	game-> m_realPlayer = _realPlayer;
	game-> m_mashinPlayer = _mashinPlayer;
	game-> m_numPlayer = _mashinPlayer + _realPlayer;
	game-> m_roundCount = 1;
	players = (Player**)malloc (game-> m_numPlayer  * sizeof(Player*));
	if (players == NULL)
	{
		return NULL;
	}
	game-> m_players = players;

	for (index = 0; index < game->  m_numPlayer ; ++ index)
	{
		for( i = 0 ; i < game->  m_mashinPlayer ; ++i)
		{
			p = PlayerCreate(SIZE, BLOCK_SIZE, index, COMPUTER);
			game-> m_players[index] = p;
			++index;
		}
		p = PlayerCreate(SIZE, BLOCK_SIZE, index, HUMAN);
		game-> m_players[index] = p;
	}	
	scores = (size_t*)malloc (game->m_numPlayer * sizeof(size_t));
	if (scores == NULL)
	{
		free(players);
		return NULL;
	}
	game-> m_score =  scores;
	round = RoundCreate (game-> m_numPlayer , game-> m_players, game -> m_score);
	game -> m_round = round;

	return game;
}


GameResult RunTheRound(Game* _game, CheckIfWin _isWinner)
{
	int index ;
	if (_game == NULL || _isWinner == NULL)
	{
		return GAME_INPUT_ERROR;
	}
	while (_isWinner(_game -> m_round) == 0)
	{
		RunRound(_game -> m_round , _game-> m_roundCount );
		_game-> m_roundCount += 1;
	}
	PrintWinnerLoser( _game);
	return GAME_SUCCESS;
}

static GameResult PrintWinnerLoser(Game* _game)
{
	int index ,winner, loser , winnerScore = 110 , loserScore = 0;
	if (_game == NULL)
	{
		return GAME_INPUT_ERROR;
	}
	for (index = 0 ; index < _game-> m_numPlayer  ; ++ index)
	{
		if(_game -> m_score[index] > loserScore)
		{
			loserScore = _game -> m_score[index];
			loser = index;
		}
			if(_game -> m_score[index] < winnerScore)
		{
			winnerScore = _game -> m_score[index];
			winner = index;
		}		
	}	
	PrintLostWinGame(loser, winner);
	return GAME_SUCCESS;
}


void GameDestroy(Game* _game)
{
	int index;
	if (_game != NULL &&  _game -> m_magicNum != 0)
	{
		for (index = 0 ; index < _game-> m_numPlayer  ; ++ index)
		{
			 PlayerDestroy(_game-> m_players[index]) ;
		}	
		free(_game-> m_score);
		RoundDestroy(_game -> m_round);
		free(_game);
		_game -> m_magicNum =0;
	}
}




