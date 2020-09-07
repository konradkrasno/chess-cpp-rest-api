#include "ClientHandler.h"

int main(int argc, char* argv[])
{
    ClientHandler client_handler;

    string port(argv[1]);
    client_handler.client_gameplay.board.provider.SetServerUrl(port+"/chess");

    Player pl;
    pl = client_handler.client_gameplay.board.provider.GetPlayerFromServer("test_1");

    string player_name;
    if (pl.GetName() == "test_1")
    {
        player_name = "test_2";
        pl.SetName("test_2");
        pl.SetColor("b");
        pl.SetStatus(false);
    }
    else
    {
        player_name = "test_1";
        pl.SetName("test_1");
        pl.SetColor("w");
        pl.SetStatus(true);
    }

    client_handler.client_player = pl;
    string color;
    color += pl.GetColor();
    client_handler.client_gameplay.board.provider.PutPlayerToServer(pl);

    client_handler.game_name = "test_game";
    client_handler.client_gameplay.board.provider.PutGameToServer(client_handler.game_name, pl);

    std::cout << "Wait for second player..." << std::endl;
    while(client_handler.client_game.GetPlayersCounter() < 2)
    {
        client_handler.client_game = client_handler.client_gameplay.board.provider.GetGameFromServer(client_handler.game_name);
    }

    client_handler.client_playmate = client_handler.client_game.GetPlaymate(player_name);
    string playmate_name = client_handler.client_playmate.GetName();
    std::cout << "Your Playmate is: " << playmate_name << std::endl;
    
    client_handler.StartGame();

    return 0;
}
