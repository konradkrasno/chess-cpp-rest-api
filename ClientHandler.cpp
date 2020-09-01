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
    else if (input == "print")
	{
		PrintPlayers();
		return false;
	}
	else if (input == "new")
	{
		CreateNewPlayer();
		return true;
	}

    // TODO finish this feature
    // if (FindPlayer()) return true;
	cout << "Wrong command, try again.";
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
	cout << endl;
}

void ClientHandler::Exit()
{
	exit(1);
}

void ClientHandler::PrintPlayers()
{
	std::list<Player> players_list = gameplay.board.provider.GetPlayersFromServer();

    cout << "Choose Player:" << endl;
    cout << "Player name: " << endl;

    for(const auto& player : players_list)
    {
        cout << player.GetName() << endl;
    }

    cout << "or print 'new' to create new Player: ";
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

	gameplay.board.provider.PutPlayerToServer(name, "none", false);

    return true;
}
