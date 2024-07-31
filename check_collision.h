#ifndef CHECK_COLLISION_H
#define CHECK_COLLISION_H

#include "Gamesetting.h"
#include "baseblock.h"
#include "fullmap.h"
#include <qobject.h>
#include <qtmetamacros.h>
#include "tank.h"

struct check : public QObject{
  Q_OBJECT
public: //warring 为什么这里不加public会报错, 说这些函数是私有的???
  
  static inline bool check_collision(const QRect &_newgeo, const Baseblock &_b) {
    return _newgeo.intersects(_b.geometry());
  }

  static Mapseg* check_collision_with_map(const QRect &_newgeo, Fullmap &_map) {
    auto fullmap = _map.get_map();

    for (int i = 0; i < Row; i++) {
      for (int j = 0; j < Col; j++) {
        if (fullmap[i][j]&&fullmap[i][j]->get_kind() >= 3) {
          if (check_collision(_newgeo, *(fullmap[i][j]))) {
            return fullmap[i][j];
          }
        }
      }
    }
    return nullptr;
  }

  static bool check_collision_with_edge(const QRect &_newgeo) {
    if (_newgeo.top() < 0 || _newgeo.bottom() > Row * SegHeight ||
        _newgeo.left() < 0 || _newgeo.right() > Col * SegWidth) {
      return true;
    }
    return false;
  }

  static Tank *check_collision_with_alltank(const QRect &_newgeo,
                                            std::vector<Tank *> &_enemyTankList,
                                            Tank &_player) {
    if (check_collision(_newgeo, _player)) {
      return &_player;
    }

    for (auto &_e : _enemyTankList) {
      if (check_collision(_newgeo, *_e)) {
        return _e;
      }
    }
    return nullptr;
  }

  static bool checkall(const QRect &_newgeo, Fullmap &_map, Tank &_player,
					   std::vector<Tank *> &_enemyTankList) {
    return (check_collision_with_map(_newgeo, _map) != nullptr) ||
           check_collision_with_edge(_newgeo) ||
		   (check_collision_with_alltank(_newgeo, _enemyTankList, _player)!=nullptr);
  }
};

#endif // CHECK_COLLISION_H
