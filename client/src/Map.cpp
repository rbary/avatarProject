#include "Map.h"
#include <QDebug>
Map::Map(){
}

Map::Map(quint32 tab[30][30]){

    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            _tab[i][j]=tab[i][j];
        }
    }
}

quint32 Map::getValSig(int x, int y){
    return _tab[x][y];
}

void Map::insererEltSig(quint32 elt, int x, int y){
    if(getValSig(x,y)==0){
        _tab[x][y]=elt;
    }
}

void Map::deleteElt(int x, int y){
    if(_tab[x][y] == 0){
        qDebug()<<"*** Nothing to delete ***";
    }
    _tab[x][y]=0;
}

void Map::setTable(quint32 tab[30][30]){
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            _tab[i][j]=tab[i][j];
        }
    }
}


