#include "Engine/pch.h"
#include "Core.h"
#include "Game.h"

int main(int argc, char** argv) {
    LaunchParameters params(argc, argv);
    Game game(params);
    game.start();
}