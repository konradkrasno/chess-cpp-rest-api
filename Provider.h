// #include <boost/lexical_cast.hpp>
// #include <boost/fusion/adapted.hpp>

// #include "restc-cpp/restc-cpp.h"
// #include "restc-cpp/SerializeJson.h"
// #include "restc-cpp/RequestBuilder.h"
#include "restincurl/restincurl.h"
#include "nlohmann/json.hpp"

#include "BoardAttributes.h"
#include "Models.h"

using namespace std;
using namespace nlohmann;

class Provider
{
private:
    string server_url;
	BoardAttributes tmp_boardAttr;
    std::list<Player> tmp_players_list;
    std::list<Game> tmp_games_list;

public:
    Provider();
    ~Provider();
	std::map <string, ChessMan> GetBoardsFromServer();
    std::list<Player> GetPlayersFromServer();
    Player GetPlayerFromServer(string const player_name);
    std::list<Game> GetGamesFromServer();
    Game GetGameFromServer(string const game_name);
    void SetServerUrl(string port) { server_url = port; }
    void PutPositionToServer(int _id, string _position, string _symbol);
    void PutPlayerToServer(Player player);
    void PutGameToServer(string _name, Player player);
};
