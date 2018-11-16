#include "gameboard.h"

GameBoard::GameBoard(QQuickItem * parent)
    : QQuickPaintedItem(parent),
      idealThreadCount{QThread::idealThreadCount()},
      cells{nullptr},
      mutex{}
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
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    std::vector<std::thread> threadgroup {};
    const int linePack {drawingArea->height() / this->idealThreadCount};
    int lineIndex {0};
    for (int currentThread = 0; currentThread < this->idealThreadCount; currentThread++){
        threadgroup.push_back(
            std::thread{&GameBoard::partitionDraw, this, drawingArea, lineIndex, lineIndex + linePack}
        );
        lineIndex += linePack;
    }
    for (auto& thread : threadgroup){
        thread.join();
    }

    this->partitionDraw(drawingArea, 0, 100);

    painter->drawImage(0, 0, *drawingArea);
    qInfo() << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - starttime << " milliseconds for updating the canvas.";
}

void GameBoard::partitionDraw(shared_ptr<QImage> image, size_t fromLine, size_t toLine){
    const size_t numberOfColumns = static_cast<size_t>(image->width());
    for (; fromLine <= toLine; fromLine++){
        QRgb *currentLine = (QRgb *)image->scanLine(fromLine);
        for (size_t currentColumn = 0; currentColumn < numberOfColumns; currentColumn++, currentLine++){
            if (this->cells->getCell(currentColumn, fromLine) == 1){
                *currentLine = *this->colorLifingCell;
            } else {
                *currentLine = *this->colorDeadCell;
            }
        }
    }
}

void GameBoard::init(const long width, const long height){
    std::lock_guard<std::mutex> lockguard{this->mutex};
    this->cells = make_unique<Cells>(width, height);
}

void GameBoard::nextGeneration(){
    std::lock_guard<std::mutex> lockguard{this->mutex};
    this->cells->update();
}

void GameBoard::spawnCell(const long x, const long y){
    std::lock_guard<std::mutex> lockguard{this->mutex};
    this->cells->spawnCell(x, y);
}
