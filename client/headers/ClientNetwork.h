#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H
/*!
 * \file ClientNetwork.h
 * \brief Classe de connection au serveur de jeu AvatarBattle2D
 * \author Roland.B,Franck.T
 */
#include <QtGui>
#include "Requete.h"
#include <QtNetwork>
#include "ui_connectWin.h"

class ClientNetwork:public QDialog, private Ui::connectWin
{
    Q_OBJECT

    public:
        /*!
          *\brief Constructeur de la classe ClientNetwork
          */
        ClientNetwork(QWidget *p_parent = 0);
        /*!
          *\brief Seter qui met à jour l'id du client
          *\param int
          *\return void
          */
        void setId(int idt);
        /*!
          *\brief Fonction qui réalise l'envoi d'une requete
          *\param QString,QString,QMap<int,int>,QMap<int,int>
          *\return void
          */
        void sendRequete(QString ent, QString mess, QMap<int, int> listAv, QMap<int, int> listBa);
        int id;                                                                             /*!< Identifiant du client*/
        QTcpSocket * socket;                                                                /*!< Pointeur vers une socket TCP*/
    private slots:
        /*!
          *\brief Slot déclenché quand on clique sur le bouton Connexion
          *\return void
          */
        void on_boutonConnexion_clicked();
        /*!
          *\brief Slot déclenché quand on clique sur le bouton Deconnexion
          *\return void
          */
        void on_boutonDeconnexion_clicked();
        /*!
          *\brief Slot déclenché quand on clique sur le bouton Fermer
          *\return void
          */
        void on_boutonFermer_clicked();
        /*!
          *\brief Slot déclenché quand la socket TCP est connectée
          *\return void
          */
        void connecte();
        /*!
          *\brief Slot déclenché quand la socket TCP est deconnectée
          *\return void
          */
        void deconnecte();
        /*!
          *\brief Slot déclenché quand une erreur se produit sur la socket
          *\return void
          */
        void erreurSocket(QAbstractSocket::SocketError erreur);
        /*!
          *\brief Slot déclenché quand on reçoit des données
          *\return void
          */
        void donneesRecues();

    signals:
        /*!
          *\brief Signal associé a l'envoi d'une requete
          *\return void
          */
        void envoiRequete(Requete req);
    private:
        quint16 tailleMessage;                                                 /*!< Taille d'un message donné*/
};
#endif //CLIENTNETWORK_H
