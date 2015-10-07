#include <ctime>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>

#include "include/gamewidget.h"
#include "include/player.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    gameStarted_ = false;
    xPixmap_.load(":/x.png");
    oPixmap_.load(":/o.png");
}

GameWidget::~GameWidget()
{
    abortGame();
}

/**
 * @brief Starts a new game running in a separate thread.
 * @param player1  Player object representing the first player.
 * @param player2  Player object representing the second player
 */
void GameWidget::startNewGame(std::unique_ptr<Player>& player1, std::unique_ptr<Player>& player2)
{
    abortGame();
    gameStarted_ = true;
    gameAborted_ = false;
    board_.clear();
    players_[0] = std::move(player1);
    players_[0]->setId(0);
    players_[1] = std::move(player2);
    players_[1]->setId(1);
    gameThreadFuture_ = QtConcurrent::run(this, &GameWidget::runGame);
    update();
}

/**
 * @brief Method running the game cycle.
 *
 * Has to be run in a single separate thread.
 */
void GameWidget::runGame()
{
    std::srand(time(NULL));
    while (!gameAborted_ && !board_.isFinished()) {
        auto& currentPlayer = players_[board_.getRound() & 1];
        auto& nextMove = currentPlayer->getNextMove(this);

        if (!gameAborted_ && board_.isAvailable(nextMove.first, nextMove.second)) {
            board_.insert(nextMove.first, nextMove.second, currentPlayer->getId());
            update();
        }
    }
    qDebug() << "game thread ended";
}

/**
 * @brief Aborts currently running game.
 *
 * Waits for a running game to finish.
 */
void GameWidget::abortGame()
{
    gameThreadMutex_.lock();
    gameAborted_ = true;
    mouseInputCondition_.wakeAll();
    gameThreadMutex_.unlock();
    gameThreadFuture_.waitForFinished();
}

/**
 * @brief Returns board for the current game.
 *
 * @return  game board
 */
const Board& GameWidget::getBoard() const
{
    return board_;
}

/**
 * @brief Returns mouse input coordinates.
 *
 * The calling thread is blocked until user clicks on the board.
 *
 * @return  pair of coordinates on the board, where the user clicked
 */
const std::pair<int, int>& GameWidget::getMouseInput()
{
    gameThreadMutex_.lock();
    mouseInputCondition_.wait(&gameThreadMutex_);
    gameThreadMutex_.unlock();
    return mouseInput_;
}

/**
 * @brief Mouse press event handler.
 *
 * Computes coordinates on the board and wakes up waiting threads.
 *
 * @param e  QMouseEvent object
 */
void GameWidget::mousePressEvent(QMouseEvent *e)
{
    gameThreadMutex_.lock();
    if (painterViewportRect_.contains(e->pos().x(), e->pos().y())) {
        int x = 3 * (e->pos().x() - painterViewportRect_.x()) / painterViewportRect_.width();
        int y = 3 * (e->pos().y() - painterViewportRect_.y()) / painterViewportRect_.height();
        mouseInput_ = std::make_pair(x, y);
        mouseInputCondition_.wakeAll();
    }
    gameThreadMutex_.unlock();
}

/**
 * @brief Paint event handler.
 */
void GameWidget::paintEvent(QPaintEvent *)
{
    if (!gameStarted_) return;

    int sideLength = std::min(width(), height());
    int left = (width() - sideLength) / 2;
    int top = (height() - sideLength) / 2;
    painterViewportRect_ = QRect(left, top, sideLength, sideLength);
    painterWindowRect_ = QRect(0, 0, sideLength, sideLength);

    QPainter painter(this);
    painter.setViewport(painterViewportRect_);
    painter.setWindow(painterWindowRect_);

    painter.setPen(QPen(QPalette().color(QPalette::Mid)));
    painter.drawLine(sideLength/3, 0, sideLength/3, sideLength-1);
    painter.drawLine(2*sideLength/3, 0, 2*sideLength/3, sideLength-1);
    painter.drawLine(0, sideLength/3, sideLength-1, sideLength/3);
    painter.drawLine(0, 2*sideLength/3, sideLength-1, 2*sideLength/3);

    QPixmap xScaledPixmap = xPixmap_.scaledToWidth(sideLength/3, Qt::SmoothTransformation);
    QPixmap oScaledPixmap = oPixmap_.scaledToWidth(sideLength/3, Qt::SmoothTransformation);
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (board_.get(x, y) == players_[0]->getId()) {
                painter.drawPixmap(x*sideLength/3, y*sideLength/3, sideLength/3, sideLength/3, xScaledPixmap);
            }
            else if (board_.get(x, y) == players_[1]->getId()) {
                painter.drawPixmap(x*sideLength/3, y*sideLength/3, sideLength/3, sideLength/3, oScaledPixmap);
            }
        }
    }

    if (board_.isFinished()) {
        QColor color = palette().color(QPalette::Window);
        color.setAlpha(192);
        painter.setPen(QPen(color));
        painter.setBrush(QBrush(color));
        painter.drawRect(painterWindowRect_);

        painter.setPen(Qt::black);
        QFont overlayFont = font();
        overlayFont.setPointSize(sideLength/10);
        painter.setFont(overlayFont);

        QString winnerString;
        if (board_.isDraw()) winnerString = "Game drawn";
        if (0 == board_.getWinner()) winnerString = "Player 1 won";
        if (1 == board_.getWinner()) winnerString = "Player 2 won";
        painter.drawText(painterWindowRect_, Qt::AlignCenter, winnerString);
    }
}
