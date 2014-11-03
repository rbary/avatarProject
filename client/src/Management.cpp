#include "Management.h"
#include <QtGui>
#include <QWheelEvent>
#include <QDebug>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////////////////////////////
Management::Management(QWidget *p_parent)
    :QGraphicsView(p_parent)
{
     connect(&clientnetwork, SIGNAL(envoiRequete(Requete)), this, SLOT(traitement(Requete)));
    _gameInitialized=false;
    QGraphicsScene * p_scene = new QGraphicsScene(this);
    int sceneRectSize =600;
    p_scene->setSceneRect(0,0,sceneRectSize,sceneRectSize);
    setScene(p_scene);
    setRenderHint(QPainter::Antialiasing, true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    id=-1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int Management::sceneSizeInPixels()
{
    QPoint corner1 = mapFromScene(0, 0);
    QPoint corner2 = mapFromScene(scene()->sceneRect().width(),0);
    return corner2.x() - corner1.x();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int Management::initSize()
{
    int desiredSize=600;
    float ratioSize =(float)desiredSize / sceneSizeInPixels();
    ratioSize = ((int)(ratioSize * 100)) / 100.0;
    scale(ratioSize, ratioSize);
    return sceneSizeInPixels();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::drawingMap(Map mapt)
{
    quint32 valAvatar=2;
    _map=mapt;
    quint32 valBlock=1;
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(_map.getValSig(i,j)==valBlock){
                scene()->addItem(new Block(i,j));
            }
        }
    }

    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
                if(_map.getValSig(i,j)==valAvatar){
                    _map.deleteElt(i,j);
                }
            }
     }
    setStyleSheet("background-color: black;");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::drawingAvatar(QMap<int, Avatar *> listtestt)
{
    quint32 valAvatar=2;

    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            for(int k=0; k<listtestt.size(); k++){
                if(_map.getValSig(i,j)==valAvatar){
                    scene()->addItem(listtestt.value(k));
                }
            }
        }
    }
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
                if(_map.getValSig(i,j)==valAvatar){
                    _map.deleteElt(i,j);
                }
            }
        }
    _gameInitialized=true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::wheelEvent(QWheelEvent *event){
    QString ent, mess;
    ent="ctosWheel";
    mess.setNum(id);
    if(_gameInitialized == true){
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        if(event->delta()>0){
            listtest.value(id)->pivoterAvatar(45);
            listAvatar.remove(id);
            listAvatar.insertMulti(id, listtest.value(id)->getz());
            listAvatar.insertMulti(id, listtest.value(id)->getx());
            listAvatar.insertMulti(id, listtest.value(id)->gety());
            clientnetwork.sendRequete(ent, mess, listAvatar, listBalle);
        }
        if(event->delta()<0){
            listtest.value(id)->pivoterAvatar(-45);
            listAvatar.remove(id);
            listAvatar.insertMulti(id, listtest.value(id)->getz());
            listAvatar.insertMulti(id, listtest.value(id)->getx());
            listAvatar.insertMulti(id, listtest.value(id)->gety());
            clientnetwork.sendRequete(ent, mess, listAvatar, listBalle);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::keyPressEvent(QKeyEvent *event){
    QString ent, mess;
    ent="ctosSpacePress";
    mess.setNum(id);
    if(_gameInitialized == true){
        if (event->key() == Qt::Key_Space){
            listtest.value(id)->avancerAvatar(_map);
            listAvatar.remove(id);
            listAvatar.insertMulti(id, listtest.value(id)->getz());
            listAvatar.insertMulti(id, listtest.value(id)->getx());
            listAvatar.insertMulti(id, listtest.value(id)->gety());
            clientnetwork.sendRequete(ent, mess, listAvatar, listBalle);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::mousePressEvent(QMouseEvent *event){
    QString ent, mess;
    ent="ctosClick";
    mess.setNum(id);
    if(_gameInitialized == true){
        if(event->button()== Qt::LeftButton){
            Bullet * bullet = new Bullet(listtest.value(id)->getx(),listtest.value(id)->gety());
            scene()->addItem(bullet);
            bullet->rotateBullet(listtest.value(id)->rotation());
            listBalle.remove(id);
            listBalle.insertMulti(id, bullet->getx());
            listBalle.insertMulti(id, bullet->gety());
            clientnetwork.sendRequete(ent, mess, listAvatar, listBalle);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Management::traitement(Requete req)
{
    if(req.getEntete()=="stocConnection" && id==-1)
    {
        for(int i=0; i<30; i++){
            for(int j=0; j<30; j++){
                tab[i][j]=req.tab[i][j];
            }
        }
        id=req.getMessage().toInt();
        clientnetwork.id=id;
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;

        _map.setTable(tab);
        drawingMap(_map);

        for(int a=0; a<listAvatar.size(); a++){
            if(listAvatar.contains(a)){
            QList<int> values = listAvatar.values(a);
                listtest.insert(a, new Avatar(values.at(1), values.at(0), values.at(2)));
                _map.insererEltSig(2,values.at(1), values.at(0));
            }
        }
        drawingAvatar(listtest);

    }else if(req.getEntete()=="stocConnection" && id>-1)
    {
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;

        for(int a=0; a<listAvatar.size(); a++){
            if(listAvatar.contains(a)){
            QList<int> values = listAvatar.values(a);
                if(listtest.contains(a)==false){
                    listtest.insert(a, new Avatar(values.at(1), values.at(0), values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }
            }
        }
        drawingAvatar(listtest);

    }else if(req.getEntete()=="stocSpacePress")
    {
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;

        for(int a=0; a<listAvatar.size(); a++){
            if(listAvatar.contains(a)){
            QList<int> values = listAvatar.values(a);
                if(listtest.contains(a)==false){
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }else if(listtest.contains(a)== true && req.getMessage().toInt()!=id){
                    scene()->removeItem(listtest.value(a));
                    listtest.remove(a);
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }
            }
        }
        drawingAvatar(listtest);


    }else if(req.getEntete()=="stocDeco" && req.listAvatar.contains(id)==false)
    {
        clientnetwork.id=-1;
        clientnetwork.close();
        clientnetwork.socket->abort();
    }else if(req.getEntete()=="stocDeco" && req.listAvatar.contains(id)==true)
    {
        qDebug()<<"stocDeco";
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;
    }else if(req.getEntete()=="stocWheel")
    {
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;

        for(int a=0; a<listAvatar.size(); a++){
            if(listAvatar.contains(a)){
            QList<int> values = listAvatar.values(a);
                if(listtest.contains(a)==false){
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }else if(listtest.contains(a)== true && req.getMessage().toInt()!=id){
                    scene()->removeItem(listtest.value(a));
                    listtest.remove(a);
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }
            }
        }
        drawingAvatar(listtest);
    }else if(req.getEntete()=="stocClick")
    {
        listAvatar=req.listAvatar;
        listBalle=req.listBalle;

        for(int a=0; a<listAvatar.size(); a++){
            if(listAvatar.contains(a)){
            QList<int> values = listAvatar.values(a);
                if(listtest.contains(a)==false){
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }else if(listtest.contains(a)== true && req.getMessage().toInt()!=id){
                    scene()->removeItem(listtest.value(a));
                    listtest.remove(a);
                    listtest.insert(a, new Avatar(values.at(1), values.at(0),values.at(2)));
                    _map.insererEltSig(2,values.at(1), values.at(0));
                }
            }
        }
        drawingAvatar(listtest);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
