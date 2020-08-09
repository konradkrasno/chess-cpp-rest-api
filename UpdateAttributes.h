#pragma once
#include <list>
#include <map>
#include <iostream>
using std::string;

#include "subsidiary.h"
#include "ChessMan.h"

class UpdateAttributes
{
public:
    UpdateAttributes();
    ~UpdateAttributes();
    bool LookForPossibleMoveAndUpdateReactionBoard(
        std::map<string, ChessMan> const boardState,
        std::map<string, std::list<string>>& movesBoard,
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const actualPosition,
        string const possiblePosition,
        ChessMan const movedChessMan
    );
    void UpdateReactionBoard(
        std::map<string, std::list<ChessMan>>& reactionBoard,
        string const possiblePosition,
        ChessMan const movedChessMan
    );
};
