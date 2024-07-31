#include "tank.h"
#include "Game.h"
#include "check_collision.h"
#include "missile.h"
#include <QImage>
#include <QPoint>
#include <qicon.h>

extern Game Thegame;

extern const int SegWidth;
extern const int SegHeight;
extern const int player_x;
extern const int player_y;

Tank::Tank(TankType type, const QPoint &pos, Direction d)
    : Baseblock(), _tank_type(type) {
  _position = pos;
  _geo.setRect(pos.x(), pos.y(), SegWidth, SegHeight);

  _dir = d;
  switch (_tank_type) {
  case Player:
    _level = 1;
    _life = 1;
    _speed = 12;
    break;

  case Enemy1:
    _level = 1;
    _life = 1;
    _speed = 12;
    break;

  case Enemy2:
    _level = 1;
    _life = 1;
    _speed = 20;
    break;

  case Enemy3:
    _level = 1;
    _life = 2;
    _speed = 10;
    break;

  default:
    break;
  }
}

Tank::Tank(TankType type) : Tank(type, {0, 0}, Up) {
  if (type == Player) {
    _position = {player_x * SegWidth, player_y * SegHeight};
    _geo.setRect(_position.x(), _position.y(), SegWidth, SegHeight);
  }
}

void Tank::update_level(int l) {
  if (_tank_type == Player) // 只有玩家坦克可以升级/更变等级
    _level = l;
}

void Tank::display(QPainter &_painter) const {
  if (_disappear)
    return;

  std::string path = ":/png/tank/";
  if (_tank_type == Player) {
    path += "p1tank";
  } else {
    path += "enemy";
    path += std::to_string(_tank_type);
  };

  switch (_dir) {
  case Up:
    path += "U.png";
    break;
  case Right:
    path += "R.png";
    break;
  case Down:
    path += "D.png";
    break;
  case Left:
    path += "L.png";
    break;
  default:
    break;
  }

  QImage img(path.c_str());
  _painter.drawImage(_geo, img);
}

QRect Tank::move() {
  auto tmp = _geo;
  QRect new_geo = _geo;

  switch (_dir) {
  case Up:
    new_geo.moveTopLeft(_position + QPoint(0, -_speed));
    break;
  case Right:
    new_geo.moveTopLeft(_position + QPoint(_speed, 0));
    break;
  case Down:
    new_geo.moveTopLeft(_position + QPoint(0, _speed));
    break;
  case Left:
    new_geo.moveTopLeft(_position + QPoint(-_speed, 0));
    break;
  default:
    break;
  }

  if (check::checkall(new_geo, Thegame.Current_map, *Thegame.PlayerTank,
                      Thegame.CurrentEnemyList)) { // todo 检查是否碰撞
    _geo = new_geo;
    _position = new_geo.topLeft();
  };

  return tmp;
}

Missile *Tank::fire() {
  Missile *missile = new Missile(*this);
  Thegame.MissileList.push_back(missile);  //开火后已经注入到导弹列表中了
  return missile;
}
