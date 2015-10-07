#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "player.h"

class Board;

class MinimaxPlayer : public Player {
public:
    std::pair<int, int> getNextMove(GameWidget *game);
protected:
    int boardScore(const Board& board);
    int minimax(Board& board, int alpha, int beta, bool maxPlayer);
};

#endif // MINIMAXPLAYER_H
