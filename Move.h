#pragma once
#include <list>
#include <iostream>
using std::string;

#include "BoardAttributes.h"
#include "PawnMoves.h"
#include "KnightMoves.h"
#include "QueenMoves.h"
#include "KingMoves.h"

class Move :
    public PawnMoves,
    public KnightMoves,
    public QueenMoves,
    public KingMoves
{
public:
    Move();
    ~Move();
    BoardAttributes boardAttributes;
    void ChessManPossibleMoves(string const actualPosition);
};
