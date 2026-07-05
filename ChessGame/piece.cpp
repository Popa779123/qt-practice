#include "piece.h"


bool Piece::isPathClear(const Board board, int fromRow, int fromCol, int toRow, int toCol)
{
    int rowStep = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colStep = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;

    int currentRow = fromRow + rowStep;
    int currentCol = fromCol + colStep;

    while (currentRow != toRow || currentCol != toCol) {
        if (board[currentRow][currentCol] != nullptr) return false;
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}


bool King::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {

    if (fromRow == toRow && fromCol == toCol) return false;

    return abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1;
}

bool Queen::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {
    if (fromRow == toRow && fromCol == toCol) return false;
    bool straight = (fromRow == toRow || fromCol == toCol);
    bool diagonal = (abs(fromRow - toRow) == abs(fromCol - toCol));
    if (straight || diagonal) return isPathClear(board, fromRow, fromCol, toRow, toCol);
    return false;
}


bool Rook::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {
    if (fromRow == toRow && fromCol == toCol) return false;
    if (fromRow != toRow && fromCol != toCol) return false;
    return isPathClear(board, fromRow, fromCol, toRow, toCol);
}


bool Bishop::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {
    if (fromRow == toRow && fromCol == toCol) return false;
    if (abs(fromRow - toRow) != abs(fromCol - toCol)) return false;
    return isPathClear(board, fromRow, fromCol, toRow, toCol);
}


bool Knight::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {
    int r = abs(fromRow - toRow);
    int c = abs(fromCol - toCol);
    return (r == 2 && c == 1) || (r == 1 && c == 2);
}


bool Pawn::isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const {
    int direction = (color == PieceColor::WHITE) ? -1 : 1;
    int startRow  = (color == PieceColor::WHITE) ?  6 :  1;
    int rowDiff   = toRow - fromRow;
    int colDiff   = toCol - fromCol;


    if (colDiff == 0 && rowDiff == direction && board[toRow][toCol] == nullptr)
        return true;

    
    if (colDiff == 0 && rowDiff == 2 * direction && fromRow == startRow && !hasMoved) {
        if (board[toRow][toCol] == nullptr &&
            board[fromRow + direction][fromCol] == nullptr)
            return true;
    }

    if (abs(colDiff) == 1 && rowDiff == direction && board[toRow][toCol] != nullptr)
        return true;

    return false;
}
