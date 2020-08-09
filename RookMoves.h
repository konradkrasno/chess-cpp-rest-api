#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "UpdateAttributes.h"


class RookMoves : 
    public UpdateAttributes
{
public:
	RookMoves();
	~RookMoves();

    void CheckRookMovesAndUpdateReactionBoard(
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

    void RookPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );
};
