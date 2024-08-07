#ifndef MISSILE_H
#define MISSILE_H

#include "baseblock.h"
#include "tank.h"

class Game;

class Missile : public Baseblock {
  
  enum MissileType {
    PlayerMissile, // 玩家
    EnemyMissile,  // 敌方
  };
  
  int _level = 1;
  int _life = 1;
  int _speed = 22;
  int _missile_type = PlayerMissile;

public:
  explicit Missile(const Tank &tank);
  

  void display(QPainter &_painter) const override;

  void move(Game &Thegame);
};

#endif