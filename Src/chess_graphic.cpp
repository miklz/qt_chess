#include "chess_graphic.h"

#define Window_X 400
#define Window_Y 400

#define Square_X 50
#define Square_Y 50

GraphicBoard::GraphicBoard(ChessGame *game, QWidget *parent) :QWidget(parent), chessGame(game) {

    start = nullptr;
    end = nullptr;
    setMinimumSize(Window_X, Window_Y);

    gridInit(game->get_set());

}

void GraphicBoard::gridInit(std::vector<Square*> squares) {

    QGridLayout *grid = new QGridLayout(this);
    grid->setContentsMargins(0,0,0,0);
    grid->setSizeConstraint(QLayout::SetNoConstraint);
    grid->setSpacing(5);

    for(auto & it: squares) {
        int row = it->get_row();
        int col = it->get_column();
        Piece *piece = it->getPiece();

        QLabel *tile = new QLabel(this);
        QPixmap wSquare, bSquare;
        wSquare.load(":/icons/square.png");
        bSquare.load(":/icons/black_square.png");

        if((row + col)%2) {
            tile->setStyleSheet("QLabel {background-color: white;}");
            tile->setPixmap(wSquare);
        } else {
            tile->setStyleSheet("QLabel {background-color: rgb(57, 57, 57);}");
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

void GraphicBoard::setPieces(std::vector<Square*> squares, Square *last_move) {

    QLayout *layout = this->layout();
    for(auto & it: squares) {
        int row = it->get_row();
        int col = it->get_column();
        Piece *p = it->getPiece();

        QPixmap wSquare, bSquare;
        wSquare.load(":/icons/square.png");
        bSquare.load(":/icons/black_square.png");

        Q_ASSERT(layout->count() == 64);
        QLayoutItem* const item = layout->itemAt(8*(7 - row) + col);
        if(item) {
            QLabel *tile = dynamic_cast<QLabel*> (item->widget());

            if((row + col)%2) {
                tile->setPixmap(wSquare);
                tile->setStyleSheet("QLabel {background-color: white;}");
            } else {
                tile->setPixmap(bSquare);
                tile->setStyleSheet("QLabel {background-color: rgb(57, 57, 57);}");
            }

            if(last_move != nullptr) {
                if((row == last_move->get_row()) && (col == last_move->get_column())) {
                    tile->setStyleSheet("QLabel {background-color: rgb(245, 235, 107);}");
                }
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

    if(start == nullptr) {
        start = chessGame->squareAt(y, x);
        if(start->getPiece()) {
            if(start->getPiece()->color() == chessGame->colorTurn()) {
                QLayout *layout = this->layout();
                QLayoutItem* const item = layout->itemAt(8*(7 - y) + x);
                QLabel *tile = dynamic_cast<QLabel*> (item->widget());
                tile->setStyleSheet("QLabel {background-color: rgb(202, 143, 247);}");
            } else {
                start = nullptr;
            }
        } else {
            start = nullptr;
        }
    } else if(end == nullptr) {
        end = chessGame->squareAt(y, x);
    }
}

void GraphicBoard::mouseReleaseEvent(QMouseEvent *ev) {
    Q_UNUSED(ev);

    if((start != nullptr) && (end != nullptr)) {
        if(chessGame->makeMove(start, end)) {
            setPieces(chessGame->get_set(), end);
            last_valid_move = end;
        } else {
            setPieces(chessGame->get_set(), last_valid_move);
        }
        start = nullptr;
        end = nullptr;
    }
}
