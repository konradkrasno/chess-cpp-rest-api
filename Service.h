#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include "BasicController.h"
#include "BoardAttributes.h"
#include "Models.h"
#include <vector>
#include <list>
using std::vector;

class Service : public BasicController {
public:
    Service(const std::string& address,const std::string& port) : BasicController(address,port) {}
    ~Service() {}
    BoardAttributes boardsOnServer;
    std::list<Player> playersOnServer;
    std::list<Game> gamesOnServer;
    /////
    std::list<int> testData;
    /////
    void handleGet(http_request message);
    void handlePut(http_request message);
    void initRestOpHandlers() override;
};

#endif // SERVICE_H_INCLUDED
