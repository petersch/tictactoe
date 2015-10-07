#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class GameWidget;

/**
 * @brief The Player class is an abstract base class for classes implementing player strategies.
 */
class Player {
public:
    void setId(int id);
    int getId();
    /**
     * @brief Abstract method implemeting player's strategy.
     * @param game  GameWidget running current game
     * @return      pair of x and y coordinates representing move,
     *              which results in the highest score
     */
    virtual std::pair<int, int> getNextMove(GameWidget *game) = 0;
private:
    int id_;
};

#endif // PLAYER_H
