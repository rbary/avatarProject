/**
 * \file Bullet.h
 * \brief Classe répresentant une balle
 * \author Roland.B
 */
#ifndef BULLET_H
#define BULLET_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <iostream>
#define BULLET_SIZE 20
#define TIMER_STARTING 50

using namespace std;

class Bullet:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum BulletDirection {Up,Down,Left, Right,UpLeft,UpRight,DownLeft,DownRight};
    /*!
      *\brief Constructeur de la classe Bullet
      */
    Bullet(int x,int y);
    /*!
      *\brief Geter qui retourne la valeur de _x
      *\return _x
      */
    int getx();
    /*!
      *\brief Geter qui retourne la valeur de _y
      *\return _x
      */
    int gety();
    /*!
      *\brief Geter qui retourne la valeur de _bulletDirection
      *\return _bulletDirection
      */
    BulletDirection getBulletDirection();
    /*!
      *\brief Geter qui retourne la valeur de _toDelete
      *\return _toDelete
      */
    bool getDeleteStatus();
    /*!
      *\brief Fonction qui met à jour la direction de la balle
      *\return void
      */
    void updateBulletDirection();
    /*!
      *\brief Fonction qui effectue une rotation d'un certains angle de la balle
      *\param int
      *\return void
      */
    void rotateBullet(int degree);
private:
    int _x,_y;                                                 /*!< Coordonnées de la balle*/
    bool _toDelete;                                            /*!< Status de suppression de la balle*/
    QPixmap _bulletImg;                                        /*!< Image de la balle*/
    int _bulletAngle;                                          /*!< Angle de rotation de la balle*/
    BulletDirection _bulletDirection;                          /*!< Direction de la balle*/
    QTimer * _bulletTimer;                                     /*!< Timer de la balle*/
protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    QRectF boundingRect() const;
public slots:
    /*!
      *\brief Slot qui effectue un avancement d'une case dans la map de la balle
      *\retun void
      */
    void bulletTrigger();
};
#endif // BULLET_H
