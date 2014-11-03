#ifndef REQUETE_H
#define REQUETE_H

#include <QString>
#include <QDebug>
#include <QVariant>
#include <QMap>
/**
 * \file Requete.h
 * \brief Classe répresentant une requete
 * \author Franck.T
 */
class Requete
{
public:
    /*!
      *\brief Constructeur de la classe Requete
      */
    Requete();
    /*!
      *\brief Constructeur de la classe Requete
      *\param QString,QString,quint32[][],QMap<int,int>,QMap<int,int>
      */
    Requete(const QString ent, const QString mess, quint32 tabt[30][30], QMap<int, int> listeAvatart, QMap<int, int> listBallet);
    /*!
      *\brief Constructeur de la classe Requete
      *\param QString,QString,QMap<int,int>,QMap<int,int>
      */
    Requete(const QString ent, const QString mess, QMap<int, int> listeAvatart, QMap<int, int> listBallet);
    /*!
      *\brief Constructeur de la classe Requete
      *\param QString,QString,quint32[][]
      */
    Requete(const QString ent, const QString mess, quint32 tabt[30][30]);
    /*!
      *\brief Constructeur de la classe Requete
      *\param QString,QString
      */
    Requete(const QString ent, const QString mess);
    /*!
      *\brief Destructeur de la classe Requete
      */
    ~Requete();
    /*!
      *\brief Fonction d'affichage d'une requete
      */
    void afficher();
    /*!
      *\brief Fonction d'affichage léger d'une requete
      */
    void softaffiche();
    /*!
      *\brief Initialisation d'une requete
      */
    void init();
    /*!
      *\brief Geter qui retourne l'entete
      *\return QString
      */
    QString getEntete();
    /*!
      *\brief Seter de l'entete
      *\param QString
      */
    void setEntete(QString ent);
    /*!
      *\brief Geter qui retourne le message
      *\return QString
      */
    QString getMessage();
    /*!
      *\brief Seter de du message
      *\param QString
      */
    void setMessage(QString mess);
    /*!
      *\brief Seter de la liste d'avatar
      *\param QMap<int,int>
      */
    void setListeA(const QMap<int, int>);
    /*!
      *\brief Seter de la liste de balle
      *\param QMap<int,int>
      */
    void setListeB(const QMap<int, int>);
    QMap<int, int> listBalle;                       /*!< Liste des coordonées d'une balle (id ,x) (id, y) (id ,z)*/
    QMap<int, int> listAvatar;                      /*!< Liste des coordonées d'un avatar (id ,x) (id, y) (id ,z)*/
    quint32 tab[30][30];                            /*!< Tableau deux dimensions représentant la carte*/
private:
    QString entete;                                 /*!< Identifiant representant l'entete*/
    QString message;                                /*!< identifiant representant le message*/
    friend QDataStream & operator << (QDataStream &, const Requete &);  /*!< Surcharge d'opérateur <<*/
    friend QDataStream & operator >> (QDataStream &, Requete &);        /*!< Surcharge d'opérateur >>*/

};

Q_DECLARE_METATYPE(Requete)
QDataStream & operator << (QDataStream & out, const Requete & req);
QDataStream & operator >> (QDataStream & in, Requete & req);


#endif // REQUETE_H
