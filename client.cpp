#include "Gameplay.h"
#include "ClientHandler.h"

int main() {
    ClientHandler client_handler;

    client_handler.gameplay.board.provider.PutTestToServer(1);
    client_handler.gameplay.board.provider.PutTestToServer(0);

    // while (true) {
    //     // client_handler.ChoosePlayer();

    //     Gameplay gameplay;
    //     gameplay.StartGame();
    // }
}
