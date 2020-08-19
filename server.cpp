#include <iostream>
#include "Service.h"
using namespace std;

int main()
{
    Service serv("172.17.0.2","80");
    serv.setEndpoint("/games");
    serv.accept().wait();
    std::cout << "Server starting..." << std::endl;
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
