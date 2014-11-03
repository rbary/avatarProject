#ifndef LAUNCHER_H
#define LAUNCHER_H
/*!
 * \file Management.h
 * \brief Classe de lancement du jeu
 * \author Roland.B
 */
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsView>
#include "Requete.h"
#include "Management.h"
#include "ClientNetwork.h"
#include <iostream>

using namespace std;

class Launcher:public QMainWindow
{
	Q_OBJECT
public:
    /*!
      *\brief Constructeur de la classe Launcher
      */
    Launcher();
private slots:
    /*!
      *\brief Slot de connection au serveur
      *\return void
      */
    void slot_seConnecterServeur();
    /*!
      *\brief Fonction permettant de fixer la taille de la fenetre
      *\return void
      */
    void setFixedSquareSize(int size);
private:
    Management *p_management;                               /*!< Pointeur vers un objet de type Management*/
    int id;                                                 /*!< Id d'initalisation*/
};
#endif //LAUNCHER_H
