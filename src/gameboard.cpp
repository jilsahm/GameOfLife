#include "gameboard.h"

GameBoard::GameBoard(QQuickItem * parent)
    : QQuickPaintedItem(parent)
{
    this->setFlag(Flag::ItemHasContents, true);
}

void GameBoard::paint(QPainter * painter){
    static auto drawingArea = make_shared<QImage>(this->width(), this->height(), QImage::Format_ARGB32);
    QRgb color = qRgb(0, 0, 0);
    drawingArea->setPixel(10, 10, color);
    drawingArea->setPixel(11, 11, color);
    drawingArea->setPixel(12, 12, color);
    painter->drawImage(0, 0, *drawingArea);
    painter->drawLine(0,0,100,100);
    painter->drawPoint(300,300);
    qWarning() << this->width() << "x" << this->height();
    qWarning() << drawingArea->width() << "x" << drawingArea->height();
}
