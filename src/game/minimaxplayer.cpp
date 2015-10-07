#include <ctime>
#include <climits>
#include <QDebug>
#include <QThread>

#include "include/minimaxplayer.h"
#include "include/gamewidget.h"
#include "include/board.h"

/**
 * @brief Computes best move for this player in the current game.
 *
 * Assuming the opponent is playing optimally, the
 * algorithm aims to maximize the minimum possible score.
 * If several moves yield the same final score, one of them
 * is chosen randomly with a uniform distribution.
 *
 * @param game  GameWidget running current game
 * @return      pair of x and y coordinates representing move,
 *              which results in the highest score
 */
std::pair<int, int> MinimaxPlayer::getNextMove(GameWidget *game)
{
    std::clock_t startTime = std::clock();

    std::pair<int, int> bestMove;
    int bestScore = INT_MIN;
    int alternativesCount = 1;

    if (game != nullptr) {
        const Board& board = game->getBoard();
        auto availableMoves = board.getAvailableMoves();
        for (auto currentMoveIter = availableMoves.begin(); currentMoveIter != availableMoves.end(); ++currentMoveIter) {
            Board currentBoard(board);
            currentBoard.insert(currentMoveIter->first, currentMoveIter->second, getId());

            int currentScore = minimax(currentBoard, INT_MIN, INT_MAX, false);

            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestMove = *currentMoveIter;
                alternativesCount = 1;
            }
            else if (currentScore == bestScore) {
                ++alternativesCount;
                if (std::rand() <= RAND_MAX / alternativesCount) {
                    bestMove = *currentMoveIter;
                }
            }
        }
    }

    int msecElapsed = 1000.0 * (std::clock() - startTime) / CLOCKS_PER_SEC;
    qDebug() << "minimax ended in" << msecElapsed << "ms";
    QThread::msleep(std::max(0, 500 - msecElapsed));

    return bestMove;
}

/**
 * @brief Computes this player's heuristic score for a board.
 *
 * Resulting score depends on who the winner is, as well as
 * the round in which the game ended.
 * Score for a game this player won is always higher than score
 * for a game this player lost.
 *
 * Resulting score is altered with respect to round number, in
 * a way which prevents the AI player from prematurely giving up
 * a game he can't win, or doing unnecessary moves in a game
 * he can't lose.
 *
 * @param board  Board object reference representing the game state
 * @return       this Player's score on the given board
 */
int MinimaxPlayer::boardScore(const Board& board)
{
    if (!board.isFinished() || board.isDraw()) return board.getRound();
    if (board.getWinner() == getId()) return 20 - board.getRound();
    return board.getRound() - 10;
}

/**
 * @brief Computes maximum score player can achieve, if the opponent plays optimally.
 *
 * Implements Minimax decision rule using Alpha-Beta pruning algorithm.
 *
 * @param board       Board object reference representing current game state
 * @param alpha       lower pruning thresshold
 * @param beta        upper pruning thresshold
 * @param max_player  true if this is maximizing player's turn, false otherwise
 * @return            maximum score player on turn can achieve
 */
int MinimaxPlayer::minimax(Board& board, int alpha, int beta, bool maxPlayer)
{
    if (board.isFinished()) {
        return boardScore(board);
    }

    int currentPlayerId = maxPlayer ? getId() : 1 - getId();
    std::list<std::pair<int, int> > availableMoves = board.getAvailableMoves();

    if (maxPlayer) {
        int result = INT_MIN;
        for (auto iter = availableMoves.begin(); iter != availableMoves.end(); ++iter) {
            std::pair<int, int>& nextMove = *iter;
            Board nextBoard(board);
            nextBoard.insert(nextMove.first, nextMove.second, currentPlayerId);

            result = std::max(result, minimax(nextBoard, alpha, beta, !maxPlayer));
            alpha = std::max(alpha, result);

            if (beta <= alpha) break;
        }
        return result;
    }
    else {
        int result = INT_MAX;
        for (auto iter = availableMoves.begin(); iter != availableMoves.end(); ++iter) {
            std::pair<int, int>& nextMove = *iter;
            Board nextBoard(board);
            nextBoard.insert(nextMove.first, nextMove.second, currentPlayerId);

            result = std::min(result, minimax(nextBoard, alpha, beta, !maxPlayer));
            beta = std::min(beta, result);

            if (beta <= alpha) break;
        }
        return result;
    }
}

