#include <iostream>
using std::cout;
using std::endl;

#include "Provider.h"

using namespace restincurl;

Provider::Provider(string port): server_url(port)
{
}

Provider::~Provider()
{
}

std::map <string, ChessMan> Provider::GetBoardsFromServer()
{
    Client client;
    client.Build()->Get(server_url)
        .AcceptJson()
        .WithCompletion([&](const Result& result) {
            if (result.curl_code == 0 && result.http_response_code == 200) {
                try {
                    const auto j = json::parse(result.body);
                    for(const auto& r : j) {
                        // TODO refactor!!!!
                        if (r["game_id"].get<int>() == 1)
                        {
                            tmp_boardAttr.boardState.at(r["position"].get<string>()) = ChessMan(
                                r["symbol"].get<string>(),
                                r["position"].get<string>(),
                                r["first_move"].get<bool>()
                                );
                        }
                    }
                    
                } catch (const std::exception& ex) {
                    std::cout << "Caught exception: " << ex.what() << std::endl;
                    return;
                }
                
            } else {
                std::cout << "Request failed: " << result.msg << std::endl
                    << "HTTP code: " << result.http_response_code << std::endl;
            }
        })
        .Execute();
        
    client.CloseWhenFinished();
    client.WaitForFinish();

    return tmp_boardAttr.boardState;
}

std::list<Player> Provider::GetPlayersFromServer()
{
    Client client;
    client.Build()->Get(server_url+"/players")
        .AcceptJson()
        .WithCompletion([&](const Result& result) {
            if (result.curl_code == 0 && result.http_response_code == 200) {
                try {
                    tmp_players_list.clear();
                    const auto players = json::parse(result.body);

                    for(const auto& player : players)
                    {
                        Player pl(player["name"].get<string>(), player["color"].get<char>(), player["active"].get<bool>());
                        tmp_players_list.push_back(pl);
                    }
                    
                } catch (const std::exception& ex) {
                    std::cout << "Caught exception: " << ex.what() << std::endl;
                    return;
                }
                
            } else {
                std::cout << "Request failed: " << result.msg << std::endl
                    << "HTTP code: " << result.http_response_code << std::endl;
            }
        })
        .Execute();
        
    client.CloseWhenFinished();
    client.WaitForFinish();

    return tmp_players_list;
}

Player Provider::GetPlayerFromServer(string const player_name)
{
    Player pl;

    Client client;
    client.Build()->Get(server_url+"/players")
        .AcceptJson()
        .WithCompletion([&](const Result& result) {
            if (result.curl_code == 0 && result.http_response_code == 200) {
                try {
                    tmp_players_list.clear();
                    const auto players = json::parse(result.body);

                    for(const auto& player : players)
                    {
                        if(player["name"] == player_name)
                        {
                            pl.SetName(player["name"].get<string>());
                            pl.SetColor(player["color"].get<string>());
                            pl.SetStatus(player["active"].get<bool>());
                        }
                    }
                    
                } catch (const std::exception& ex) {
                    std::cout << "Caught exception: " << ex.what() << std::endl;
                    return;
                }
                
            } else {
                std::cout << "Request failed: " << result.msg << std::endl
                    << "HTTP code: " << result.http_response_code << std::endl;
            }
        })
        .Execute();
        
    client.CloseWhenFinished();
    client.WaitForFinish();

    return pl;
}

std::list<Game> Provider::GetGamesFromServer()
{
    Client client;
    client.Build()->Get(server_url+"/games")
        .AcceptJson()
        .WithCompletion([&](const Result& result) {
            if (result.curl_code == 0 && result.http_response_code == 200) {
                try {
                    tmp_games_list.clear();
                    const auto games = json::parse(result.body);

                    for(const auto& game : games)
                    {
                        std::list<Player> players;
                        for(const auto& player : game["players"])
                        {
                            Player pl(player["name"].get<string>(), player["color"].get<string>(), player["active"].get<bool>());
                            players.push_back(pl);
                        }
                        Game gm(
                            game["id"].get<int>(),
                            game["name"].get<string>(),
                            game["players_counter"].get<int>(),
                            players);
                        tmp_games_list.push_back(gm);
                    }
                    
                } catch (const std::exception& ex) {
                    std::cout << "Caught exception: " << ex.what() << std::endl;
                    return;
                }
                
            } else {
                std::cout << "Request failed: " << result.msg << std::endl
                    << "HTTP code: " << result.http_response_code << std::endl;
            }
        })
        .Execute();
        
    client.CloseWhenFinished();
    client.WaitForFinish();

    return tmp_games_list;
}

Game Provider::GetGameFromServer(string const game_name)
{
    Game gm;

    Client client;
    client.Build()->Get(server_url+"/games")
        .AcceptJson()
        .WithCompletion([&](const Result& result) {
            if (result.curl_code == 0 && result.http_response_code == 200) {
                try {
                    tmp_games_list.clear();
                    const auto games = json::parse(result.body);

                    for(const auto& game : games)
                    {
                        if(game["name"] == game_name)
                        {
                            std::list<Player> players;
                            for(const auto& player : game["players"])
                            {
                                Player pl(player["name"].get<string>(), player["color"].get<string>(), player["active"].get<bool>());
                                players.push_back(pl);
                            }
                            gm.SetId(game["id"].get<int>());
                            gm.SetName(game["name"].get<string>());
                            gm.SetPlayersCounter(game["players_counter"].get<int>());
                            gm.SetPlayers(players);
                        }
                    }                    
                } catch (const std::exception& ex) {
                    std::cout << "Caught exception: " << ex.what() << std::endl;
                    return;
                }
                
            } else {
                std::cout << "Request failed: " << result.msg << std::endl
                    << "HTTP code: " << result.http_response_code << std::endl;
            }
        })
        .Execute();
        
    client.CloseWhenFinished();
    client.WaitForFinish();

    return gm;
}

void Provider::PutPositionToServer(int _id, string _position, string _symbol)
{
    json j;
    j["game_id"] = _id;
    j["position"] = _position;
    j["symbol"] = _symbol;

    Client client;
    client.Build()->Put(server_url)
        .AcceptJson()
        .WithJson(j.dump())
        .WithCompletion([&](const Result& result) {
        })
        .Execute();

    client.CloseWhenFinished();
    client.WaitForFinish();
}

void Provider::PutPlayerToServer(Player player)
{
    string color;
    color += player.GetColor();

    json j;
    j["name"] = player.GetName();
    j["color"] = color;
    j["active"] = player.GetStatus();

    Client client;
    client.Build()->Put(server_url+"/players")
        .AcceptJson()
        .WithJson(j.dump())
        .WithCompletion([&](const Result& result) {
        })
        .Execute();

    client.CloseWhenFinished();
    client.WaitForFinish();
}

void Provider::PutGameToServer(string _name, Player player)
{
    string color;
    color += player.GetColor();

    json j;
    j["name"] = _name;

    json json_array = json::array();

    json p;
    p["name"] = player.GetName();
    p["color"] = color;
    p["active"] = player.GetStatus();
    json_array.push_back(p);

    j["players"] = json_array;

    Client client;
    client.Build()->Put(server_url+"/games")
        .AcceptJson()
        .WithJson(j.dump())
        .WithCompletion([&](const Result& result) {
        })
        .Execute();

    client.CloseWhenFinished();
    client.WaitForFinish();
}
