#include <iostream>

#include <QApplication>

#include "chess_board.h"
#include "chess_graphic.h"

int main(int argc, char *argv[]) {
/*
    ChessGame game;

    game.setupBoard();

    int i = 0;
    int move[5];
    while(i < 5) {
        game.print_board();
        std::cin >> move[0];
        std::cin >> move[1];
        std::cin >> move[2];
        std::cin >> move[3];
        game.makeMove(new Square(move[0], move[1]), new Square(move[2], move[3]));
    }
*/

    QApplication app(argc, argv);

    ChessGame game;

    game.setupBoard();

    GraphicBoard *window = new GraphicBoard(&game);

//    window->setPieces(game.get_set());
    window->show();

    return app.exec();
}
