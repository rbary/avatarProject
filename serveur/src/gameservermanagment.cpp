#include "gameservermanagment.h"

gameServerManagment::gameServerManagment()
{
    connect(&network, SIGNAL(envoireq(Requete)), this, SLOT(traitement(Requete)));
    compteur=0;

    for(int i=0; i<30; i++){
        for(int j=0; j<30; j++){
            if(i==0 || j==0 ||i==29 || j==29){
                tab[i][j]=1;
            }else{
                tab[i][j]=0;
            }
        }
    }
}

QString gameServerManagment::getEtatServer()
{
    return network.getEtatServer();
}

void gameServerManagment::traitement(Requete req)
{
    req.softaffiche();
    if(req.getEntete()=="ctosConnection")
    {
        QString mess;
        mess.setNum(compteur);
        QString ent;
        ent="stocConnection";

        listAvatar.insertMulti(compteur,3);
        listAvatar.insertMulti(compteur,1);
        listAvatar.insertMulti(compteur,1);

        Requete reponse(ent, mess, tab, listAvatar, listBalle);
        compteur=compteur+1;

        network.envoyerATous(reponse);

    }else if(req.getEntete()=="ctosDeco")
    {
        QString test;
        test=req.getMessage();
        int id;
        id=test.toInt();

        QString ent;
        ent="stocDeco";
        QString mess;
        mess=test;

        listAvatar.remove(id);
        listBalle.remove(id);

        Requete reponse(ent, mess, listAvatar, listBalle);

        network.envoyerATous(reponse);
    }else if(req.getEntete()=="ctosSpacePress")
    {
        QString ent,mess;
        ent="stocSpacePress";
        mess.setNum(req.getMessage().toInt());

        listAvatar=req.listAvatar;
        listBalle=req.listBalle;


        Requete reponse(ent, mess, listAvatar, listBalle);
        network.envoyerATous(reponse);
    }else if(req.getEntete()=="ctosWheel")
    {
        QString ent,mess;
        ent="stocWheel";
        mess.setNum(req.getMessage().toInt());

        listAvatar=req.listAvatar;
        listBalle=req.listBalle;


        Requete reponse(ent, mess, listAvatar, listBalle);
        network.envoyerATous(reponse);
    }else if(req.getEntete()=="ctosClick")
    {
        QString ent,mess;
        ent="stocClick";
        mess.setNum(req.getMessage().toInt());

        listAvatar=req.listAvatar;
        listBalle=req.listBalle;
    }

}


