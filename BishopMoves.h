#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "UpdateAttributes.h"


class BishopMoves :
	public UpdateAttributes
{
public:
	BishopMoves();
	~BishopMoves();

    void CheckBishopMovesAndUpdateReactionBoard(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank,
        string const file_range,
        string const rank_range
    );

    void BishopPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );
};
