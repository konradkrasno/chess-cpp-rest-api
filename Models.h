#pragma once
#include <list>
#include <string>
using std::string;

class Game
{
private:
    int _id;
    string name;
    int players_counter = 1;
public:
    Game();
    ~Game();
    int GetPlayersCounter() const { return players_counter; }
    void IncreasePlayersCounter() { players_counter++; }
    int GetGameId() const { return _id; }
};

class Player
{
private:
    // int _id;
    string _name;
    string _color;
    bool _status;
    std::list<int> _games;
public:
    Player(string name, string color, bool status);
    ~Player();
    void JoinGame(Game& game);
    string GetName() const { return _name; }
    string GetColor() const { return _color; }
    bool GetStatus() const { return _status; }
    std::list<int> GetGamesList() const { return _games; }
};
