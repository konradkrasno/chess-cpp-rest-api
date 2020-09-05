#pragma once
#include <iostream>
using std::string;

#include "Gameplay.h"

class ClientHandler
{
public:
    ClientHandler();
    ~ClientHandler();
    Player client_player;
    Player client_playmate;
    string game_name;
    Game client_game;
    Gameplay client_gameplay;
    std::list<Player> players;
    string MakeLowercase(string input);
    bool CheckInput(string input);
    bool GetInputFromUser();
    void Help() const;
    void Exit();
    void PrintPlayers();
    void PrintGames();
    bool ChoosePlayer();
    // bool FindPlayer(string input);
    bool CreateNewPlayer();
    bool ChooseGame();
    bool CreateNewGame();
    bool StartGame();
};
