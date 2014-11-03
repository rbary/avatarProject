#ifndef MANAGEMENT_H
#define MANAGEMENT_H
/*!
 * \file Management.h
 * \brief Classe permettant la gestion du jeu
 * \author Roland.B
 */

#include <QApplication>
#include <QGraphicsView>
#include <QMouseEvent>
#include "ClientNetwork.h"
#include "Map.h"
#include "Block.h"
#include "Avatar.h"
#include "Bullet.h"
#include <QTimer>

class Management:public QGraphicsView
{
    Q_OBJECT
public:
    /*!
      *\brief Constructeur de la classe Management
      */
    Management(QWidget * p_parent = 0);
    /*!
      *\brief Fonction qui initialise la taille du QGraphicsView associé au management
      *\return int
      */
    int initSize();
    /*!
      *\brief Fonction qui réalise le rendu graphique de la carte
      *\return void
    */
    void drawingMap(Map mapt);
    /*!
      *\brief Fonction qui réalise le rendu graphique de tous les avatars présents sur la carte
      *\param QMap<int, Avatar *>
      *\return void
      */
    void drawingAvatar(QMap<int, Avatar *> listtestt);
    ClientNetwork clientnetwork;                                                  /*! Attribut de type ClientNetwork*/
public slots:
    /*!
      *\brief Slot de traitement d'une requete
      */
    void traitement(Requete req);
protected:
     /*!
       *\brief Evenement déclenché par la mollete de la souris
       *\return void
       */
    void wheelEvent(QWheelEvent *event);
    /*!
      *\brief Evenement déclenché suite à la pression d'une touche du clavier
      *\return void
      */
    void keyPressEvent(QKeyEvent *event);
    /*!
      *\brief Evenement déclenché par un click de la souris
      *\return void
      */
    void mousePressEvent(QMouseEvent *event);
private:
    Map _map;                                                                     /*!< Une map par defaut*/
    int sceneSizeInPixels();                                                      /*!< Retourne la dimension de la scene en px*/                                                         /*!< Un objet de type avatar*/
    bool _gameInitialized;                                                        /*!< Statut d'initalisation du jeu*/
    QMap<int, int> listBalle;                                                     /*!< Une liste de balles*/
    QMap<int, int> listAvatar;                                                    /*!< Une liste d'avatars*/
    QMap<int , Avatar *> listtest;                                                /*!< Une liste d'avatar temporelle*/
    quint32 tab[30][30];                                                          /*!< Un tableau 2D de quint32*/
    int id;                                                                       /*!< Un id pour le joueur*/
};
#endif // MANAGEMENT_H
