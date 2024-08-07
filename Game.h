// 记录游戏的变量
#ifndef GAME_H
#define GAME_H

#include "fullmap.h"
#include "tank.h"
#include <qpainter.h>
#include <stack>
#include <QMainWindow>
#include "missile.h"

class Missile;

struct Game {

  // 游戏数据
  int score = 0;        // 分数
  int level = 1;        // 当前关卡
  int playerlife = 3;   // 玩家生命
  int player_level = 1; // 玩家坦克等级

  std::stack<Tank *> enemy_tank;     // 当前关卡剩余的敌方坦克堆栈
  std::vector<Tank *> CurrentEnemyList; // 当前存在的地方坦克列表
  Tank *PlayerTank = nullptr; // 玩家当前的坦克

  std::vector<Missile*> MissileList; // 存储所有的炮弹

  Fullmap Current_map{};         // 地图
  Mapseg *player_base = nullptr; // 玩家基地


  QPainter Gamepainter; // 画笔 由于QPainter必须绑定窗口才能显示,
                        // 必须将它绑定一个窗口,可以初始化时就绑定指针,
						// 也可以在用begin()成员函数绑定

  // 构造函数
  Game();
  ~Game() {
    game_clear();
	if (PlayerTank != nullptr)
    	delete PlayerTank;
    PlayerTank = nullptr;
    };

  void game_clear();

  void game_init(int l);

  void load_EnemyStack(int l);

  bool gameover_check();
  bool gameend_check();

  void load_a_enemy();
  void load_player();
  void load_new_player();
  void display();

  void check_disappear(); // 检查各个元素 是否disappear

  bool game_update(); // 更新游戏状态

  void missile_move(){
	if(!MissileList.empty()){
		for (auto &m : MissileList){
			m->move(*this);
		}
	}
  }
};

//static Game Thegame{};

#endif // GAME_H