#ifndef PIECE_H
#define PIECE_H

#include <cmath>

enum class PieceColor { WHITE, BLACK };

class Piece;
using Board = Piece*[8][8];


class Piece
{
protected:
    PieceColor color;

public:
    Piece(PieceColor c) : color(c) {}
    virtual ~Piece() {}

    static bool isPathClear(const Board board, int fromRow, int fromCol, int toRow, int toCol);
    PieceColor getColor() const { return color; }

    virtual bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const = 0;
    virtual int getTypeIndex() const = 0;
    virtual bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const = 0;
};

class King : public Piece {
public:
    King(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 0; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        return abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1 &&
               (abs(fromRow - toRow) + abs(fromCol - toCol) > 0);
    }
};

class Queen : public Piece {
public:
    Queen(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 1; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        return (fromRow == toRow || fromCol == toCol) ||
               (abs(fromRow - toRow) == abs(fromCol - toCol));
    }
};


class Rook : public Piece {
public:
    Rook(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 2; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        return (fromRow == toRow || fromCol == toCol);
    }
};


class Bishop : public Piece {
public:
    Bishop(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 3; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        return abs(fromRow - toRow) == abs(fromCol - toCol);
    }
};


class Knight : public Piece {
public:
    Knight(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 4; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        int r = abs(fromRow - toRow);
        int c = abs(fromCol - toCol);
        return (r == 2 && c == 1) || (r == 1 && c == 2);
    }
};


class Pawn : public Piece {
private:
    bool hasMoved = false;
public:
    Pawn(PieceColor c) : Piece(c) {}
    bool isValidMove(const Board board, int fromRow, int fromCol, int toRow, int toCol) const override;
    int getTypeIndex() const override { return 5; }
    void setHasMoved() { hasMoved = true; }
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const override {
        int direction = (color == PieceColor::WHITE) ? -1 : 1;
        return abs(fromCol - toCol) == 1 && (toRow - fromRow) == direction;
    }
    void markAsMoved() { hasMoved = true; }
    void resetMoved() { hasMoved = false; }
    bool getHasMoved() const { return hasMoved; }
};

#endif // PIECE_H
