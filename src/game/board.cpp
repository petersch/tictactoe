#include "include/board.h"

Board::Board()
{
    clear();
}

/**
 * @brief Clears the board for a new game.
 */
void Board::clear()
{
    winningPlayer_ = -1;
    round_ = 0;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            gridData_[y][x] = -1;
        }
    }
}

/**
 * @brief Stores ID of a player taking turn on the designated coordinates.
 *
 * @param x          chosen x-coordinate on the board
 * @param y          chosen y-coordinate on the board
 * @param player_id  id of the player taking turn
 */
void Board::insert(int x, int y, int playerId)
{
    if (isAvailable(x, y)) {
        gridData_[y][x] = playerId;
        ++round_;

        bool vertWin = true;
        bool horzWin = true;
        bool diagWin1 = (x==y);
        bool diagWin2 = (x==2-y);

        for (int i = 0; i < 3; ++i) {
            horzWin &= (gridData_[y][i] == playerId);
            vertWin &= (gridData_[i][x] == playerId);
            diagWin1 &= (gridData_[i][i] == playerId);
            diagWin2 &= (gridData_[i][2-i] == playerId);
        }

        if (vertWin || horzWin || diagWin1 || diagWin2) {
            winningPlayer_ = playerId;
        }
    }
}

/**
 * @brief Returns ID of the player, who owns the specified position on the board.
 * @param x  desired x-coordinate on the board
 * @param y  desired y-coordinate on the board
 * @return   player ID, or -1 if empty
 */
int Board::get(int x, int y) const
{
    return gridData_[y][x];
}

/**
 * @brief Returns true, if a specified position on the board is empty.
 * @param x  desired x-coordinate on the board
 * @param y  desired y-coordinate on the board
 * @return   true, if position is empty
 */
bool Board::isAvailable(int x, int y) const
{
    return (x >= 0 && y >= 0 && x < 3 && y < 3 && gridData_[y][x] == -1);
}

/**
 * @brief Returns true, if one of the players won, or theboard is full.
 * @return  true, if the game is finished
 */
bool Board::isFinished() const
{
    return winningPlayer_ != -1 || round_ >= 9;
}

/**
 * @brief Returns true, if the game ended in a draw.
 * @return  true, if game is drawn
 */
bool Board::isDraw() const
{
    return isFinished() && getWinner() == -1;
}

/**
 * @brief Returns number of rounds played.
 * @return  number of rounds
 */
int Board::getRound() const
{
    return round_;
}

/**
 * @brief Returns winner ID.
 * @return  winning player's ID, if game has a winner, -1 otherwise
 */
int Board::getWinner() const
{
    return winningPlayer_;
}

/**
 * @brief Returns list of all available positions on the board.
 * @return  list of pairs of x and y coordinates
 */
std::list<std::pair<int, int> > Board::getAvailableMoves() const
{
    std::list<std::pair<int, int> > movesList;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (isAvailable(x, y)) {
                movesList.push_back(std::make_pair(x, y));
            }
        }
    }
    return movesList;
}

