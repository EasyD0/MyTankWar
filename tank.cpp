#include "tank.h"
#include <QImage>
#include <QPoint>
#include "fullmap.h"
#include "check_collision.h"


extern const int SegWidth;
extern const int SegHeight;
const int player_x = 4;
const int player_y = 12;
extern Fullmap *Current_map;

template <TankType T>
Tank<T>::Tank(const QPoint &pos, Direction d) : Baseblock() {
  _position = pos;
  _geo.setRect(pos.x(), pos.y(), SegWidth, SegHeight);

  _dir = d;
  switch (T) {
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
template <TankType T>
Tank<T>::Tank() : Tank<T>({0 * SegWidth, 0 * SegHeight}, Up) {}

template <>
Tank<Player>::Tank()
    : Tank<Player>({player_x * SegWidth, player_y * SegHeight}, Up) {}

template <> void Tank<Player>::update_level(int l) { _level = l; }

template <TankType T> void Tank<T>::display(QPainter &_painter) const {
  if (_disappear)
    return;
  
  std::string path = ":/png/tank/";
  if (T == Player) {
    path += "p1tank";
  } else {
    path += "enemy";
    path += std::to_string(T);
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

template <TankType T> QRect Tank<T>::move() {
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
  /*
  if (check_collision_with_map()) { // todo 检查是否碰撞
    _geo = new_geo;
    _position = new_geo.topLeft();
  };
*/
  return tmp;
}

