#include "ClientHandler.h"

int main() {
    ClientHandler client_handler;

    Player pl;

	cout << "Give me Player name: ";
	string player;
	cin >> player;

    string player_name;
    if (player == "1")
    {
        player_name = "test_1";
        pl.SetName("test_1");
        pl.SetColor("w");
        pl.SetStatus(true);
    }
    else
    {
        player_name = "test_2";
        pl.SetName("test_2");
        pl.SetColor("b");
        pl.SetStatus(false);
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
