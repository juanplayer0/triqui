#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Triqui");
    board = new GameBoard(this);
    setCentralWidget(board);
}

MainWindow::~MainWindow() { delete ui; }
