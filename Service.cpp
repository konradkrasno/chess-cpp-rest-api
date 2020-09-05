#include "Service.h"
#include <string>
using std::string;

void Service::initRestOpHandlers() {
	_listener.support(methods::GET,std::bind(&Service::handleGet,this,std::placeholders::_1));
	_listener.support(methods::PUT,std::bind(&Service::handlePut,this,std::placeholders::_1));
}

void Service::handleGet(http_request message) {
    vector<string> path = requestPath(message);
    if(path.empty()) {
        vector <json::value> boardPositions;
        json::value chessman;

        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                string symbol(boardsOnServer.boardState.at(position).GetSymbol());
                bool first_move(boardsOnServer.boardState.at(position).CheckFirstMove());

                chessman["game_id"] = json::value::number(1);
                chessman["position"] = json::value::string(position);
                chessman["symbol"] = json::value::string(symbol);
                chessman["first_move"] = json::value::boolean(first_move);
                boardPositions.push_back(chessman);
            }
        }
        json::value boardPositionsList;
        boardPositionsList = json::value::array(boardPositions);
        message.reply(status_codes::OK, boardPositionsList);
    }
    else {
        if (path[0]=="players") {
            vector <json::value> jsonPlayers;
            json::value jsonPlayer;

            for(const auto& player : playersOnServer)
            {
                string name(player.GetName());
                string color;
                color += player.GetColor();
                bool active(player.GetStatus());

                vector<json::value> games;
                for(const auto& game : player.GetGames())
                {
                    games.push_back(game);
                }

                jsonPlayer["name"] = json::value::string(name);
                jsonPlayer["color"] = json::value::string(color);
                jsonPlayer["active"] = json::value::boolean(active);
                jsonPlayer["games"] = json::value::array(games);
                jsonPlayers.push_back(jsonPlayer);
            }

            json::value playersList;
            playersList = json::value::array(jsonPlayers);
            message.reply(status_codes::OK, playersList);
            }
        if (path[0]=="games") {
            vector <json::value> jsonGames;
            json::value jsonGame;

            for(const auto& game : gamesOnServer)
            {
                int id(game.GetId());
                string name(game.GetName());
                int players_counter(game.GetPlayersCounter());

                vector<json::value> jsonPlayers;
                json::value jsonPlayer;
                for(const auto& player : game.GetPlayers())
                {
                    string name(player.GetName());
                    string color;
                    color += player.GetColor();
                    bool active(player.GetStatus());

                    jsonPlayer["name"] = json::value::string(name);
                    jsonPlayer["color"] = json::value::string(color);
                    jsonPlayer["active"] = json::value::boolean(active);
                    jsonPlayers.push_back(jsonPlayer);
                }

                jsonGame["id"] = json::value::number(id);
                jsonGame["name"] = json::value::string(name);
                jsonGame["players"] = json::value::array(jsonPlayers);
                jsonGame["players_counter"] = json::value::number(players_counter);
                jsonGames.push_back(jsonGame);
            }

            json::value gamesList;
            gamesList = json::value::array(jsonGames);
            message.reply(status_codes::OK, gamesList);
            }
    }
}

void Service::handlePut(http_request message) {
    std::cout << "message: " << message.to_string() << std::endl;

    if(message.request_uri().to_string() == "/chess")
    {
        message.extract_json().then([=](pplx::task<json::value> task)
        {
            try
            {
                json::value val = task.get();
                int game_id = val[U("game_id")].as_number().to_int32();
                string position = val[U("position")].as_string();
                string symbol = val[U("symbol")].as_string();
                boardsOnServer.boardState.at(position) = ChessMan(symbol, position, false);
                message.reply(status_codes::OK);
            }
            catch(std::exception& e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }

    else if(message.request_uri().to_string() == "/chess/players")
    {
        message.extract_json().then([=](pplx::task<json::value> task)
        {
            try
            {
                json::value val = task.get();
                string name = val[U("name")].as_string();
                string color = val[U("color")].as_string();
                bool active = val[U("active")].as_bool();

                for(auto& player : playersOnServer)
                {
                    if(player.GetName() == name)
                    {
                        player.SetColor(color);
                        player.SetStatus(active);
                        message.reply(status_codes::OK);
                        return;
                    }
                }
                playersOnServer.push_back(Player(name, color, active));
                message.reply(status_codes::OK);
            }
            catch(std::exception& e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }

    else if(message.request_uri().to_string() == "/chess/games")
    {
        message.extract_json().then([=](pplx::task<json::value> task)
        {
            try
            {
                json::value val = task.get();
                string name = val[U("name")].as_string();

                json::array players = val[U("players")].as_array();

                Player pl;
                for(auto& player : players)
                {
                    string player_name = player[U("name")].as_string();
                    string player_color = player[U("color")].as_string();
                    bool player_status = player[U("active")].as_bool();

                    pl.SetName(player_name);
                    pl.SetColor(player_color);
                    pl.SetStatus(player_status);
                }

                for(auto& game : gamesOnServer)
                {
                    if(game.GetName() == name)
                    {
                        if(game.AddPlayer(pl))
                        {
                            message.reply(status_codes::OK);
                            return;
                        }
                        else
                        {
                            // TODO finish statement
                            message.reply(status_codes::OK);
                            return;
                        }
                    }
                }

                std::list<Player> playerList;
                playerList.push_back(pl);

                gamesOnServer.push_back(Game(++last_id, name, 1, playerList));
                message.reply(status_codes::OK);
            }
            catch(std::exception& e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }
}
