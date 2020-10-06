#include <iostream>

#include <QApplication>

#include "chess_board.h"
#include "chess_graphic.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ChessGame game;

    game.setupBoard();

    GraphicBoard *window = new GraphicBoard(&game);

    window->show();

    return app.exec();
}
