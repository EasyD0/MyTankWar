#include "mapseg.h"
#include "Gamesetting.h"
#include <QImage>
#include <QPainter>
#include <qsize.h>

void Mapseg::init_kind(MapBlock kind) {
  switch (kind) {
  case nothing:
    _life = 0;
    _penetration = 0;
    _pass = true;
    _disappear = true;
    break;

  case wall:
    _life = 1;
    _penetration = 1;
    _pass = false;
    break;
    
  case steel:
    _life = 2; // 钢铁生命值为2
    _penetration = 2; //2级导弹可破坏
    _pass = false;
    break;
    
  case sand:
    break;
  case water:
    _life = INT_MAX;
    _penetration = 0; // 可直接穿透
    _pass = false;
    break;

  case grass:
    _life = INT_MAX;
    _penetration = 0; // 可直接穿透
    _pass = true;
    break;

  case boss:
    _life = 2;
    _penetration = 1; // 1级导弹可破坏
    _pass = false;
    break;
    
  default:
    break;
  };
}

Mapseg::Mapseg(const QPoint &pos, MapBlock segkind)
    : Baseblock(), _seg_kind(segkind) {

  // 初始化位置和几何形状 
  _position = pos;
  _geo.setRect(pos.x(), pos.y(), SegWidth, SegHeight);

  // 初始化地块属性
  init_kind(segkind);
}

void Mapseg::display(QPainter &_painter) const{
  if (_disappear)
    return;
  
  QImage img;

  switch (_seg_kind) {
  case nothing:
    return;
	break;
  case wall:
    img.load(":/mapseg/png/mapseg/wall.png");
    break;
  case steel:
    img.load(":/mapseg/png/mapseg/steel.png");
    break;
  case sand:
    img.load(":/mapseg/png/mapseg/sand.png");
    break;
  case water:
    img.load(":/mapseg/png/mapseg/water.png");
    break;
  case grass:
    img.load(":/mapseg/png/mapseg/grass.png");
    break;
  case boss:
    img.load(":/mapseg/png/mapseg/boss.png");
    break;
  default:
	break;
  };
  _painter.drawImage(_geo, img);
}

void Mapseg::update_seg() {  
  if (_life == 0) { //error
	_seg_kind = nothing;
	_disappear = true;
  }

  if (_disappear) {
    init_kind(nothing);
  }
}