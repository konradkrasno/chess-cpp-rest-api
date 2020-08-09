#pragma once
#include <iostream>
#include <list>
using std::string;

#include "subsidiary.h"

enum class ChessManType
{
    None,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Pawn,
};

class ChessMan
{
private:
    string _symbol;
    ChessManType _type;
    char _color;
    string _position;
    bool _firstMove;
    string _moveDirection;

public:
    ChessMan(ChessManType const type, char const color, string position = "none");
	~ChessMan();
    string GetSymbol() const { return _symbol; }
    ChessManType GetType() const { return _type; }
    char GetColor() const { return _color; }
    bool CheckFirstMove() const { return _firstMove; }
    void ChangeFirstMove() { _firstMove = false; }
    string CheckMoveDirection() const { return _moveDirection; }
    string GetPosition() const { return _position; }
    string ChangePosition(string const position) { return _position = position; }
    bool operator==(ChessMan const& chessMan) const;
    bool operator!=(ChessMan const& chessMan) const;
};
