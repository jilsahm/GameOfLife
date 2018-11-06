#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>
#include <thread>
#include <vector>

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QThread>

#include "cells.h"

using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

class GameBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    GameBoard(QQuickItem * parent = nullptr);
    void paint(QPainter *) override;
    void debug(shared_ptr<QImage>);
    Q_INVOKABLE void init(const long, const long);
    Q_INVOKABLE void nextGeneration();    

private:
    void partitionDraw(shared_ptr<QImage>, size_t, size_t);

    const int         idealThreadCount;
    unique_ptr<QRgb>  colorLifingCell;
    unique_ptr<QRgb>  colorDeadCell;
    unique_ptr<Cells> cells;
};

#endif // GAMEBOARD_H
