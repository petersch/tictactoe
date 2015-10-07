#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFuture>
#include <QMutex>
#include <QWaitCondition>

#include "board.h"

class Player;

/**
 * @brief The GameWidget class is a QWidget running the game.
 */
class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void startNewGame(std::unique_ptr<Player>& player1, std::unique_ptr<Player>& player2);
    const Board& getBoard() const;
    const std::pair<int, int>& getMouseInput();

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

private:
    Board board_;
    std::unique_ptr<Player> players_[2];
    bool gameStarted_, gameAborted_;

    QMutex gameThreadMutex_;
    QWaitCondition mouseInputCondition_;
    QFuture<void> gameThreadFuture_;
    std::pair<int, int> mouseInput_;

    QRect painterViewportRect_, painterWindowRect_;
    QPixmap xPixmap_, oPixmap_;

    void runGame();
    void abortGame();
};

#endif // GAMEWIDGET_H
