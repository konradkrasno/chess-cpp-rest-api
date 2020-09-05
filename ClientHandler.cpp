#include <iostream>
#include <list>
using std::cout;
using std::endl;

#include "ClientHandler.h"

ClientHandler::ClientHandler()
{
}

ClientHandler::~ClientHandler()
{
}

string ClientHandler::MakeLowercase(string input)
{
	string lowercase;
	for (char const& c : input)
	{
		lowercase += tolower(c);
	}
	return lowercase;
}

bool ClientHandler::CheckInput(string input)
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
    else if (input == "players")
	{
		PrintPlayers();
		return false;
	}
	else if (input == "games")
	{
		PrintGames();
		return false;
	}
	else if (input == "newplayer")
	{
		CreateNewPlayer();
		return true;
	}
	else if (input == "newgame")
	{
		CreateNewGame();
		return true;
	}

    // TODO finish this feature
    // if (FindPlayer()) return true;
	cout << "Wrong command, try again: ";
	return false;
}

bool ClientHandler::GetInputFromUser()
{
	string input;
	cin >> input;
	input = MakeLowercase(input);
	bool valid(CheckInput(input));
	if (valid)
	{
		// validPosition = input;
		return true;
	};
	return false;
}

void ClientHandler::Help() const
{
	cout << endl;
	cout << "To quit the game print 'exit'" << endl;
	cout << "To print list of players print 'players'" << endl;
	cout << "To print list of games print 'games'" << endl;
	cout << "To quit the game print 'exit'" << endl;
	cout << endl;
}

void ClientHandler::Exit()
{
	exit(1);
}

void ClientHandler::PrintPlayers()
{
	std::list<Player> players_list = client_gameplay.board.provider.GetPlayersFromServer();

    cout << "Choose Player:" << endl;
    cout << "Player name: " << endl;

    for(const auto& player : players_list)
    {
        cout << player.GetName() << endl;
    }

    cout << "or print 'newplayer' to create new Player: ";
}

void ClientHandler::PrintGames()
{
	std::list<Game> games_list = client_gameplay.board.provider.GetGamesFromServer();

    cout << "Choose Game:" << endl;
    cout << "Game name: " << endl;

    for(const auto& game : games_list)
    {
        cout << game.GetName() << endl;
    }

    cout << "or print 'newgame' to create new Game: ";
}

bool ClientHandler::ChoosePlayer()
{
    cout << "This is Chess Game" << endl;
	cout << "Print 'help' for more information" << endl;
	cout << endl;

    PrintPlayers();

    while (true) {
        if (GetInputFromUser()) break;
    }

	return true;
}

// TODO finish this feature
// string ClientHandler::FindPlayer(string input)
// {
//     for(const auto& player : players)
//     {
//         if (player == input)
//         {
//             return player
//         }
//     }
// }

bool ClientHandler::CreateNewPlayer()
{
	cout << "Give me Player name: ";
	string name;
	cin >> name;

	client_player.SetName(name);

	while (true)
	{
		cout << "What color would you like to play? " << endl;
		cout << "Print 1 for White" << endl;
		cout << "Print 2 for Black" << endl;
		string color;
		cin >> color;

		if (color == "1")
		{
			client_player.SetColor("w");
			client_player.SetStatus(true);
			client_gameplay.board.provider.PutPlayerToServer(client_player);
			break;
		} 
		else if (color == "2")
		{
			client_player.SetColor("b");
			client_player.SetStatus(false);
			client_gameplay.board.provider.PutPlayerToServer(client_player);
			break;
		}
	}

    return true;
}

bool ClientHandler::ChooseGame()
{
    cout << "Choose Game or create new:" << endl;
	cout << "Print 'help' for more information" << endl;
	cout << endl;

    PrintGames();

    while (true) {
        if (GetInputFromUser()) break;
    }

	return true;
}

bool ClientHandler::CreateNewGame()
{
	// cout << "Give me Game name: ";
	// string name;
	// cin >> name;

	// TODO handle with game id and increasing players counter
	std::list<Game> games = client_gameplay.board.provider.GetGamesFromServer();

	// for(auto& game : games)
	// {
	// 	if(game.GetId() == 1)
	// 	{
	// 		client_game.AddPlayer(client_player);
	// 	}
	// 	else
	// 	{
	// 		int id = 1;
	// 		string name("game");
	// 		client_game.SetId(id);
	// 		client_game.SetName(name);
	// 		client_game.AddPlayer(client_player);
	// 		client_gameplay.board.provider.PutGameToServer(id, name, client_game.GetPlayersCounter(), client_game.GetPlayers());		
	// 	}
	// }
    return true;
}

bool ClientHandler::StartGame()
{
	client_gameplay.StartGame(client_player, client_playmate);
}
