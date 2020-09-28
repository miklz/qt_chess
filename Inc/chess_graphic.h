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
        void paintEvent(QPaintEvent* pe);
        void setPieces(std::vector<Square*> squares);

        //~GraphicBoard();

    private:
        ChessGame *chessGame;
        QGridLayout *grid;
};
