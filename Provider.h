#include <boost/lexical_cast.hpp>
#include <boost/fusion/adapted.hpp>

#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/SerializeJson.h"
#include "restc-cpp/RequestBuilder.h"

#include "BoardAttributes.h"

using namespace std;
using namespace restc_cpp;

struct Position {
	bool first_move;
    int game_id;
    string position;
    string symbol;
};

BOOST_FUSION_ADAPT_STRUCT(
    Position,
    (bool, first_move)
    (int, game_id)
    (string, position)
    (string, symbol)
)

class Provider
{
public:
    Provider();
    ~Provider();
	std::map <string, ChessMan> GetDataFromServer();
    void PutDataToServer(int _id, string pos, string sym);
};
