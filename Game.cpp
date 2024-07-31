#include "Game.h"
#include "missile.h"
#include <qpainter.h>

extern QPainter painter;

Game::Game() {                           // 默认的第一关
  Current_map.load_default_map(painter); // 载入并绘制了地图

  player_base = Current_map.get_map()[12][6];

  score = 0;
  level = 1;
  playerlife = 3;
  player_level = 1;

  load_enemy(level);
  load_a_enemy();
  load_a_enemy();

  load_player();

  display(painter);
}

void Game::game_clear() { // 清除内容, 为了载入新的关卡
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

  delete PlayerTank;
  PlayerTank = nullptr;

  Current_map.clear();
  player_base = nullptr;
}

void Game::game_init(int l) { // 载入新的关卡
  level = l;
  Current_map.load_map(level, painter);

  player_base = Current_map.get_map()[12][6];

  load_enemy(level);
  load_a_enemy();
  load_a_enemy();

  load_player();

  display(painter);
}

void Game::load_enemy(int level) { // 载入敌方坦克堆栈
  if (level == 1 || level == 2) {
    enemy_tank.push(new Tank(Enemy2, {0, 0}, Up));
    enemy_tank.push(new Tank(Enemy2, {0, 1}, Up));
    enemy_tank.push(new Tank(Enemy2, {0, 2}, Up));
    enemy_tank.push(new Tank(Enemy2, {0, 3}, Up));
  }
}

void Game::load_a_enemy() { // 将坦克 从观关卡剩余堆栈 转移到当前存在的坦克列表
  if (!enemy_tank.empty() && CurrentEnemyList.size() < 2) {
    auto *tank = enemy_tank.top();
    enemy_tank.pop();
    CurrentEnemyList.push_back(tank);
  }
}

void Game::load_player() {
  PlayerTank->_geo.setRect(player_x * SegWidth, player_y * SegHeight, SegWidth,
                           SegHeight);
  PlayerTank->_dir = Up;
}

void Game::load_new_player() {
  if (PlayerTank != nullptr) {
    delete PlayerTank;
  }

  PlayerTank = new Tank(Player);
}

void Game::display(QPainter &_painter) {
  Current_map.display(_painter);

  for (auto &tank : CurrentEnemyList) {
    tank->display(_painter);
  }

  PlayerTank->display(_painter);

  for (auto &missile : MissileList) {
    missile->display(painter);
  }
}

bool Game::gameover_check() { // TODO 游戏结束
  if (playerlife <= 0) {

    return true;
  }

  if (player_base->life() <= 0) {
    return true;
  }

  return false;
}

void Game::check_disappear() { //检查是否有消失的坦克或者导弹, 并删除他们
  for (auto it = MissileList.begin(); it != MissileList.end();) {
    if ((*it)->is_disappear()) {
      delete *it;
      it = MissileList.erase(it);  //这里不必担心迭代器失效的问题, 因为erase会返回下一个迭代器
    } else {
      it++;
    }
  }

  for (auto it = CurrentEnemyList.begin(); it != CurrentEnemyList.end();) {
    if ((*it)->is_disappear()) {
      delete *it;
      it = CurrentEnemyList.erase(it);
    } else {
      it++;
    }
  }

  if (PlayerTank->is_disappear()) {
	delete PlayerTank;
	PlayerTank = nullptr;
  }
}

bool Game::game_update() { //每一帧的更新
  if (gameover_check())
    // TODO 游戏结束
    return false;

  if (gameend_check())
	// TODO 过关
	return false;

  // 更新坦克
  check_disappear();

  if (PlayerTank == nullptr) {
	playerlife -= 1;
	load_new_player();
  }

  load_a_enemy();

  // 更新地图
  Current_map.update_map();

  // 显示图像
  display(painter);

  return true;
}

bool Game::gameend_check() {
  if (CurrentEnemyList.empty() && enemy_tank.empty()) {
	level += 1;
	game_init(level);
	return true;
  }
  return false;
}