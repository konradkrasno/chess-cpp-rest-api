# chess-cpp-rest-api

This is a console application written in C++ with which you can play chess online in localhost. It uses REST API.

## Installation

You can use docker to start up the game.

Clone github repository:
```bash
git clone https://github.com/konradkrasno/chess-cpp-rest-api.git
cd chess-cpp-rest-api
```

Create docker image:
```bash
docker build --tag chess-cpp-rest-api:1.0 .
```

Create docker container and initialize server:
```bash
docker container run --name chess-server -v ${pwd}:/cpp-rest-api -p 80:80 -it chess-cpp-rest-api:1.0 bash 
make -f server.mak && ./server `cat /etc/hosts | grep 172 | cut -c 1-10`
```

To initialize client open new command line and enter to chess-cpp-api folder. Then you can run the container:
```bash
docker container run --name chess-client -v ${pwd}:/cpp-rest-api -p 8080:80 -it chess-cpp-rest-api:1.0 bash
```
Check server container port and run:
```bash
make -f client.mak && ./client [server_port]
```
To create another client create new container with another port.
