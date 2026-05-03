#include "core/game.h"


int main(int, char**) {
    Game& game = Game::getInstance();
    game.init("Ghost Escape", 1920, 1280);
    game.run();
    return 0;
}