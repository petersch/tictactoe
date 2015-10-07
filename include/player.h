#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class GameWidget;

class Player {
public:
    void setId(int id);
    int getId();
    virtual std::pair<int, int> getNextMove(GameWidget *game) = 0;
private:
    int id_;
};

#endif // PLAYER_H
