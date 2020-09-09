# chess-cpp-rest-api

This is a console application written in C++ with which you can play chess online in localhost. It uses REST API.

## Installation

You can use docker to start up the game.

Clone github repository:
```bash
git clone https://github.com/konradkrasno/chess-cpp-rest-api.git
cd chess-cpp-rest-api
```
Initialize server:
```bash
docker-compose -f docker-compose-server.yml up
```

To initialize client open new command line and create docker container.
First you have to build an image:
```bash
docker build --tag chess-cpp-rest-api:1.0 .
```
Then you can run the container:
```bash
docker container run --name chess-client -v ${pwd}:/cpp-rest-api -p 8080:80 -it chess-cpp-rest-api:1.0 bash
```
Finally print inside container:
```bash
make -f client.mak && ./client `cat /etc/hosts | grep 172 | cut -c 1-6`
```
