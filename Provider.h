#include <boost/lexical_cast.hpp>
#include <boost/fusion/adapted.hpp>

#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/SerializeJson.h"
#include "restc-cpp/RequestBuilder.h"

#include "BoardAttributes.h"
#include "Models.h"

using namespace std;
using namespace restc_cpp;

struct Position {
	bool first_move;
    int game_id;
    string position;
    string symbol;
};
struct Player_struct {
    string name;
    string color;
    bool status;
    // list<int> games;
};

BOOST_FUSION_ADAPT_STRUCT(
    Position,
    (bool, first_move)
    (int, game_id)
    (string, position)
    (string, symbol)
)
BOOST_FUSION_ADAPT_STRUCT(
    Player_struct,
    (string, name)
    (string, color)
    (bool, status)
    // (list<int>, games)
)

class Provider
{
public:
    Provider();
    ~Provider();
	std::map <string, ChessMan> GetBoardsFromServer();
    std::list<Player> GetPlayersFromServer();
    void PutPositionToServer(int _id, string _position, string _symbol);
    void PutPlayerToServer(string _name, string _color, bool _status = false);
};
