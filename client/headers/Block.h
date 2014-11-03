#ifndef BLOCK_H
#define BLOCK_H
/*!
 * \file Block.h
 * \brief Classe répresentant un Block
 * \author Roland.B
 */
#include <QPainter>
#include <QGraphicsItem>
#define BLOCK_SIZE 20

class Block: public QGraphicsItem
{
private:
    int _x,_y;                      /*!<Coordonnées d'un block*/
    QPixmap _blockImg;              /*!<Image d'un block*/
public:
    /*!
      *\brief Constructeur de la classe block
      */
    Block(int x,int y,QGraphicsItem * parent=0);
protected:
    void paint(QPainter *p_painter, const QStyleOptionGraphicsItem *p_option,
               QWidget *p_widget);
    QRectF boundingRect() const;
};
#endif //BLOCK_H
