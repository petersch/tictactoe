#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/gamewidget.h"
#include "include/humanplayer.h"
#include "include/minimaxplayer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    game = new GameWidget(this);
    setCentralWidget(game);

    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
}

/**
 * @brief Starts a new game against AI, with human being the first player.
 */
void MainWindow::on_actionFirstPlayer_triggered() {
    std::unique_ptr<Player> player1(new HumanPlayer());
    std::unique_ptr<Player> player2(new MinimaxPlayer());
    game->startNewGame(player1, player2);
}

/**
 * @brief Starts a new game against AI, with human being the second player.
 */
void MainWindow::on_actionSecondPlayer_triggered() {
    std::unique_ptr<Player> player1(new MinimaxPlayer());
    std::unique_ptr<Player> player2(new HumanPlayer());
    game->startNewGame(player1, player2);
}
