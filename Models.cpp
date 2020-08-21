#include "Models.h"

Game::Game()
{
}

Game::~Game()
{
}

Player::Player(string name, string color, bool status): _name(name), _color(color), _status(status)
{
}

Player::~Player()
{
}

void Player::JoinGame(Game& game)
{
    int players_ctr(game.GetPlayersCounter());

    if (players_ctr < 2)
    {
        _games.push_back(game.GetGameId());
        game.IncreasePlayersCounter();
    }
}
