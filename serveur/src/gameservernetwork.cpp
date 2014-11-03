#include "gameservernetwork.h"



gameServerNetwork::gameServerNetwork()
{

    etatServeur = new QLabel;
    serveur = new QTcpServer(this);
    if (!serveur->listen(QHostAddress::Any, 50885))
    {
        etatServeur->setText("Le serveur n'a pas pu etre demarre.<br>Raison : " + serveur->errorString());
    }
    else
    {
        etatServeur->setText("Le serveur a ete demarre sur le port " + QString::number(serveur->serverPort())+ "<br>" + "Des clients peuvent maintenant se connecter.");
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }

    tailleMessage = 0;
}



void gameServerNetwork::nouvelleConnexion()
{
    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}



void gameServerNetwork::deconnexionClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0)
        return;

    clients.removeOne(socket);

    socket->deleteLater();
}



void gameServerNetwork::envoyerATous(const Requete &req)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << req;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->write(paquet);
    }

}



void gameServerNetwork::donneesRecues()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0)
        return;

    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;

    Requete req;
    in >> req;

    emit envoireq(req);

    tailleMessage = 0;
}



QString gameServerNetwork::getEtatServer()
{
    return etatServeur->text();
}
