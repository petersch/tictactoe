#include "include/humanplayer.h"
#include "include/gamewidget.h"

/**
 * @brief Returns move chosen by the player.
 * @param game  GameWidget running current game
 * @return      pair of x and y coordinates representing chosen move
 */
std::pair<int, int> HumanPlayer::getNextMove(GameWidget *game) {
    if (game)
        return game->getMouseInput();
    else
        return std::pair<int, int>();
}

