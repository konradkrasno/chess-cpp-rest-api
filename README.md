# chess-cpp-rest-api

This is console application written in C++ which you can play chess online in localhost. This uses REST API.

# Installation

You can use docker to start up the game.

Clone github repository:
```bash
git clone https://github.com/konradkrasno/chess-cpp-rest-api.git
```

Initialize server:
```bash
docker-compose -f docker-compose-server.yml
```
Initialize client:
```bash
docker-compose -f docker-compose-client.yml
```
