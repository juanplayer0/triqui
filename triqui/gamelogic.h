#pragma once
#include <QString>

class GameLogic {
public:
    GameLogic();
    bool makeMove(int row, int col);
    char checkWinner();
    bool isBoardFull();
    void reset();
    char getCell(int row, int col) const;
    char getCurrentPlayer() const;

private:
    char board[3][3];
    char currentPlayer;
};
