#pragma once
#include <list>
#include <iostream>
using std::string;

#include "RookMoves.h"
#include "BishopMoves.h"


class QueenMoves :
	public RookMoves,
    public BishopMoves
{
public:
    QueenMoves();
    ~QueenMoves();

    void QueenPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );
};
