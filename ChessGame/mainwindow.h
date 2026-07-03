#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSize>
#include "piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCellClicked(int row, int col);
    void on_btnLoadBoard_clicked();
    void on_btnNewGame_clicked();

private:
    Ui::MainWindow *ui;

    Piece* board[8][8];
    PieceColor currentTurn = PieceColor::WHITE;

    int selectedRow = -1;
    int selectedCol = -1;

    QIcon pieceIcons[2][6];
    QPushButton* buttons[8][8];

    void initBoard();
    void clearBoard();
    void updateBoardUI();
    QString getSquareColor(int row, int col);
    bool isKingInCheck(PieceColor color);
    bool hasAnyValidMoves(PieceColor color);
};

#endif // MAINWINDOW_H
