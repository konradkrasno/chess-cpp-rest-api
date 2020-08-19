#include <iostream>
using std::cout;
using std::endl;

#include "Provider.h"

namespace url_options {
    string server_url = "http://172.17.0.1/games";
}

namespace tmp_data {
	BoardAttributes tmp_boardAttr;
}

void GetData(Context& ctx) {
     try {
        std::list<Position> positions_list;
        SerializeFromJson(positions_list, ctx.Get(url_options::server_url));

        for(const auto& pos : positions_list)
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

Provider::Provider()
{
}

Provider::~Provider()
{
}

void Provider::PutDataToServer(int _id, string pos, string sym)
{
	Position data_object;
    data_object.game_id = _id;
    data_object.position = pos;
    data_object.symbol = sym;

    auto rest_client_put = RestClient::Create();

    rest_client_put->ProcessWithPromise([&](Context& ctx) {
        auto reply = RequestBuilder(ctx)
                .Put(url_options::server_url)
                .Data(data_object)
                .Execute();
    });

    rest_client_put->CloseWhenReady(true);
}

std::map <string, ChessMan> Provider::GetDataFromServer()
{
	auto rest_client_get = RestClient::Create();
    rest_client_get->Process(GetData);
    rest_client_get->CloseWhenReady(true);
    return tmp_data::tmp_boardAttr.boardState;
}
