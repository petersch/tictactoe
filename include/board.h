#ifndef BOARD_H
#define BOARD_H

#include <list>

/**
 * @brief The Board class holds the state of a TicTacToe game.
 */
class Board {
public:
    Board();
    void clear();
    void insert(int x, int y, int playerId);
    int get(int x, int y) const;
    bool isAvailable(int x, int y) const;
    bool isFinished() const;
    bool isDraw() const;
    int getRound() const;
    int getWinner() const;
    std::list<std::pair<int, int> > getAvailableMoves() const;
private:
    int gridData_[3][3];
    int winningPlayer_;
    int round_;
};

#endif // BOARD_H
