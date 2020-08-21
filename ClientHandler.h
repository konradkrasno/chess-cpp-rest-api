#pragma once
#include <iostream>
using std::string;

#include "Gameplay.h"

class ClientHandler
{
public:
    ClientHandler();
    ~ClientHandler();
    Gameplay gameplay;
    std::list<Player> players;
    string MakeLowercase(string input);
    bool CheckInput(string input);
    bool GetInputFromUser();
    void Help() const;
    void Exit();
    void PrintPlayers();
    bool ChoosePlayer();
    // bool FindPlayer(string input);
    bool CreateNewPlayer();
    bool ChooseGame();
    bool CreateNewGame();
    bool StartGame();
};
