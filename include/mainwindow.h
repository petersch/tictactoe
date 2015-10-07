#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class GameWidget;

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    GameWidget *game;
private slots:
    void on_actionFirstPlayer_triggered();
    void on_actionSecondPlayer_triggered();
};

#endif // MAINWINDOW_H
