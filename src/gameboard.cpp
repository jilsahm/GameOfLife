#include "gameboard.h"

GameBoard::GameBoard(QQuickItem * parent)
    : QQuickPaintedItem(parent),
      cells{1920, 700}
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
    static auto drawingArea     = make_shared<QImage>(this->width(), this->height(), QImage::Format_ARGB32);
    size_t      numberOfRows    {static_cast<size_t>(drawingArea->height())};
    size_t      numberOfColumns {static_cast<size_t>(drawingArea->width())};
    QRgb       *currentLine     {nullptr};
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    for (size_t currentRow = 0; currentRow < numberOfRows; currentRow++ ){
        currentLine = (QRgb *)drawingArea->scanLine(currentRow);
        for (size_t currentColumn = 0; currentColumn < numberOfColumns; currentColumn++, currentLine++){
            if (this->cells.getCell(currentColumn, currentRow) == 1){
                *currentLine = *this->colorLifingCell;
            } else {
                *currentLine = *this->colorDeadCell;
            }
        }
    }

    painter->drawImage(0, 0, *drawingArea);
    qInfo() << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - starttime << " milliseconds for updating the canvas.";
    //debug(drawingArea);
    //qWarning() << this->width() << "x" << this->height();
    //qWarning() << drawingArea->width() << "x" << drawingArea->height();
}

void GameBoard::nextGeneration(){
    this->cells.update();
}
