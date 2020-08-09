#include "subsidiary.h"
#include "ChessMan.h"

ChessMan::ChessMan(ChessManType const type, char const color, string position) : _type(type), _color(color), _position(position)
{
	switch (_type)
	{
	case ChessManType::None:
		_symbol += "none";
		_firstMove = false;
		break;
	case ChessManType::Rook:
		if (color == 'w') _symbol = "♜";
		else _symbol = "♖";
		_firstMove = true;
		break;
	case ChessManType::Knight:
		if (color == 'w') _symbol = "♞";
		else _symbol = "♘";
		_firstMove = false;
		break;
	case ChessManType::Bishop:
		if (color == 'w') _symbol = "♝";
		else _symbol = "♗";
		_firstMove = false;
		break;
	case ChessManType::Queen:
		if (color == 'w') _symbol = "♛";
		else _symbol = "♕";
		_firstMove = false;
		break;
	case ChessManType::King:
		if (color == 'w') _symbol = "♚";
		else _symbol = "♔";
		_firstMove = true;
		break;
	case ChessManType::Pawn:
		if (color == 'w') _symbol = "♟";
		else _symbol = "♙";
		_firstMove = true;
		if (_color == 'w') _moveDirection = "increase";
		else _moveDirection = "decrease";
		break;
	default:
		break;
	}
}

ChessMan::~ChessMan()
{
}

bool ChessMan::operator==(ChessMan const& chessMan) const
{
	return (_symbol == chessMan._symbol && _position == chessMan._position);
}
bool ChessMan::operator!=(ChessMan const& chessMan) const
{
	return (_symbol != chessMan._symbol || _position != chessMan._position);
}
