#include "check_collision.h"
#include "missile.h"
#include "Game.h"
//extern Game Thegame;


Missile::Missile(const Tank &tank) : Baseblock() {
  _dir = tank._dir;
  _level = tank._level;
  _speed = tank._speed + 10 + (_level > 1) * 10;

  if (tank._tank_type == Player) {
    _missile_type = PlayerMissile;
  } else {
    _missile_type = EnemyMissile;
  }

  _position =
      tank._position + QPoint((_dir == Up || _dir == Down) * SegWidth / 2 +
                                  (_dir == Right) * SegWidth,
                              (_dir == Left || _dir == Right) * SegHeight / 2 +
                                  (_dir == Down) * SegHeight);

  _geo.setRect(_position.x(), _position.y(), MissileWidth, MissileHeight);
}

void Missile::display(QPainter &_painter) const {
  if (_disappear)
    return;
  QImage img(":/png/other/Missile.png");
  _painter.drawImage(_geo, img);
}

void Missile::move(Game &Thegame) {
  if (_disappear)
    return;
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

  //  TODO和边界碰撞
  if (check::check_collision_with_edge(new_geo)) {
    _life = 0;
    _disappear = true;
  }

  // TODO 和地图块碰撞 暂时不考虑, 直接让导弹穿透
  auto *seg = check::check_collision_with_map(new_geo, Thegame.Current_map);
  if (seg) {
    // if(seg->)
  }

  // 和坦克碰撞
  auto *tank = check::check_collision_with_alltank(
      new_geo, Thegame.CurrentEnemyList, *Thegame.PlayerTank);
  if (tank) {
    // 发生碰撞后, 导弹消失
    _life = 0;
    _disappear = true;

    if (_missile_type ==
        PlayerMissile) // 玩家导弹不可能命中自己,因此不用判断坦克类型
      tank->_life -= 1;
    else if (tank->_tank_type == Player) { // 如果敌人导弹命中玩家
      tank->_life -= 1;
    }

    if (tank->_life <= 0) { // 如果坦克死亡
      tank->_disappear = true;
      if (tank->_tank_type == Player) { // 如果玩家死亡

        Thegame.playerlife -= 1;
        if (Thegame.playerlife <= 0) {
          // TODO 游戏结束, 这里是否应该放到 struct Game 中实现?
        };
      } else { // 如果敌人死亡
        Thegame.score += 100;
      }
    }
  }

  // TODO 和导弹碰撞  暂时不考虑

  // 都没有碰撞
  _position = new_geo.topLeft();
  _geo = new_geo;
}