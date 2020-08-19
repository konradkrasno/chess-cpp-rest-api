#include "Service.h"
#include <string>
using std::string;
void Service::initRestOpHandlers() {
	_listener.support(methods::GET,std::bind(&Service::handleGet,this,std::placeholders::_1));
	_listener.support(methods::PUT,std::bind(&Service::handlePut,this,std::placeholders::_1));
}

void Service::handleGet(http_request message) {
    // ////
    // boardOnServer.boardState.at("g7") = ChessMan(ChessManType::None, 0, "g7");
    // boardOnServer.boardState.at("h7") = ChessMan(ChessManType::None, 0, "h7");
    // boardOnServer.boardState.at("g5") = ChessMan(ChessManType::Pawn, 'b', "g5");
    // boardOnServer.boardState.at("h4") = ChessMan(ChessManType::Pawn, 'b', "h4");
    // ////

    vector<string> path = requestPath(message);
    if(path.empty()) {
        vector <json::value> boardPositions;
        json::value chessman;

        for (char const& file : fileRange)
        {
            for (char const& rank : rankRange)
            {
                string position(ConvertFileAndRankToPosition(file, rank));
                string symbol(boardOnServer.boardState.at(position).GetSymbol());
                bool first_move(boardOnServer.boardState.at(position).CheckFirstMove());

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
        message.reply(status_codes::BadRequest);
    }
}

// void Service::handleGet(http_request message) {
//     vector<string> path = requestPath(message);
//     if(path.empty()) {
//         vector <json::value> jsonNumbers;
//         for(unsigned int i = 0;i<numbers.size();i++) {
//             json::value number;
//             number["number"] = json::value::number(numbers[i]);
//             jsonNumbers.push_back(number);
//         }
//         json::value generatedNumberList;
//         generatedNumberList["numbers"] = json::value::array(jsonNumbers);
//         message.reply(status_codes::OK,generatedNumberList);
//     }
//     else {
//         if(path[0]=="avg") {
//             float avg = calculateSum()/numbers.size();
//             json::value number;
//             number["avg"] = json::value::number(avg);
//             message.reply(status_codes::OK,number);
//         }
//         else if(path[0]=="sum") {
//             float sum = calculateSum();
//             json::value number;
//             number["sum"] = json::value::number(sum);
//             message.reply(status_codes::OK,number);
//         }
//         else {
//             message.reply(status_codes::BadRequest);
//         }
//     }
// }

void Service::handlePut(http_request message) {
    message.extract_json().then([=](pplx::task<json::value> task)
    {
        try
        {
            json::value val = task.get();
            int game_id = val[U("game_id")].as_number().to_int32();
            string position = val[U("position")].as_string();
            string symbol = val[U("symbol")].as_string();
            boardOnServer.boardState.at(position) = ChessMan(symbol, position, false);
            message.reply(status_codes::OK);
        }
        catch(std::exception& e) {
            message.reply(status_codes::BadRequest);
        }
    });
}
