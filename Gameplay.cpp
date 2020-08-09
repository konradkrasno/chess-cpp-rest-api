#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "Gameplay.h"

static const std::map<char, string> players
{
	{ 'w', "White" },
	{ 'b', "Black" }
};

static const bool invertTable(false);


Gameplay::Gameplay()
{
}

Gameplay::~Gameplay()
{
}

char Gameplay::SwitchPlayer(char const playerColor)
{
	if (playerColor == 'w') return 'b';
	return 'w';
}

string Gameplay::MakeLowercase(string input)
{
	string lowercase;
	for (char const& c : input)
	{
		lowercase += tolower(c);
	}
	return lowercase;
}

bool Gameplay::ValidatePositionInput(string input)
{
	if (input.size() != 2) return false;

	bool validFile(false);
	bool validRank(false);
	for (char const& file : fileRange)
	{
		if (input[0] == file) validFile = true;
	}
	for (char const& rank : rankRange)
	{
		if (input[1] == rank) validRank = true;
	}
	if (validFile && validRank) return true;

	return false;
}

bool Gameplay::CheckInput(string input, char const playerColor, bool& castling)
{
	if (input == "exit")
	{
		Exit();
	}
	else if (input == "help")
	{
		Help();
		return false;
	}
	else if (input == "drawboard")
	{
		PleaseDrawBoard(playerColor);
		return false;
	}
	else if (input == "castling")
	{
		castling = Castling(playerColor);
		return false;
	}
	
	if (ValidatePositionInput(input)) return true;

	cout << "Wrong command, coorginates have to be in format e.g. f4" << endl;
	return false;
}

bool Gameplay::GetInputFromUser(char const playerColor, string const message, string& validPosition, bool& castling)
{
	cout << players.at(playerColor) << message << endl;
	cout << "Give coordinates or print help for more information about other commands: ";
	string input;
	cin >> input;
	input = MakeLowercase(input);
	bool valid(CheckInput(input, playerColor, castling));
	if (valid)
	{
		validPosition = input;
		return true;
	};
	return false;
}

void Gameplay::Exit()
{
	exit(1);
}

void Gameplay::Help() const
{
	cout << endl;
	cout << "To make move choose field with Chessman witch you want to move." << endl;
	cout << "You have to give letter and number of coordinates with this order." << endl;
	cout << endl;
	cout << "To quit the game print: exit" << endl;
	cout << endl;
	cout << "To make CASTLING print: castling" << endl;
	cout << endl;
	cout << "To DRAW BOARD again print: drawboard" << endl;
	cout << endl;
}

void Gameplay::PleaseDrawBoard(char const playerColor) const
{
	board.DrawBoard(playerColor, invertTable);
}

bool Gameplay::Castling(char const playerColor, string test_input)
{
	int number_of_castlings;
	char rookFileForCastling;
	char castlingRank;
	if (playerColor == 'w') castlingRank = '1';
	else castlingRank = '8';

	number_of_castlings = board.FindCastlings(playerColor, rookFileForCastling, castlingRank);

	if (number_of_castlings == 2)
	{
		cout << "Which rook would you like to make castling?" << endl;
		cout << "Give me coodinate letter: ";

		string input;
		if (test_input != "default") input = test_input;
		else cin >> input;
		input = MakeLowercase(input);

		if (input == "a" || input == "h")
		{
			rookFileForCastling = input[0];
			board.MakeCastling(playerColor, rookFileForCastling, castlingRank);
			return true;
		}
		
		cout << "Wrong coordinate letter." << endl;
		return false;
	}
	
	else if (number_of_castlings == 1)
	{
		board.MakeCastling(playerColor, rookFileForCastling, castlingRank);
		return true;
	}

	cout << "Castling is not allowed" << endl;
	return false;
}

bool Gameplay::SwitchPlayerAndLookForCheckMateOrCheck(char& playerColor)
{
	playerColor = SwitchPlayer(playerColor);
	board.DrawBoard(playerColor, invertTable);

	if (board.CheckMate(playerColor))
	{
		cout << "Check mate! " << players.at(SwitchPlayer(playerColor)) << ", you win!" << endl;
		return true;
	}

	if (board.Check(playerColor, board.boardAttributes.kingsPositions.at(playerColor)))
		cout << players.at(playerColor) << ", your King is checked!" << endl;


	return false;
}

void Gameplay::StartGame()
{
	cout << "This is Chess Game" << endl;
	cout << "Print help for more information" << endl;
	cout << endl;

	char playerColor('w');

	board.DrawBoard(playerColor, invertTable);

	while (true)
	{
		bool castling(false);
		bool new_position_validation(false);

		string actual_position;
		string new_position;

		while (true)
		{
			bool act_position_validation(GetInputFromUser(playerColor, ": which chessman would you like to move? ", actual_position, castling));
			if (act_position_validation || castling) break;
		}
		if (!castling)
		{
			new_position_validation = GetInputFromUser(playerColor, ": where would you like to move? ", new_position, castling);
		}

		if (new_position_validation)
		{
			if (board.MakeMove(playerColor, actual_position, new_position))
			{
				if (SwitchPlayerAndLookForCheckMateOrCheck(playerColor)) break;
			}
		}
		else if (castling)
		{
			if (SwitchPlayerAndLookForCheckMateOrCheck(playerColor)) break;
		}
	}
}
