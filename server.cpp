#include <iostream>
#include "Service.h"
using namespace std;

int main(int argc, char* argv[])
{
    string IPAddress(argv[1]);
    std::cout << "IPAddress: " << IPAddress << std::endl;

    Service serv(IPAddress,"80");
    serv.setEndpoint("/chess");
    serv.accept().wait();
    std::cout << "Server running..." << std::endl;
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
