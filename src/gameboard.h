#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>

using std::shared_ptr;
using std::make_shared;

class GameBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    GameBoard(QQuickItem * parent = nullptr);
    void paint(QPainter *) override;

private:
};

#endif // GAMEBOARD_H
