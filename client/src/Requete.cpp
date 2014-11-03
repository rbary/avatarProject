#include "Requete.h"

Requete::Requete()
{
}

Requete::Requete(const QString ent, const QString mess):entete(ent),message(mess)
{
}

Requete::Requete(const QString ent, const QString mess, quint32 tabt[30][30]):entete(ent),message(mess)
{
    for(int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            tab[i][j]=tabt[i][j];
        }
    }
}

Requete::Requete(const QString ent, const QString mess, QMap<int, int> listeAvatart, QMap<int, int> listeBallet):entete(ent),message(mess)
{
    listAvatar=listeAvatart;
    listBalle=listeBallet;
}



Requete::Requete(const QString ent, const QString mess, quint32 tabt[30][30], QMap<int, int> listeAvatart, QMap<int, int> listeBallet):entete(ent),message(mess)
{
    for(int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            tab[i][j]=tabt[i][j];
        }
    }

    listAvatar=listeAvatart;
    listBalle=listeBallet;
}



Requete::~Requete()
{

}

void Requete::setListeA(const QMap<int, int> listT)
{
    listAvatar=listT;
}

void Requete::setListeB(const QMap<int, int> listT)
{
    listBalle=listT;
}

void Requete::setMessage(QString mess)
{
    message=mess;
}

void Requete::setEntete(QString ent)
{
    entete=ent;
}

void Requete::afficher()
{
    qDebug() <<"Entete = " << this->entete << "Message = " << this->message;
    for(int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            qDebug() << this->tab[i][j];
        }
    }
    qDebug() << this->listAvatar;
    qDebug() << this->listBalle;
}

void Requete::softaffiche()
{
   qDebug() <<"Entete = " << this->entete << "Message = " << this->message;
   qDebug() << this->listAvatar;
   qDebug() << this->listBalle;
}

QString Requete::getEntete()
{
    return entete;
}

QString Requete::getMessage()
{
    return message;
}

QDataStream & operator << (QDataStream & out, const Requete & req)
{
    out << req.entete << req.message;
    for(int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            out << req.tab[i][j];
        }
    }
    out << req.listAvatar;
    out << req.listBalle;
    return out;
}

QDataStream & operator >> (QDataStream & in, Requete & req)
{
    in >>req.entete;
    in >>req.message;
    for(int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            in >> req.tab[i][j];
        }
    }
    in >> req.listAvatar;
    in >> req.listBalle;
    return in;
}

void Requete::init()
{
        qRegisterMetaTypeStreamOperators<Requete>("Requete");
        qMetaTypeId<Requete>();
}
