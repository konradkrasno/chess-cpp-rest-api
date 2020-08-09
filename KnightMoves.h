#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "UpdateAttributes.h"


class KnightMoves :
    public UpdateAttributes
{
public:
    KnightMoves();
    ~KnightMoves();

    void CheckKnightMovesAndUpdateReactionBoard(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank,
        string const file_range,
        string const rank_range,
        int const addFileStep,
        int const addRankStep
    );

    void KnightPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );
};
