#include "Game.h"
#include "missile.h"
#include <qpainter.h>

// extern QPainter painter;

Game::Game() : Current_map() { // 默认的第一关
  score = 0;
  level = 1;
  playerlife = 3;
  player_level = 1;

  PlayerTank = new Tank{Player};
  game_init(1);
}

void Game::game_init(int l) { // 载入新的关卡, 地图, 敌人信息, 玩家信息
  game_clear();

  level = l;
  Current_map.load_map(level);
  player_base = Current_map.get_map()[12][6];

  load_EnemyStack(level);
  load_a_enemy();
  load_a_enemy();

  load_player();
}

void Game::game_clear() { // 清除数据, 为了载入新的关卡
  for (auto &tank : CurrentEnemyList) {
    delete tank;
  }
  CurrentEnemyList.clear();

  while (!enemy_tank.empty()) {
    delete enemy_tank.top();
    enemy_tank.pop();
  }

  for (auto &missile : MissileList) {
    delete missile;
  }
  MissileList.clear();

  Current_map.clear();
  player_base = nullptr;
}

void Game::load_EnemyStack(
    int l) { // 载入敌方坦克堆栈 l=level, 注意这是堆栈, 最后的是第一个坦克
  if (l == 1 || l == 2) {
    enemy_tank.push(new Tank(Enemy1, {2 * SegWidth, 0 * SegHeight}, Up));
    enemy_tank.push(new Tank(Enemy2, {8 * SegWidth, 0 * SegHeight}, Up));
    enemy_tank.push(new Tank(Enemy3, {6 * SegWidth, 0 * SegHeight}, Up));
    enemy_tank.push(new Tank(Enemy1, {0 * SegWidth, 0 * SegHeight}, Up));
  }
}

void Game::load_a_enemy() { // 将坦克 从观关卡剩余堆栈 转移到当前存在的坦克列表
  if (!enemy_tank.empty() && CurrentEnemyList.size() < 2) {
    auto *tank = enemy_tank.top();
    enemy_tank.pop();
    CurrentEnemyList.push_back(tank);
  }
}

void Game::load_player() { // 重置玩家坦克的位置

  PlayerTank->_position = {player_x * SegWidth, player_y * SegHeight};
  PlayerTank->_geo.setRect(player_x * SegWidth, player_y * SegHeight, SegWidth,
                           SegHeight);
  PlayerTank->_dir = Up;
}

void Game::load_new_player() { // 玩家重开
  if (PlayerTank != nullptr) {
    delete PlayerTank;
  }

  PlayerTank = new Tank(Player);
  load_player();
}

void Game::display() {

  // 显示坦克
  for (auto &tank : CurrentEnemyList) {
    tank->display(Gamepainter);
  }

  PlayerTank->display(Gamepainter);

  // 显示导弹
  for (auto &missile : MissileList) {
    missile->display(Gamepainter);
  }
  // 显示地图
  Current_map.display(Gamepainter);
}

bool Game::gameover_check() { // TODO 游戏结束, 现在直接返回false
  return false;
  if (playerlife <= 0) { // 玩家生命为0
    return true;
  }

  if (player_base->life() <= 0) { // 玩家基地被摧毁
    return true;
  }

  return false;
}

void Game::check_disappear() { // 检查是否有消失的坦克或者导弹, 并删除他们,
                               // 对于地形的消失, 由fullmap处理
  for (auto it = MissileList.begin(); it != MissileList.end();) {
    if ((*it)->is_disappear()) {
      delete (*it);
      it = MissileList.erase(
          it); // 这里不必担心迭代器失效的问题, 因为erase会返回下一个迭代器
    } else {
      ++it;
    }
  }

  for (auto it = CurrentEnemyList.begin(); it != CurrentEnemyList.end();) {
    if ((*it)->is_disappear()) {
      delete *it;
      it = CurrentEnemyList.erase(it);
    } else {
      ++it;
    }
  }

  if (PlayerTank->is_disappear()) {
    delete PlayerTank;
    PlayerTank = nullptr;
  }
}

bool Game::game_update() { // 每一帧的更新
  if (gameover_check())
    // TODO 游戏结束
    return false;

  if (gameend_check())
    // TODO 过关
    return false;

  // 清除消失的坦克和导弹
  check_disappear();

  if (PlayerTank == nullptr) {
    playerlife -= 1;
    load_new_player();
  }

  load_a_enemy();

  // 导弹移动
  missile_move();

  // 更新地图, 删除消失的地形
  Current_map.update_map();

  // 显示图像
  this->display();

  return true;
}

bool Game::gameend_check() { // 关卡结束
  if (CurrentEnemyList.empty() && enemy_tank.empty()) {
    level += 1;
    game_init(level);
    return true;
  }
  return false;
}
