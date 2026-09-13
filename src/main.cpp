#include "core/game.h"


int main(int, char**) {
    Game& game = Game::getInstance();
    game.init("Ghost Escape", 1080, 720);
    game.run();
    return 0;
}