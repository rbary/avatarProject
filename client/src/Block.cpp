#include "Block.h"
#include <QPainter>

Block::Block(int x, int y, QGraphicsItem *parent):QGraphicsItem(parent)
{
    _x=x;
    _y=y;
    setPos(_x * BLOCK_SIZE,_y * BLOCK_SIZE);
    _blockImg.load("data/block2.png");
}

void Block::paint(QPainter *p_painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    p_painter->drawPixmap(0,0,BLOCK_SIZE,BLOCK_SIZE,_blockImg);
}

QRectF Block::boundingRect() const
{
       return QRectF(0,0,BLOCK_SIZE,BLOCK_SIZE);
}
