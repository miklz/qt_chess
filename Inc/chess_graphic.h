#pragma once

#include <QtWidgets>
#include <QPainter>
#include <vector>

#include "chess_board.h"

class GraphicBoard : public QWidget {
    Q_OBJECT

    public:
        GraphicBoard(ChessGame *game, QWidget *parent = 0);

        void gridInit(std::vector<Square*> squares);
        void setPieces(std::vector<Square*> squares, Square *last_move);

    private:
        std::vector<Square*> chess_board;
        ChessGame *chessGame;
        QGridLayout *grid;
        Square *start;
        Square *end;

        void mousePressEvent(QMouseEvent *ev);
        void mouseReleaseEvent(QMouseEvent *ev);
};
