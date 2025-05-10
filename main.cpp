#include "Core.h"
#include "Game.h"

int main(int argc, char** argv) {
    LaunchParameters params(argc, argv);
    Game game(params);
    game.startMainLoop();
    return 0;
}