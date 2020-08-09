#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "ChessMan.h"

class BoardAttributes
{
public:
    BoardAttributes();
    ~BoardAttributes();
    std::map <char, string> kingsPositions;
    std::map <string, ChessMan> boardState;
    std::map <string, std::list<string>> movesBoard;
    std::map <string, std::list<ChessMan>> reactionBoard;
    std::map <char, string> InitialKingsPositions();
    std::map<string, ChessMan> StartingBoard();
    std::map <string, std::list<string>> EmptyMovesBoard();
    std::map <string, std::list<ChessMan>> EmptyReactionBoard();
};
