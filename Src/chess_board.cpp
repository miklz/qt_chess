#include "chess_board.h"

Square* Piece::getSquare(std::vector<Square*> list, Square *find) {

    int row, col;
    auto it = list.begin();

    for(it = list.begin(); it != list.end(); ++it) {
        row = (*it)->get_row();
        col = (*it)->get_column();
        if((row == find->get_row()) && (col == find->get_column()))
            break;
    }

    return *it;
}

bool Pawn::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    if(handleBlock(start, end, squares)) {
        return false;
    }

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    if(col_begin != col_fini) {
        int col_offset = col_fini - col_begin;

        if((col_offset > 1) || (col_offset < -1)) {
            return false;
        }

        if(end->getPiece() == nullptr) {
            return false;
        }
    }

    int row_offset = row_fini - row_begin;
    if((row_offset > 2) || (row_offset < -2)) {
        return false;
    }

    if(!Moved && ((row_offset > 1) || (row_offset < -1))) {
        return false;
    }

    return true;
}

bool Pawn::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {
    int col_begin = start->get_column();
    int col_fini = end->get_column();

    if(col_fini == col_begin) {
        if(end->getPiece() != nullptr) {
            return true;
        }
    }

    if(end->getPiece()->color() == _color) {
        return true;
    }

    return false;
}

bool Knight::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    if(handleBlock(start, end, squares)) {
        return false;
    }

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    // All possible moves of a knight 
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; i++) {
        // Position of knight after move
        int x = col_begin + X[i];
        int y = row_begin + Y[i];

        if((x == col_fini) && (y == row_fini)) {
            return true;
        }
    }

    return false;
}

bool Knight::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {

    if(end->getPiece()->color() == _color) {
        return true;
    }

    return false;
}

bool Bishop::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    int x = col_fini - col_begin;
    int y = row_fini - row_begin;

    if(x != y) {
        return false;
    }

    if(handleBlock(start, end, squares)) {
        return false;
    }

    return true;
}

bool Bishop::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {

    if(end->getPiece()->color() == _color) {
        return true;
    }

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    int x = col_fini - col_begin;
    int y = row_fini - row_begin;

    Piece *piece;
    Square *empty;
    if((x > 0) && (y > 0)) {
        for(int i = col_begin + 1; i < col_fini; ++i) {
            empty = getSquare(squares, new Square(i, i));
            piece = empty->getPiece();
            if(piece != nullptr) {
                return true;
            }
        }
    } else if((x > 0) && (y < 0)) {
        for(int i = col_begin + 1; i < col_fini; ++i) {
            empty = getSquare(squares, new Square(-i, i));
            piece = empty->getPiece();
            if(piece != nullptr) {
                return true;
            }
        }
    } else if((x < 0) && (y > 0)) {
        for(int i = row_begin + 1; i < row_fini; ++i) {
            empty = getSquare(squares, new Square(i, -i));
            piece = empty->getPiece();
            if(piece != nullptr) {
                return true;
            }
        }
    } else {
        for(int i = row_fini - 1; i < row_begin; ++i) {
            empty = getSquare(squares, new Square(i, i));
            piece = empty->getPiece();
            if(piece != nullptr) {
                return true;
            }
        }
    }

    return false;
}

bool Rook::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    if((row_begin != row_fini) && (col_begin != col_fini)) {
        return false;
    }

    if(handleBlock(start, end, squares)) {
        return false;
    }

    return true;
}

bool Rook::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {

    if(end->getPiece()->color() == _color) {
        return false;
    }

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    Piece *piece;
    Square *empty;
    if(row_begin == row_fini) {
        int x = col_fini - col_begin;
        if(x > 0) {
            for(int i = col_begin + 1; i < col_fini; ++i) {
                empty = getSquare(squares, new Square(row_begin, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else {
            for(int i = col_fini - 1; i < col_begin; ++i) {
                empty = getSquare(squares, new Square(row_begin, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        }
    } else {
        int y = row_fini - row_begin;
        if(y > 0) {
            for(int i = row_begin + 1; i < row_fini; ++i) {
                empty = getSquare(squares, new Square(i, col_begin));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else {
            for(int i = row_fini + 1; i < row_begin; ++i) {
                empty = getSquare(squares, new Square(i, col_begin));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Queen::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    int x = col_fini - col_begin;
    int y = row_fini - row_begin;

    if((row_begin != row_fini) && (col_begin != col_fini) && (x != y)) {
        return false;
    }

    if(handleBlock(start, end, squares)) {
        return false;
    }

    return true;
}

bool Queen::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {
    if(end->getPiece()->color() == _color) {
        return true;
    }

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    int x = col_fini - col_begin;
    int y = row_fini - row_begin;

    Piece *piece;
    Square *empty;
    if(row_begin == row_fini) {
        if(x > 0) {
            for(int i = col_begin + 1; i < col_fini; ++i) {
                empty = getSquare(squares, new Square(row_begin, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else {
            for(int i = col_fini - 1; i < col_begin; ++i) {
                empty = getSquare(squares, new Square(row_begin, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        }
    } else if(col_begin == col_fini) {
        if(y > 0) {
            for(int i = row_begin + 1; i < row_fini; ++i) {
                empty = getSquare(squares, new Square(i, col_begin));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else {
            for(int i = row_fini + 1; i < row_begin; ++i) {
                empty = getSquare(squares, new Square(i, col_begin));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        }
    } else {
        if((x > 0) && (y > 0)) {
            for(int i = col_begin + 1; i < col_fini; ++i) {
                empty = getSquare(squares, new Square(i, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else if((x > 0) && (y < 0)) {
            for(int i = col_begin + 1; i < col_fini; ++i) {
                empty = getSquare(squares, new Square(-i, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else if((x < 0) && (y > 0)) {
            for(int i = row_begin + 1; i < row_fini; ++i) {
                empty = getSquare(squares, new Square(i, -i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        } else {
            for(int i = row_fini - 1; i < row_begin; ++i) {
                empty = getSquare(squares, new Square(i, i));
                piece = empty->getPiece();
                if(piece != nullptr) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool King::validMove(Square *start, Square *end, std::vector<Square*> squares) {

    int row_begin = start->get_row();
    int col_begin = start->get_column();
    int row_fini = end->get_row();
    int col_fini = end->get_column();

    int x = col_fini - col_begin;
    int y = row_fini - row_begin;

    if((x > 1) || (x < -1) || (y > 1) || (y < -1)) {
        return false;
    }

    if(handleBlock(start, end, squares)) {
        return false;
    }

    return true;
}

bool King::handleBlock(Square *start, Square *end, std::vector<Square*> squares) {

    if(end->getPiece()->color() == _color) {
        return true;
    }

    return false;
}
