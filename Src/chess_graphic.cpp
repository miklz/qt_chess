#include "chess_graphic.h"

#define Window_X 400
#define Window_Y 400

#define Square_X 50
#define Square_Y 50

GraphicBoard::GraphicBoard(ChessGame *game, QWidget *parent) : chessGame(game), QWidget(parent) {

    start = nullptr;
    end = nullptr;
    setMinimumSize(Window_X, Window_Y);

    gridInit(game->get_set());

}

void GraphicBoard::gridInit(std::vector<Square*> squares) {

    QGridLayout *grid = new QGridLayout(this);
    grid->setContentsMargins(0,0,0,0);
    grid->setSizeConstraint(QLayout::SetNoConstraint);
    grid->setSpacing(0);

    for(auto & it: squares) {
        int row = it->get_row();
        int col = it->get_column();
        Piece *piece = it->getPiece();

        QLabel *tile = new QLabel(this);
        QPixmap wSquare, bSquare;
        wSquare.load("icons/square.png");
        bSquare.load("icons/blue_square.png");

        if((row + col)%2) {
            tile->setStyleSheet("QLabel {background-color: white;}");
            tile->setPixmap(wSquare);
        } else {
            tile->setStyleSheet("QLabel {background-color: blue;}");
            tile->setPixmap(bSquare);
        }

        if(piece != nullptr) {
            tile->setPixmap(piece->get_icon());
        }

        tile->setContentsMargins(0,0,0,0);
        tile->setScaledContents(true);
        tile->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        grid->addWidget(tile, (7 - row), col, Qt::AlignCenter);
    }

    setLayout(grid);
}

void GraphicBoard::setPieces(std::vector<Square*> squares) {

    QLayout *layout = this->layout();
    for(auto & it: squares) {
        int row = it->get_row();
        int col = it->get_column();
        Piece *p = it->getPiece();

        QPixmap wSquare, bSquare;
        wSquare.load("icons/square.png");
        bSquare.load("icons/blue_square.png");

        Q_ASSERT(layout->count() == 64);
        QLayoutItem* const item = layout->itemAt(8*(7 - row) + col);
        if(item) {
            QLabel *tile = dynamic_cast<QLabel*> (item->widget());
            if((row + col)%2) {
                tile->setPixmap(wSquare);
            } else {
                tile->setPixmap(bSquare);
            }

            if(p) {
                tile->setPixmap(p->get_icon());
            }
        }
    }
}

void GraphicBoard::mousePressEvent(QMouseEvent *ev) {

    int x, y;
    x = ev->x()/Square_X;
    y = 7 - (ev->y()/Square_Y);


    if(start==nullptr) {
        start = chessGame->squareAt(new Square(y, x));
    } else if(end == nullptr) {
        end = chessGame->squareAt(new Square(y, x));
    }

    std::cout << "(" << y << "," << x << ")" << std::endl;
}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *ev) {

    if((start != nullptr) && (end !=nullptr)) {
        chessGame->makeMove(start, end);
        start = nullptr;
        end = nullptr;
        setPieces(chessGame->get_set());
    }
}
