#include "Avatar.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Avatar::Avatar(int x, int y, int z, QGraphicsItem *parent):QGraphicsItem(parent)
{
    _x=x;
    _y=y;
    _z=z;
    setPos(_x * AVATAR_SIZE,_y * AVATAR_SIZE);
    _toDelete=false;
    this->setTransformOriginPoint(AVATAR_SIZE/2,AVATAR_SIZE/2);
    switch(z){
    case 0: /*Correspond a la direction Up*/
        _avatarAngle=0;
        _avatarDirection=Up;
        _avatarImg.load("data/avatar8.png");
        break;
    case 1:
        _avatarAngle=45;
        _avatarDirection=UpRight;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(45);
        break;
    case 2:
        _avatarAngle=90;
        _avatarDirection=Right;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(90);
        break;
    case 3:
        _avatarAngle=135;
        _avatarDirection=DownRight;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(135);
        break;
    case 4:
        _avatarAngle=180;
        _avatarDirection=Down;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(180);
        break;
    case 5:
        _avatarAngle=225;
        _avatarDirection=DownLeft;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(225);
        break;
    case 6:
        _avatarAngle=270;
        _avatarDirection=Left;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(270);
        break;
    case 7:
        _avatarAngle=315;
        _avatarDirection=UpLeft;
        _avatarImg.load("data/avatar8.png");
        this->pivoterAvatar(315);
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
bool Avatar::getDeleteStatus()
{
    return _toDelete;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Avatar::updateDirection()
{
    if(_avatarAngle == 0 || _avatarAngle == 360){
        _avatarDirection=Up;
        _z=0;
    }

    if(_avatarAngle == 45 || _avatarAngle == 405){
        _avatarDirection=UpRight;
        _z=1;
    }

    if(_avatarAngle == 90){
        _avatarDirection=Right;
         _z=2;
    }

    if(_avatarAngle == 135){
        _avatarDirection=DownRight;
         _z=3;
    }

    if(_avatarAngle == 180){
        _avatarDirection=Down;
         _z=4;
    }

    if(_avatarAngle == 225){
        _avatarDirection=DownLeft;
         _z=5;
    }

    if(_avatarAngle == 270){
        _avatarDirection=Left;
         _z=6;
    }

    if(_avatarAngle == 315){
        _avatarDirection=UpLeft;
         _z=7;
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
Avatar::AvatarDirection Avatar::getDirectionAvatar(){
    return _avatarDirection;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void Avatar::avancerAvatar(Map map)
{

    quint32 valFree=0;
    int holdx=this->getx();
    int holdy=this->gety();
    qDebug()<<holdx<<holdy;

    if(this->getDirectionAvatar()== Avatar::Up && avoidColliding(map,this->getDirectionAvatar())==true){
         _y--;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::UpRight && avoidColliding(map,this->getDirectionAvatar())==true){
         _y--;
         _x++;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::Right && avoidColliding(map,this->getDirectionAvatar())==true){
         _x++;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::DownRight && avoidColliding(map,this->getDirectionAvatar())==true){
         _y++;
         _x++;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar() == Avatar::Down && avoidColliding(map,this->getDirectionAvatar())==true){
         _y++;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::DownLeft && avoidColliding(map,this->getDirectionAvatar())==true){
         _y++;
         _x--;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::Left && avoidColliding(map,this->getDirectionAvatar())==true){
         _x--;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }

     if(this->getDirectionAvatar()== Avatar::UpLeft && avoidColliding(map,this->getDirectionAvatar())==true){
         _y--;
         _x--;
         setPos(_x*AVATAR_SIZE,_y*AVATAR_SIZE);
         map.insererEltSig(valFree,holdx,holdy);
     }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Avatar::pivoterAvatar(int degre){

    _avatarAngle=this->rotation() + degre;
    this->setRotation(_avatarAngle);
    this->updateDirection(); /*Mise a jour de la direction de l'avatar*/

    if(this->rotation() >= 360){
        this->setRotation(this->rotation() - 360);
        }
    if(this->rotation() <= 0){
        this->setRotation(this->rotation() + 360);
        }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Avatar::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,AVATAR_SIZE,AVATAR_SIZE,_avatarImg);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
QRectF Avatar::boundingRect() const
{
   return QRectF(0,0,AVATAR_SIZE,AVATAR_SIZE);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Avatar::getx(){
    return _x;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Avatar::gety(){
    return _y;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int Avatar::getz()
{
    return _z;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool Avatar::avoidColliding(Map map, AvatarDirection direction){
    quint32 valFree=0;
    int x=this->getx();
    int y=this->gety();

    if(direction == Up){
        if(map.getValSig(x,y-1) == valFree)
        {
            return true;
        }else{
            return false;
        }
    }

    if(direction == UpRight){
        if(map.getValSig(x+1,y-1) == valFree)
            return true;
        else
            return false;
    }

    if(direction == Right){
        if(map.getValSig(x+1,y) == valFree)
            return true;
        else
            return false;
    }

    if(direction == DownRight){
        if(map.getValSig(x+1,y+1)==valFree)
            return true;
        else
            return false;
    }

    if(direction == Down){
        if(map.getValSig(x,y+1)==valFree)
            return true;
        else
            return false;
    }

    if(direction == DownLeft){
        if(map.getValSig(x-1,y+1)==valFree)
            return true;
        else
            return false;
    }

    if(direction ==Left){
        if(map.getValSig(x-1,y)==valFree)
            return true;
        else
            return false;
    }

    if(direction == UpLeft){
        if(map.getValSig(x-1,y-1)==valFree)
            return true;
        else
            return false;
    }
    return true;
}


