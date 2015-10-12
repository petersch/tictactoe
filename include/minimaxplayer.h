#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "player.h"

class Board;

/**
 * @brief The MinimaxPlayer class implements AI player using MinMax decision rule.
 */
class MinimaxPlayer : public Player {
public:
    std::pair<int, int> getNextMove(GameWidget *game);
protected:
    int boardScore(const Board& board);
    int minimax(const Board& board, int alpha, int beta, bool maxPlayer);
};

#endif // MINIMAXPLAYER_H
