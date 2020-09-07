#pragma once
#include <iostream>
#include <map>
using std::string;

#include "subsidiary.h"
#include "ChessMan.h"
#include "Move.h"
#include "Board.h"

static const std::map<char, string> players
{
	{ 'w', "White" },
	{ 'b', "Black" }
};

static const bool invertTable(true);

class Gameplay
{
public:
	Gameplay();
	~Gameplay();
	Board board;
	char SwitchPlayer(char const playerColor);
	string MakeLowercase(string input);
	bool ValidatePositionInput(string input);
	bool GetInputFromUser(char const playerColor, string const message, string& validPosition, bool& castling);
	bool CheckInput(string input, char const playerColor, bool& castling);
	void Exit();
	void Help() const;
	void PleaseDrawBoard(char const playerColor) const;
	bool Castling(char const playerColor, string test_input = "default");
	bool SwitchPlayerAndLookForCheckMateOrCheck(char playerColor, Player& player, Player& playmate);
	void StartGame(Player& player, Player& playmate);
	void UpdateDataFromServer();
};
