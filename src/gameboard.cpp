#include "gameboard.h"

GameBoard::GameBoard(QQuickItem * parent)
    : QQuickPaintedItem(parent)
{
    this->colorLifingCell = make_unique<QRgb>(qRgb(100, 255, 100));
    this->colorDeadCell   = make_unique<QRgb>(qRgb(32, 32, 32));
    this->setFlag(Flag::ItemHasContents, true);
}

void GameBoard::debug(shared_ptr<QImage> image){
    int   numberOfRows    {image->height()};
    int   numberOfColumns {image->width()};
    QRgb *currentLine     {nullptr};

    for (int currentRow = 0; currentRow < numberOfRows; currentRow++ ){
        currentLine = (QRgb *)image->scanLine(currentRow);
        for (int currentColumn = 0; currentColumn < numberOfColumns; currentColumn++, currentLine++){
            if (currentColumn % 2 == 0){
                *currentLine = *this->colorLifingCell;
            } else {
                *currentLine = *this->colorDeadCell;
            }
        }
    }
}

void GameBoard::paint(QPainter * painter){
    static auto drawingArea = make_shared<QImage>(this->width(), this->height(), QImage::Format_ARGB32);
    QRgb color = qRgb(0, 0, 255);
    drawingArea->setPixel(0, 0, color);
    painter->drawImage(0, 0, *drawingArea);
    debug(drawingArea);
    //qWarning() << this->width() << "x" << this->height();
    //qWarning() << drawingArea->width() << "x" << drawingArea->height();
}
