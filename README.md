# chess-cpp-rest-api

This is a console application written in C++ with which you can play chess online in localhost. It uses REST API.\
The main goal of creating this application is make way for play with chess game on two different computers.

## How it works?

First step is setting up server. Server saves information about players and games status.
Afterwards we have to set up server client. Using client we will could play with another client.

The game is played by command prompt. When you start the game you will see chess board and you will be invite to make move.
Moves are making by giving coordinate of field with chessman which we want to move and then giving the coordinates of field where we want to move this chessman.
Game logic check possible moves and when king is in check or when is checkmate:

## Design goals

- [x] Create REST API server which can handle users and games
- [x] Create client which can take and put data from server
- [x] Handle creating users
- [ ] Handle choosing existing users
- [x] Handle creating new games and assign players
- [ ] Handle choosing ols games
- [ ] Handle choosing player color
- [x] Handle starting game for two clients

## Installation with using Docker

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
Check server container IP address and run:
```bash
make -f client.mak && ./client [server_IPAddress]
```
To create another client create new container with another port.
