#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "UpdateAttributes.h"


class KingMoves :
	public UpdateAttributes
{
public:
	KingMoves();
	~KingMoves();

    void CheckKingDiagonalMovesAndUpdateReactionBoard(
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

    void CheckKingStraightMovesAndUpdateReactionBoard(
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

    void KingPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );

};