#include "ClientNetwork.h"

ClientNetwork::ClientNetwork(QWidget *p_parent):QDialog(p_parent){
    setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(donneesRecues()));
    connect(socket,SIGNAL(connected()), this,SLOT(connecte()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(deconnecte()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(erreurSocket(QAbstractSocket::SocketError)));
    tailleMessage=0;
    id=-1;
}







void ClientNetwork::on_boutonConnexion_clicked(){
     // On annonce sur la fenêtre qu'on est en train de se connecter
    messageList->append(tr("<em>Tentative de connexion en cours...</em>"));
    boutonConnexion->setEnabled(false);

    socket->abort(); // On désactive les connexions précédentes s'il y en a
    socket->connectToHost(serveurIP->text(), serveurPort->value());
    // On se connecte au serveur demandé
}







void ClientNetwork::on_boutonDeconnexion_clicked(){
    messageList->append(tr("<em>Deconnexion</em>"));
    boutonConnexion->setEnabled(false);

    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    QString ent,mess;
    ent ="ctosDeco";
    mess.setNum(id);
    qDebug() << id;
    Requete req(ent, mess);


    out << (quint16) 0;
    out << req;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);
}





void ClientNetwork::on_boutonFermer_clicked(){
    boutonFermer->setEnabled(false);
    this->close();
}







void ClientNetwork::connecte(){
    messageList->append(tr("<em>Connexion russie !</em>"));
    boutonConnexion->setEnabled(true);

    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    QString ent,mess;
    ent ="ctosConnection";
    mess.setNum(id);
    Requete req(ent, mess);


    out << (quint16) 0;
    out << req;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);
}







void ClientNetwork::donneesRecues(){
    QDataStream in(socket);

    if (tailleMessage == 0)
    {

        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;
    // Si on arrive jusqu' cette ligne, on peut recuprer le message entier
    Requete req;
    in >> req;

    emit envoiRequete(req);

    // On remet la taille du message  0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}




void ClientNetwork::sendRequete(QString ent, QString mess, QMap<int,int> listAv, QMap<int, int> listBa)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    Requete req(ent, mess, listAv, listBa);

    out << (quint16) 0;
    out << req;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);
}





///////////////////////////////////////////////////////////////////////////////////////////////////
void ClientNetwork::deconnecte(){
    messageList->append(tr("<em>Déconnecté du serveur</em>"));
    this->close();
}










///////////////////////////////////////////////////////////////////////////////////////////////////
void ClientNetwork::erreurSocket(QAbstractSocket::SocketError erreur){
    switch(erreur){
        case QAbstractSocket::HostNotFoundError:
            messageList->append(tr("<em>Erreur : Le serveur n'a pas pu être trouvé.Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            messageList->append(tr("<em>Erreur : Le serveur a réfusé la connexion.Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            messageList->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            messageList->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}





void ClientNetwork::setId(int idt){
    id=idt;
}

