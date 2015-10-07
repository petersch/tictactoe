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
 * Starts a new game against AI, with human being the first player.
 */
void MainWindow::on_actionFirstPlayer_triggered() {
    game->startNewGame(
                std::unique_ptr<Player>(new HumanPlayer()),
                std::unique_ptr<Player>(new MinimaxPlayer())
            );
}

/**
 * Starts a new game against AI, with human being the second player.
 */
void MainWindow::on_actionSecondPlayer_triggered() {
    game->startNewGame(
                std::unique_ptr<Player>(new MinimaxPlayer()),
                std::unique_ptr<Player>(new HumanPlayer())
            );
}
