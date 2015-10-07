#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player{
public:
    std::pair<int, int> getNextMove(GameWidget *game);
};

#endif // HUMANPLAYER_H
