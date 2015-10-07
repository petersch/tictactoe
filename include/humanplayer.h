#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

/**
 * @brief The HumanPlayer class implements player using mouse input from the GameWidget.
 */
class HumanPlayer : public Player{
public:
    std::pair<int, int> getNextMove(GameWidget *game);
};

#endif // HUMANPLAYER_H
