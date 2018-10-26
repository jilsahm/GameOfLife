#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>

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

private:
    unique_ptr<QRgb> colorLifingCell;
    unique_ptr<QRgb> colorDeadCell;
};

#endif // GAMEBOARD_H
