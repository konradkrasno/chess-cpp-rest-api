#include "subsidiary.h"
#include "ChessMan.h"

ChessMan::ChessMan(ChessManType const type, char const color, string position) : _type(type), _color(color), _position(position)
{
	switch (_type)
	{
	case ChessManType::None:
		_symbol = "none";
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

ChessMan::ChessMan(string const symbol, string const position, bool const first_move) : _symbol(symbol), _position(position), _firstMove(first_move)
{
	if (symbol == "none")
	{
		_type = ChessManType::None;
		_color = 0;
	}
	else if (symbol == "♖") 
	{
		_type = ChessManType::Rook;
		_color = 'b';
	}
	else if (symbol == "♜") 
	{
		_type = ChessManType::Rook;
		_color = 'w';
	}
	else if (symbol == "♞") 
	{
		_type = ChessManType::Knight;
		_color = 'w';
	}
	else if (symbol == "♘") 
	{
		_type = ChessManType::Knight;
		_color = 'b';
	}
	else if (symbol == "♝") 
	{
		_type = ChessManType::Bishop;
		_color = 'w';
	}
	else if (symbol == "♗") 
	{
		_type = ChessManType::Bishop;
		_color = 'b';
	}
	else if (symbol == "♛") 
	{
		_type = ChessManType::Queen;
		_color = 'w';
	}
	else if (symbol == "♕") 
	{
		_type = ChessManType::Queen;
		_color = 'b';
	}
	else if (symbol == "♚") 
	{
		_type = ChessManType::King;
		_color = 'w';
	}
	else if (symbol == "♔") 
	{
		_type = ChessManType::King;
		_color = 'b';
	}
	else if (symbol == "♟") 
	{
		_type = ChessManType::Pawn;
		_color = 'w';
		if (_color == 'w') _moveDirection = "increase";
		else _moveDirection = "decrease";
	}
	else if (symbol == "♙") 
	{
		_type = ChessManType::Pawn;
		_color = 'b';
		if (_color == 'w') _moveDirection = "increase";
		else _moveDirection = "decrease";
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
