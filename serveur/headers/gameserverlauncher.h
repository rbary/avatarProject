#ifndef GAMESERVERLAUNCHER_H
#define GAMESERVERLAUNCHER_H
/**
 * \file gameserverlauncher.h
 * \brief Classe répresentant un gameserverlauncher
 * \author  Franck.T
 */
#include <QtGui>
#include "gameservermanagment.h"

class gameServerLauncher : public QWidget
{
    Q_OBJECT
public:
    /*!
      *\brief Constructeur de la classe gameServerLauncher
      */
    gameServerLauncher();
    /*!
      *\brief Fonction qui creer l'interface du serveur
      */
    void start();
    /*!
      *\brief Fonction qui ferme le serveur
      */
    void end();
private:
    gameServerManagment manag;/*!< Identifiant d'un management*/
    QLabel *etatServeur;/*!< Identifiant d'un etatServeur*/
    QPushButton *boutonQuitter;/*!< Identifiant d'un boutonQuitter*/
};

#endif // GAMESERVERLAUNCHER_H
