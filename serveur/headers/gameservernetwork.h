#ifndef GAMESERVERNETWORK_H
#define GAMESERVERNETWORK_H
#include <QtGui>
#include <QtNetwork>
#include "requete.h"
/**
 * \file gameservernetwork.h
 * \brief Classe répresentant un gameservernetwork
 * \author Franck.T
 */
class gameServerNetwork : public QObject
{
    Q_OBJECT
public:
    /*!
      *\brief Constructeur de la classe gameservernetwork
      */
    gameServerNetwork();
    /*!
      *\brief Fonction qui envoi a tous les clients un message
      */
    void envoyerATous(const QString &message);
    /*!
      *\brief Fonction qui envoi une requete a tous les clients
      */
    void envoyerATous(const Requete &req);
    /*!
      *\brief Fonction qui renvoi l'etat du serveur
      *\return QString
      */
    QString getEtatServer();
public slots:
    /*!
      *\brief Slot lorsqu'il y a un client qui se connecte
      */
    void nouvelleConnexion();
    /*!
      *\brief Slot lorsqu'il y a un donnée recu
      */
    void donneesRecues();
    /*!
      *\brief Slot lorsqu'il y a un clients qui se deconnecte
      */
    void deconnexionClient();

private:
    QLabel *etatServeur;                    /*!< QLabel qui représente l'état serveur*/
    QTcpServer *serveur;                    /*!< Identifiant du serveur*/
    QList<QTcpSocket *> clients;            /*!< Liste de QTCPSocket représentant les clients*/
    quint16 tailleMessage;                  /*!< Entier représentant la taille d'un message*/
signals:
    /*!
      *\brief Signal qui envoi une requete au gameservermanagment
      */
    void envoireq(Requete);
};

#endif // GAMESERVERNETWORK_H
