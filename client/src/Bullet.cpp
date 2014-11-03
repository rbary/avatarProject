#include "Bullet.h"
/////////////////////////////////////////////////////////////////////////////////////////////
Bullet::Bullet(int x, int y)
{
    _x=x;
    _y=y;
    setPos(_x * BULLET_SIZE, _y * BULLET_SIZE);
	_bulletImg.load("data/bullet.png");
	_toDelete=false;
	_bulletDirection=Up;
    this->setTransformOriginPoint(BULLET_SIZE/2,BULLET_SIZE/2);
    _bulletTimer = new QTimer();
    QObject::connect(_bulletTimer, SIGNAL(timeout()),this,SLOT(bulletTrigger()));
    _bulletTimer->start(100);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool Bullet::getDeleteStatus()
{
	return _toDelete;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::updateBulletDirection()
{
    if(_bulletAngle == 0 || _bulletAngle == 360){
        _bulletDirection=Up;
    }

    if(_bulletAngle == 45 || _bulletAngle == 405){
        _bulletDirection=UpRight;
    }

    if(_bulletAngle == 90){
        _bulletDirection=Right;
    }

    if(_bulletAngle == 135){
        _bulletDirection=DownRight;
    }

    if(_bulletAngle == 180){
        _bulletDirection=Down;
    }

    if(_bulletAngle == 225){
        _bulletDirection=DownLeft;
    }

    if(_bulletAngle == 270){
        _bulletDirection=Left;
    }

    if(_bulletAngle == 315){
        _bulletDirection=UpLeft;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Bullet::getx()
{
    return _x;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Bullet::gety()
{
    return _y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->drawPixmap(0,0,BULLET_SIZE,BULLET_SIZE,_bulletImg);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
QRectF Bullet::boundingRect()const
{
	return QRectF(0,0,BULLET_SIZE,BULLET_SIZE);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bullet::rotateBullet(int degree)
{
	_bulletAngle=this->rotation() + degree;
    this->setRotation(_bulletAngle);
    this->updateBulletDirection(); /*Mise a jour de la direction de la balle*/

    if(this->rotation() >= 360){
        this->setRotation(this->rotation() - 360);
        }
    if(this->rotation() <= 0){
        this->setRotation(this->rotation() + 360);
        }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Bullet::BulletDirection Bullet::getBulletDirection(){
    return _bulletDirection;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void Bullet::bulletTrigger(){
    switch(this->getBulletDirection()){
    case Up:
        _y--;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case UpRight:
        _y--;
        _x++;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case Right:
        _x++;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case DownRight:
        _y++;
        _x++;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case Down:
        _y++;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case DownLeft:
        _y++;
        _x--;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case Left:
        _x--;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    case UpLeft:
        _y--;
        _x--;
        setPos(_x*BULLET_SIZE,_y*BULLET_SIZE);
        break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

