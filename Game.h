// 记录游戏的变量

#include <stack>
#include "fullmap.h"

struct Game {
  int score = 0; // 分数
  int level = 1; // 当前关卡
  int playerlife = 3; // 玩家生命
  int player_level = 1; // 玩家坦克等级

  // TODO 记录时间

  std::stack<int> enemy_tank; // 当前关卡敌方坦克堆栈
  Fullmap *map = nullptr; // 地图

  Game() = default;


  void init(int level) { load_enemy(); }

  void load_enemy() { //载入敌方坦克堆栈
	// TODO
  }



};