#include "QueenMoves.h"

QueenMoves::QueenMoves() : RookMoves(), BishopMoves()
{
}

QueenMoves::~QueenMoves()
{
}

void QueenMoves::QueenPossibleMoves(
	std::map<string, ChessMan> const boardState,
	std::map<string, std::list<string>>& movesBoard,
	std::map<string, std::list<ChessMan>>& reactionBoard,
	string const actualPosition,
	ChessMan const movedChessMan,
	char const file, 
	char const rank
)
{
	RookPossibleMoves(
		boardState,
		movesBoard,
		reactionBoard,
		actualPosition,
		movedChessMan,
		file,
		rank
	);
	BishopPossibleMoves(
		boardState,
		movesBoard,
		reactionBoard,
		actualPosition,
		movedChessMan,
		file,
		rank
	);
}
