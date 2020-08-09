#pragma once
#include <list>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "UpdateAttributes.h"


class PawnMoves : 
    public UpdateAttributes
{
public:
	PawnMoves();
	~PawnMoves();
    bool LookForPawnPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        string possiblePosition,
        string actualPosition
    );
    void LookForPawnPossibleCaptureAndUpdateReactionBoard(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string possiblePosition,
        string actualPosition,
        ChessMan movedChessMan
    );
    void CheckPawnCaptures(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank,
        string const file_range
    );
    void PawnPossibleMoves(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string actualPosition,
        ChessMan const movedChessMan,
        char const file,
        char const rank
    );
};
