#include "gameboard.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QVariant>
#include <QFont>

GameBoard::GameBoard(QWidget* parent) : QWidget(parent), gameOver(false) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    statusLabel = new QLabel("Turno de X", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);

    QWidget* gridWidget = new QWidget(this);
    QGridLayout* grid = new QGridLayout(gridWidget);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j] = new QPushButton("", gridWidget);
            buttons[i][j]->setFixedSize(80, 80);
            buttons[i][j]->setProperty("row", i);
            buttons[i][j]->setProperty("col", j);
            buttons[i][j]->setFont(QFont("Arial", 24));
            connect(buttons[i][j], &QPushButton::clicked, this, &GameBoard::onCellClicked);
            grid->addWidget(buttons[i][j], i, j);
        }
    }

    mainLayout->addWidget(gridWidget);

    QPushButton* resetBtn = new QPushButton("Reiniciar", this);
    connect(resetBtn, &QPushButton::clicked, this, &GameBoard::resetGame);
    mainLayout->addWidget(resetBtn);
}

void GameBoard::onCellClicked() {
    if (gameOver) return;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    int row = btn->property("row").toInt();
    int col = btn->property("col").toInt();

    if (!logic.makeMove(row, col)) return;

    char cell = logic.getCell(row, col);
    btn->setText(QString(cell));

    char winner = logic.checkWinner();
    if (winner != ' ') {
        statusLabel->setText(QString("Gano el jugador %1").arg(winner));
        disableAll();
        gameOver = true;
        return;
    }

    if (logic.isBoardFull()) {
        statusLabel->setText("Empate");
        gameOver = true;
        return;
    }

    updateStatus();
}

void GameBoard::styleButton(QPushButton* btn, char symbol) {
    btn->setText(QString(symbol));
}

void GameBoard::updateStatus() {
    char p = logic.getCurrentPlayer();
    statusLabel->setText(QString("Turno de %1").arg(p));
}

void GameBoard::disableAll() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            buttons[i][j]->setEnabled(false);
}

void GameBoard::resetGame() {
    logic.reset();
    gameOver = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j]->setText("");
            buttons[i][j]->setEnabled(true);
        }
    }
    statusLabel->setText("Turno de X");
}
