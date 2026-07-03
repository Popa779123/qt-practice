#include "mainwindow.h"
#include "ui_chess.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            board[r][c] = nullptr;
        }
    }


    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QString btnName = QString("btn_%1_%2").arg(row).arg(col);
            buttons[row][col] = findChild<QPushButton*>(btnName);
            if (buttons[row][col]) {
                QFont font = buttons[row][col]->font();
                font.setPointSize(28);
                buttons[row][col]->setFont(font);
                connect(buttons[row][col], &QPushButton::clicked, this, [this, row, col]() {
                    onCellClicked(row, col);
                });
            }
        }
    }

    // Кэш иконок
    pieceIcons[0][0] = QIcon(":/images/wK.png"); pieceIcons[1][0] = QIcon(":/images/bK.png");
    pieceIcons[0][1] = QIcon(":/images/wQ.png"); pieceIcons[1][1] = QIcon(":/images/bQ.png");
    pieceIcons[0][2] = QIcon(":/images/wR.png"); pieceIcons[1][2] = QIcon(":/images/bR.png");
    pieceIcons[0][3] = QIcon(":/images/wB.png"); pieceIcons[1][3] = QIcon(":/images/bB.png");
    pieceIcons[0][4] = QIcon(":/images/wN.png"); pieceIcons[1][4] = QIcon(":/images/bN.png");
    pieceIcons[0][5] = QIcon(":/images/wP.png"); pieceIcons[1][5] = QIcon(":/images/bP.png");

    initBoard();
    updateBoardUI();
    setWindowTitle("Ход белых");
}

MainWindow::~MainWindow()
{
    clearBoard();
    delete ui;
}

void MainWindow::clearBoard()
{
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            delete board[r][c];
            board[r][c] = nullptr;
        }
    }
}

void MainWindow::initBoard()
{
    clearBoard();

    // Чёрные фигуры
    board[0][0] = new Rook(PieceColor::BLACK);
    board[0][7] = new Rook(PieceColor::BLACK);
    board[0][1] = new Knight(PieceColor::BLACK);
    board[0][6] = new Knight(PieceColor::BLACK);
    board[0][2] = new Bishop(PieceColor::BLACK);
    board[0][5] = new Bishop(PieceColor::BLACK);
    board[0][3] = new Queen(PieceColor::BLACK);
    board[0][4] = new King(PieceColor::BLACK);
    for (int c = 0; c < 8; ++c)
        board[1][c] = new Pawn(PieceColor::BLACK);

    // Белые фигуры
    board[7][0] = new Rook(PieceColor::WHITE);
    board[7][7] = new Rook(PieceColor::WHITE);
    board[7][1] = new Knight(PieceColor::WHITE);
    board[7][6] = new Knight(PieceColor::WHITE);
    board[7][2] = new Bishop(PieceColor::WHITE);
    board[7][5] = new Bishop(PieceColor::WHITE);
    board[7][3] = new Queen(PieceColor::WHITE);
    board[7][4] = new King(PieceColor::WHITE);
    for (int c = 0; c < 8; ++c)
        board[6][c] = new Pawn(PieceColor::WHITE);
}

void MainWindow::updateBoardUI()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton* btn = buttons[row][col];
            if (!btn) continue;

            Piece* p = board[row][col];
            if (p) {
                int colorIdx = (p->getColor() == PieceColor::WHITE) ? 0 : 1;
                int typeIdx  = p->getTypeIndex();
                btn->setIcon(pieceIcons[colorIdx][typeIdx]);
                btn->setIconSize(QSize(50, 50));
            } else {
                btn->setIcon(QIcon());
            }

            btn->setStyleSheet(
                QString("background-color: %1; border: none;")
                    .arg(getSquareColor(row, col))
                );
        }
    }
}

QString MainWindow::getSquareColor(int row, int col)
{
    return (row + col) % 2 == 0 ? "#f0d9b5" : "#b58863";
}


bool MainWindow::isKingInCheck(PieceColor color)
{
    int kingRow = -1;
    int kingCol = -1;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board[r][c];
            if (p && p->getColor() == color &&
                dynamic_cast<King*>(p)) {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
    }

    if (kingRow == -1)
        return false; // король всегда должен существовать


    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* enemy = board[r][c];
            if (!enemy || enemy->getColor() == color)
                continue;

            if (enemy->isValidMove(board, r, c, kingRow, kingCol))
                return true;
        }
    }

    return false;
}

bool MainWindow::hasAnyValidMoves(PieceColor color)
{
    for (int r1 = 0; r1 < 8; ++r1) {
        for (int c1 = 0; c1 < 8; ++c1) {

            Piece* piece = board[r1][c1];
            if (!piece || piece->getColor() != color)
                continue;

            for (int r2 = 0; r2 < 8; ++r2) {
                for (int c2 = 0; c2 < 8; ++c2) {

                    Piece* target = board[r2][c2];

                    if (target && target->getColor() == color)
                        continue;


                    if (target && dynamic_cast<King*>(target))
                        continue;

                    if (!piece->isValidMove(board, r1, c1, r2, c2))
                        continue;


                    Piece* captured = board[r2][c2];
                    board[r2][c2] = piece;
                    board[r1][c1] = nullptr;

                    bool inCheck = isKingInCheck(color);

                    // откат
                    board[r1][c1] = piece;
                    board[r2][c2] = captured;

                    if (!inCheck)
                        return true;
                }
            }
        }
    }
    return false;
}
void MainWindow::onCellClicked(int row, int col)
{

    if (selectedRow == -1) {
        Piece* p = board[row][col];
        if (p && p->getColor() == currentTurn) {
            selectedRow = row;
            selectedCol = col;


            buttons[row][col]->setStyleSheet(
                "background-color: yellow; border: none;");
        }
        return;
    }

    Piece* piece = board[selectedRow][selectedCol];
    Piece* target = board[row][col];

        if (target && target->getColor() == currentTurn) {
        selectedRow = -1;
        selectedCol = -1;
        updateBoardUI();
        return;
    }


    if (target && dynamic_cast<King*>(target)) {
        selectedRow = -1;
        selectedCol = -1;
        updateBoardUI();
        return;
    }


    if (!piece->isValidMove(board, selectedRow, selectedCol, row, col)) {
        selectedRow = -1;
        selectedCol = -1;
        updateBoardUI();
        return;
    }


    Piece* captured = board[row][col];

    board[row][col] = piece;
    board[selectedRow][selectedCol] = nullptr;

    if (isKingInCheck(currentTurn)) {
        board[selectedRow][selectedCol] = piece;
        board[row][col] = captured;

        selectedRow = -1;
        selectedCol = -1;
        updateBoardUI();
        return;
    }


    delete captured;
    if (piece->getTypeIndex() == 5) { // если пешка
        if (piece->getColor() == PieceColor::WHITE && row == 0) {
            delete board[row][col];
            board[row][col] = new Queen(PieceColor::WHITE);
        }
        else if (piece->getColor() == PieceColor::BLACK && row == 7) {
            delete board[row][col];
            board[row][col] = new Queen(PieceColor::BLACK);
        }
    }

    currentTurn = (currentTurn == PieceColor::WHITE)
                      ? PieceColor::BLACK
                      : PieceColor::WHITE;

    selectedRow = -1;
    selectedCol = -1;

    updateBoardUI();


    if (isKingInCheck(currentTurn)) {

        if (!hasAnyValidMoves(currentTurn)) {
            QString winner =
                (currentTurn == PieceColor::WHITE) ? "Чёрные" : "Белые";
            QMessageBox::information(this, "Мат", winner + " победили!");
            on_btnNewGame_clicked();
            return;
        }

        QString side =
            (currentTurn == PieceColor::WHITE) ? "белых" : "чёрных";

        setWindowTitle("ШАХ! Ход " + side);
        QMessageBox::information(this, "Шах",
                                 "Шах королю " + side + "!");
    }
    else if (!hasAnyValidMoves(currentTurn)) {
        QMessageBox::information(this, "Пат", "Ничья!");
        on_btnNewGame_clicked();
        return;
    }
    else {
        QString side =
            (currentTurn == PieceColor::WHITE) ? "белых" : "чёрных";
        setWindowTitle("Ход " + side);
    }
}
void MainWindow::on_btnNewGame_clicked()
{
    clearBoard();
    initBoard();
    currentTurn = PieceColor::WHITE;
    selectedRow = -1;
    selectedCol = -1;
    updateBoardUI();
    setWindowTitle("Ход белых");
}

void MainWindow::on_btnLoadBoard_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть расстановку", "", "Текстовые файлы (*.txt)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    clearBoard();

    int row = 0;
    while (!file.atEnd() && row < 8) {
        QString line = file.readLine().trimmed();

        for (int col = 0; col < 8 && col < line.length(); ++col) {
            QChar ch = line[col];

            if (ch == '.' || ch == ' ') {
                board[row][col] = nullptr;
                continue;
            }

            PieceColor color = ch.isUpper() ? PieceColor::WHITE : PieceColor::BLACK;
            QChar c = ch.toLower();

            switch (c.unicode()) {
            case 'k': board[row][col] = new King(color);   break;
            case 'q': board[row][col] = new Queen(color);  break;
            case 'r': board[row][col] = new Rook(color);   break;
            case 'b': board[row][col] = new Bishop(color); break;
            case 'n': board[row][col] = new Knight(color); break;
            case 'p': board[row][col] = new Pawn(color);   break;
            default:  board[row][col] = nullptr; break;
            }
        }
        row++;
    }

    file.close();

    currentTurn = PieceColor::WHITE;
    selectedRow = -1;
    selectedCol = -1;
    updateBoardUI();
    setWindowTitle("Расстановка загружена. Ход белых");
}
