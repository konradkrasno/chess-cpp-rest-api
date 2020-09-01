#include "Service.h"
#include <string>
using std::string;

void Service::initRestOpHandlers() {
	_listener.support(methods::GET,std::bind(&Service::handleGet,this,std::placeholders::_1));
	_listener.support(methods::PUT,std::bind(&Service::handlePut,this,std::placeholders::_1));
}

void Service::handleGet(http_request message) {
    ///////
    // boardOnServer.boardState.at("g7") = ChessMan(ChessManType::None, 0, "g7");
    // boardOnServer.boardState.at("h7") = ChessMan(ChessManType::None, 0, "h7");
    // boardOnServer.boardState.at("g5") = ChessMan(ChessManType::Pawn, 'b', "g5");
    // boardOnServer.boardState.at("h4") = ChessMan(ChessManType::Pawn, 'b', "h4");
    // Player p1("player1", "w", false);
    // Player p2("player2", "b", true);
    // playersOnServer.push_back(p1);
    // playersOnServer.push_back(p2);
    ///////

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
                string color(player.GetColor());
                bool status(player.GetStatus());

                vector<json::value> games;
                for(const auto& game : player.GetGamesList())
                {
                    games.push_back(game);
                }

                jsonPlayer["name"] = json::value::string(name);
                jsonPlayer["color"] = json::value::string(color);
                jsonPlayer["status"] = json::value::boolean(status);
                jsonPlayer["games"] = json::value::array(games);
                jsonPlayers.push_back(jsonPlayer);
            }

            json::value playersList;
            playersList = json::value::array(jsonPlayers);
            message.reply(status_codes::OK, playersList);
            }
        /////
        else if (path[0]=="test") {
            vector <json::value> jsonTestVector;
            json::value jsonTest;

            for(const auto& t : testData)
            {
                int test = t;
                jsonTest["test"] = json::value::number(test);
                jsonTestVector.push_back(jsonTest);
            }

            json::value testList;
            testList = json::value::array(jsonTestVector);
            message.reply(status_codes::OK, testList);
            }
        else {
            message.reply(status_codes::BadRequest);
        }
        /////
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
                bool status = val[U("status")].as_bool();
                playersOnServer.push_back(Player(name, color, status));
                message.reply(status_codes::OK);
            }
            catch(std::exception& e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }
    /////
    else if(message.request_uri().to_string() == "/chess/test")
    {
        message.extract_json().then([=](pplx::task<json::value> task)
        {
            try
            {
                json::value val = task.get();
                int test = val[U("test")].as_number().to_int32();
                testData.push_back(test);
                message.reply(status_codes::OK);
            }
            catch(std::exception& e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }
    /////
}
