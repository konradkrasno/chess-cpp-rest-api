#include <iostream>
using std::cout;
using std::endl;

#include "Provider.h"

namespace url_options {
    string server_url = "http://172.17.0.1/chess";
}

namespace tmp_data {
	BoardAttributes tmp_boardAttr;
    std::list<Player> tmp_players_list;
}

void GetBoardsData(Context& ctx) {
     try {
        std::list<Position> positions;
        SerializeFromJson(positions, ctx.Get(url_options::server_url));

        for(const auto& pos : positions)
        {
            // TODO refactor!!!!
            if (pos.game_id == 1)
            {
                tmp_data::tmp_boardAttr.boardState.at(pos.position) = ChessMan(pos.symbol, pos.position, pos.first_move);
            }
        }

    } catch (const exception& ex) {
        clog << "Caught exception: " << ex.what() << endl;
    }
}

void GetPlayersData(Context& ctx) {
     try {
        tmp_data::tmp_players_list.clear();
        std::list<Player_struct> players;
        SerializeFromJson(players, ctx.Get(url_options::server_url+"/players"));

        for(const auto& player : players)
        {
            Player pl(player.name, player.color, player.status);
            tmp_data::tmp_players_list.push_back(pl);
        }

    } catch (const exception& ex) {
        clog << "Caught exception: " << ex.what() << endl;
    }
}

Provider::Provider()
{
}

Provider::~Provider()
{
}

std::map <string, ChessMan> Provider::GetBoardsFromServer()
{
	auto rest_client_get = RestClient::Create();
    rest_client_get->Process(GetBoardsData);
    rest_client_get->CloseWhenReady(true);
    return tmp_data::tmp_boardAttr.boardState;
}

std::list<Player> Provider::GetPlayersFromServer()
{
	auto rest_client_get = RestClient::Create();
    rest_client_get->Process(GetPlayersData);
    rest_client_get->CloseWhenReady(true);
    return tmp_data::tmp_players_list;
}

void Provider::PutPositionToServer(int _id, string _position, string _symbol)
{
	Position data_object;
    data_object.game_id = _id;
    data_object.position = _position;
    data_object.symbol = _symbol;

    auto rest_client_put = RestClient::Create();

    rest_client_put->ProcessWithPromise([&](Context& ctx) {
        auto reply = RequestBuilder(ctx)
                .Put(url_options::server_url)
                .Data(data_object)
                .Execute();
    });

    rest_client_put->CloseWhenReady(true);
}

void Provider::PutPlayerToServer(string _name, string _color, bool _status)
{
	Player_struct data_object;
    data_object.name = _name;
    data_object.color = _color;
    // data_object.status = _status;

    auto rest_client_put = RestClient::Create();

    rest_client_put->ProcessWithPromise([&](Context& ctx) {
        auto reply = RequestBuilder(ctx)
                .Put(url_options::server_url+"/players")
                .Data(data_object)
                .Execute();
    });

    rest_client_put->CloseWhenReady(true);
}
