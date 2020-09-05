#include <iostream>
#include "Models.h"

Player::Player(): _active(false)
{
}

Player::Player(string name, char color, bool active): _name(name), _color(color), _active(active)
{
}

Player::Player(string name, string str_color, bool active): _name(name), _active(active)
{
    if (str_color == "w") _color = 'w';
    else if (str_color == "b") _color = 'b';
}

Player::~Player()
{
}

// void Player::JoinGame(Game& game)
// {
//     int players_counter(game.GetPlayersCounter());

//     if (players_counter < 2)
//     {
//         _games.push_back(game.GetId());
//         game.IncreasePlayersCounter();
//     }
// }

void Player::SetColor(string str_color)
{
    if (str_color == "w") _color = 'w';
    else if (str_color == "b") _color = 'b';
}

void Player::ChangeStatus()
{
    if (_active) _active = false;
    else _active = true;
}


Game::Game()
{
}

Game::Game(int id, string name, int players_counter, std::list<Player> players):
    _id(id),
    _name(name),
    _players_counter(players_counter),
    _players(players)
{
}

Game::~Game()
{
}

bool Game::AddPlayer(Player player)
{
    if (_players_counter < 2)
    {
        _players.push_back(player);
        IncreasePlayersCounter();
        return true;
    }
    return false;
}

Player Game::GetPlaymate(string const player_name) const
{
    for(auto& player : _players)
    {
        if(player.GetName() != player_name) return player;
    }
}
