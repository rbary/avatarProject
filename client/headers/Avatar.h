#ifndef AVATAR_H
#define AVATAR_H
/*!
 * \file Avatar.h
 * \brief Classe répresentant un Avatar
 * \author Roland.B
 */
#include <QPainter>
#include <QGraphicsItem>
#include <iostream>
#include "Map.h"
#include <QDebug>
#define AVATAR_SIZE 20
#define ANGLE_ROTATION 45

using namespace std;
class Avatar:public QGraphicsItem
{
public:
    enum AvatarDirection {Up,Down,Left, Right,UpLeft,UpRight,DownLeft,DownRight};
    /*!
      *\brief Constructeur de la classe Avatar
      */
    Avatar(int x, int y, int z, QGraphicsItem *parent=0);
    /*!
      *\brief Geter qui retourne la valeur de _x
      *\return _x
      */
    int getx();
    /*!
      *\brief Geter qui retourne la valeur de  _y
      *\return _y
      */
    int gety();
    /*!
      *\brief Geter qui retourne la valeur de _z
      *\return _z
      */
    int getz();
    /*!
      *\brief Geter qui retourne la valeur de _toDelete
      *\return _toDelete
      */
    bool getDeleteStatus();
    /*!
      *\brief Fonction qui met à jour la direction de l'avatar
      *\return void
      */
    void updateDirection();
    /*!
      *\brief Geter qui retourne la valeur de _avatarDirection
      *\return _avatartDirection
      */
    AvatarDirection getDirectionAvatar();
    /*!
      *\brief Fonction qui effectue une rotation d'un certains angle de l'avatar
      *\param int
      *\return void
      */
    void pivoterAvatar(int degre);
    /*!
      *\brief Fonction qui effectue un deplacement d'une case dans la map
      *\param Map
      *\return void
      */
    void avancerAvatar(Map map);
    /*!
      *\brief Fonction qui indique l'evitement d'une collision
      *\param Map,AvatarDirection
      *\return true si on evite un collision,false sinon
      */
    bool avoidColliding(Map map,AvatarDirection direction);
private:
    int _x,_y;                                                      /*!< Coordonnées de l'avatar*/
    int _z;                                                         /*!< Valeur numérique de la direction de l'avatar*/
    int _avatarId;                                                  /*!< Identifiant d'un avatar*/
    AvatarDirection _avatarDirection;                               /*!< Direction d'un avatar*/
    int _avatarAngle;                                               /*!< Angle d'un avatar*/
    QPixmap _avatarImg;                                             /*!< Image d'un avatar*/
    bool _toDelete;                                                 /*!< Statut de suppression d'un avatar*/
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *p_option,
               QWidget *p_widget);
    QRectF boundingRect() const;
};
#endif //AVATAR_H
