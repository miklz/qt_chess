#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include <QtWidgets>

enum class PieceType {None, Pawn, Knight, Bishop, Rook, Queen, King};

enum class PieceColor {None, White, Black};

class Square;
class ChessGame;

class Piece {
    public:
        Piece(PieceColor color, PieceType type): _color(color), _type(type) {};

        PieceType type() {
            return _type;
        };

        PieceColor color() {
            return _color;
        };

        QPixmap get_icon() {
            return _icon;
        };

        virtual bool validMove(Square *start, Square *end, std::vector<Square*> squares) = 0;
        virtual bool handleBlock(Square *start, Square *end, std::vector<Square*> squares) = 0;

    protected:
        PieceColor _color;
        PieceType _type;
        QPixmap _icon;

        Square* getSquare(std::vector<Square*> list, Square *find);
};

class Square {
    public:
        Square(int row, int col):
            _row(row), _column(col), _piece(nullptr) {};
        Square(int row, int col, Piece *piece):
            _row(row), _column(col), _piece(piece) {};

        int get_row(void) {
            return _row;
        };

        int get_column(void) {
            return _column;
        };

        Piece* getPiece() {
            return _piece;
        };

        void setPiece(Piece *piece) {
            _piece = piece;
        };


    private:
        int _row;
        int _column;
        Piece *_piece;
};

class Pawn : public Piece {
    public:
        Pawn(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_plt45_pawn.svg");
            } else {
                _icon.load(":/icons/Chess_pdt45_pawn.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);

    private:
        bool Moved = false;
        bool Promoted;
        //Piece promoteTo;
};

class Knight : public Piece {
    public:
        Knight(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_nlt45_knight.svg");
            } else {
                _icon.load(":/icons/Chess_ndt45_knight.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);
};

class Bishop : public Piece {
    public:
        Bishop(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_blt45_bishop.svg");
            } else {
                _icon.load(":/icons/Chess_bdt45_bishop.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);
};

class Rook : public Piece {
    public:
        Rook(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_rlt45_rook.svg");
            } else {
                _icon.load(":/icons/Chess_rdt45_rook.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);
};

class Queen : public Piece {
    public:
        Queen(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_qlt45_queen.svg");
            } else {
                _icon.load(":/icons/Chess_qdt45_queen.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);
};

class King : public Piece {
    public:
        King(PieceColor color, PieceType type): Piece(color, type) {
            if(color == PieceColor::White) {
                _icon.load(":/icons/Chess_klt45_king.svg");
            } else {
                _icon.load(":/icons/Chess_kdt45_king.svg");
            }
        };

        bool validMove(Square *start, Square *end, std::vector<Square*> squares);

        bool handleBlock(Square *start, Square *end, std::vector<Square*> squares);
};

class Board {
    public:
        // Create a piece on the board
        bool initPiece(PieceType type, PieceColor color, Square place);

        // Return the pointer of a piace at this specific location or nullptr the square is empty
        Piece* getPiece(Square place);

    protected:
        PieceColor turn;
        unsigned int m_width, m_height;
        std::vector<Piece*> pieces;
        Piece* newPiece(PieceType type, PieceColor color);
};

class ChessGame : public Board {
    public:
        // Setup the initial position of the board
        void setupBoard() {
            for(int i = 7; i >= 0; i--) {
                if(i == 7) {
                    chess_board.push_back(new Square(i, 0, new Rook(PieceColor::Black, PieceType::Rook)));
                    chess_board.push_back(new Square(i, 1, new Knight(PieceColor::Black, PieceType::Knight)));
                    chess_board.push_back(new Square(i, 2, new Bishop(PieceColor::Black, PieceType::Bishop)));
                    chess_board.push_back(new Square(i, 3, new Queen(PieceColor::Black, PieceType::Queen)));
                    chess_board.push_back(new Square(i, 4, new King(PieceColor::Black, PieceType::King)));
                    chess_board.push_back(new Square(i, 5, new Bishop(PieceColor::Black, PieceType::Bishop)));
                    chess_board.push_back(new Square(i, 6, new Knight(PieceColor::Black, PieceType::Knight)));
                    chess_board.push_back(new Square(i, 7, new Rook(PieceColor::Black, PieceType::Rook)));
                } else if(i == 0) {
                    chess_board.push_back(new Square(i, 0, new Rook(PieceColor::White, PieceType::Rook)));
                    chess_board.push_back(new Square(i, 1, new Knight(PieceColor::White, PieceType::Knight)));
                    chess_board.push_back(new Square(i, 2, new Bishop(PieceColor::White, PieceType::Bishop)));
                    chess_board.push_back(new Square(i, 3, new Queen(PieceColor::White, PieceType::Queen)));
                    chess_board.push_back(new Square(i, 4, new King(PieceColor::White, PieceType::King)));
                    chess_board.push_back(new Square(i, 5, new Bishop(PieceColor::White, PieceType::Bishop)));
                    chess_board.push_back(new Square(i, 6, new Knight(PieceColor::White, PieceType::Knight)));
                    chess_board.push_back(new Square(i, 7, new Rook(PieceColor::White, PieceType::Rook)));
                } else {
                    for(int j = 0; j < 8; j++) {
                        if(i == 6) {
                            chess_board.push_back(new Square(i, j, new Pawn(PieceColor::Black, PieceType::Pawn)));
                        } else if(i == 1) {
                            chess_board.push_back(new Square(i, j, new Pawn(PieceColor::White, PieceType::Pawn)));
                        } else {
                            chess_board.push_back(new Square(i, j));
                        }
                    }
                }
            }
        }

        // Performs a move and retorn true if succeds or false if not
        bool makeMove(Square *start, Square *end) {
            Square *begin = getSquare(chess_board, start);
            Square *fini = getSquare(chess_board, end);
            Piece *toMove = start->getPiece();

            // Confirms if there's a piece there
            if(toMove == nullptr) {
                return false;
            }

            // Of who is the turn
            if(toMove->color() != _turn) {
                return false;
            }

            if(toMove->validMove(start, end, chess_board)) {
                begin->setPiece(nullptr);
                fini->setPiece(toMove);

                // Change Turns
                if(toMove->color() == PieceColor::White) {
                    _turn = PieceColor::Black;
                } else {
                    _turn = PieceColor::White;
                }
                return true;
            }
            return false;
        }

        // What piece is being checked
        PieceColor check();

        // Returns true if we got to a stalemate false if not
        bool Stalemate();

        // Returns true if we got to a checkmate false if not
        bool checkMate(PieceColor status);

        PieceColor colorTurn() {
            return _turn;
        }

        std::vector<Square*> get_set() {
            return chess_board;
        }

        Square* squareAt(int row, int col) {
            int row_s, col_s;
            auto it = chess_board.begin();
            for(it = chess_board.begin(); it != chess_board.end(); ++it) {
                row_s = (*it)->get_row();
                col_s = (*it)->get_column();
                if((row_s == row) && (col_s == col)) {
                    break;
                }
            }
            return *it;
        }

        ~ChessGame() {
            chess_board.clear();
        }

    protected:
        std::vector<Square*> chess_board;
        Square * getSquare(std::vector<Square*> list, Square* find) {
            int row, col;
            auto it = list.begin();
            for(it = list.begin(); it != list.end(); ++it) {
                row = (*it)->get_row();
                col = (*it)->get_column();
                if((row == find->get_row()) && (col == find->get_column())) {
                    break;
                }
            }
            return *it;
        }
        // What piece is being checked
        PieceColor _status;

        // Which player has the turn
        PieceColor _turn = PieceColor::White;
};
