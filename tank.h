#ifndef TANK_H
#define TANK_H
//#include "Gamesetting.h"
#include "baseblock.h"
#include <qobject.h>
#include <qpoint.h>

enum TankType {
  Player, // 玩家
  Enemy1, // 普通坦克
  Enemy2, // 快速坦克
  Enemy3  // 重型坦克
};

template <TankType T> class Tank : public Baseblock {

  friend class Game;
protected:
  TankType _type = T; // 坦克类型
  int _level = 1;     // 大炮等级 等级1:低速炮, 等级2: 高速炮, 等级3: 高速穿甲弹
  int _life = 1;      // 生命
  int _speed = 12;     // 速度

public:
  Tank(const QPoint& pos, Direction d); // 初始化必须给出坦克的位置和方向
  Tank();

public:
  inline void update_level(int l);
  inline void add_life() { _life++; }
  inline void add_level() { _level++; }
  inline void rotation_L() {_dir = static_cast<Direction>((_dir + 3) % 4);}
  inline void rotation_R() { _dir = static_cast<Direction>((_dir + 1) % 4); }
  
  QRect move();
  Baseblock *fire(); // todo 发射后应该返回这个炮弹的指针
  
  void display(QPainter &_painter) const override;



private:
};

#endif // TANK_H
