#ifndef GAMESERVERMANAGMENT_H
#define GAMESERVERMANAGMENT_H
#include "gameservernetwork.h"
#include "requete.h"
#include <QDebug>
#include <QTimer>
/**
 * \file gameservermanagment.h
 * \brief Classe répresentant un gameservermanagment
 * \author Franck.T
 */
class gameServerManagment: public QObject
{
    Q_OBJECT
public:
    /*!
      *\brief Constructeur de la classe gameservermanagment
      */
    gameServerManagment();
    /*!
      *\brief Fonction qui renvoi l'etat du serveur
      *\return QString
      */
    QString getEtatServer();
private:
    gameServerNetwork network;              /*!< Identifiant d'un gameservernetwork*/
    quint32 tab[30][30];                    /*!< Tableau deux dimensions représentant la carte*/
    QMap<int, int> listAvatar;              /*!< Liste des coordonées d'un avatar (id ,x) (id, y) (id ,z)*/
    QMap<int, int> listBalle;               /*!< Liste des coordonées d'une balle (id ,x) (id, y) (id ,z)*/
    int compteur;                           /*!< Entier qui represente l'id d'un client*/
public slots:
    void traitement(Requete req);
};

#endif // GAMESERVERMANAGMENT_H
