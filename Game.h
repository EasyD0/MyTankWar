// 记录游戏的变量
#ifndef GAME_H
#define GAME_H

#include "fullmap.h"
#include "tank.h"
#include <qpainter.h>
#include <stack>


class Missile;

struct Game {

  // 游戏数据
  int score = 0;        // 分数
  int level = 1;        // 当前关卡
  int playerlife = 3;   // 玩家生命
  int player_level = 1; // 玩家坦克等级

  std::stack<Tank *> enemy_tank;     // 当前关卡剩余的敌方坦克堆栈
  std::vector<Tank *> CurrentEnemyList; // 当前存在的地方坦克列表
  Tank *PlayerTank = new Tank{Player}; // 玩家当前的坦克

  std::vector<Missile*> MissileList; // 存储所有的炮弹

  Fullmap Current_map{};         // 地图
  Mapseg *player_base = nullptr; // 玩家基地


  QPainter painter; // 画笔

  // 构造函数
  Game();
  ~Game(){game_clear();};

  void game_clear();

  void game_init(int level);

  void load_enemy(int level);

  bool gameover_check();
  bool gameend_check();

  void load_a_enemy();
  void load_player();
  void load_new_player();
  void display(QPainter &_painter);

  void check_disappear(); // 检查各个元素 是否disappear

  bool game_update(); // 更新游戏状态
};

static Game Thegame{};

#endif // GAME_H