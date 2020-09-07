#pragma once
#include <list>
#include <string>
using std::string;

class Player
{
private:
    // int _id;
    string _name;
    char _color;
    bool _active;
    std::list<int> _games;
public:
    Player();
    Player(string name, char color, bool active);
    Player(string name, string str_color, bool active);
    ~Player();
    // void JoinGame(Game& game);
    string GetName() const { return _name; }
    char GetColor() const { return _color; }
    bool GetStatus() const { return _active; }
    std::list<int> GetGames() const { return _games; }
    void SetName(string name) { _name = name; }
    void SetColor(string str_color);
    void SetStatus(bool status) { _active = status; }
    void ChangeStatus();
};

class Game
{
private:
    int _id;
    string _name;
    int _players_counter = 1;
    std::list<Player> _players;
public:
    Game();
    Game(int id, string name, int players_counter, std::list<Player> players);
    ~Game();
    int GetPlayersCounter() const { return _players_counter; }
    void IncreasePlayersCounter() { _players_counter++; }
    int GetId() const { return _id; }
    string GetName() const { return _name; }
    std::list<Player> GetPlayers() const { return _players; }
    void SetId(int id) { _id = id; }
    void SetName(string name) { _name = name; }
    void SetPlayersCounter(int players_counter) { _players_counter = players_counter; }
    void SetPlayers(std::list<Player> players) { _players = players; }
    bool AddPlayer(Player player);
    Player GetPlaymate(string const player_name) const;
};
