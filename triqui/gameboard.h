#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "gamelogic.h"

class GameBoard : public QWidget {
    Q_OBJECT

public:
    explicit GameBoard(QWidget* parent = nullptr);

private slots:
    void onCellClicked();
    void resetGame();

private:
    QPushButton* buttons[3][3];
    QLabel* statusLabel;
    GameLogic logic;
    bool gameOver;

    void updateStatus();
    void disableAll();
    void styleButton(QPushButton* btn, char symbol);
};
