#include "chess_graphic.h"

#define Window_X 400
#define Window_Y 400

#define Square_X 50
#define Square_Y 50

GraphicBoard::GraphicBoard(ChessGame *game, QWidget *parent) : chessGame(game), QWidget(parent) {

    setMinimumSize(Window_X, Window_Y);

}

void GraphicBoard::paintEvent(QPaintEvent* pe) {
    std::cout << "Painting" << std::endl;
    // Initialization
    unsigned int numCellX = 8, numCellY = 8;
    QRect wRect = rect();
    unsigned int cellSizeX = wRect.width() / numCellX;
    unsigned int cellSizeY = wRect.height() / numCellY;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the background. The whole widget is drawed.
    painter.setBrush(QColor(0,0,255)); //blue
    painter.drawRect(wRect);

    // Draw the cells which are of the other color
    // Note: the grid may not fit in the whole rect, because the size of the widget
    // should be a multiple of the size of the cells. If not, a black line at the right
    // and at the bottom may appear.
    painter.setBrush(QColor(255,255,255)); //white
    for(unsigned int j = 0; j < numCellY; j++)
        for(unsigned int i = j % 2; i < numCellX; i+=2)
            painter.drawRect(i * cellSizeX, j * cellSizeY, cellSizeX, cellSizeY);

    setPieces(chessGame->get_set());
}

void GraphicBoard::setPieces(std::vector<Square*> squares) {

    for(auto & it: squares) {
        int row = it->get_row();
        int col = it->get_column();
        Piece *p = it->getPiece();

        if(p) {
            QLabel *piece = new QLabel(this);
            std::cout << "Pieces" << std::endl;
            piece->setPixmap(p->get_icon());
            piece->setGeometry(col*Square_X, (7 - row)*Square_Y, Square_X, Square_Y);
            piece->show();
        }
    }
}
