#ifndef CHECK_COLLISION_H
#define CHECK_COLLISION_H

#include "Gamesetting.h"
#include "baseblock.h"
#include "fullmap.h"
#include <qobject.h>
#include <qtmetamacros.h>
#include <vector>


struct check : public QObject{
  Q_OBJECT
  
  static inline bool check_collision(const QRect &newgeo, const Baseblock &b) {
    return newgeo.intersects(b.geometry());
  }

  static bool check_collision_with_map(const QRect &newgeo, Fullmap &map) {
    auto fullmap = map.get_map();

    for (int i = 0; i < Row; i++) {
      for (int j = 0; j < Col; j++) {
        if (fullmap[i][j]->get_kind() >= 3) {
          if (check_collision(newgeo, *(fullmap[i][j]))) {
            return true;
          }
        }
      }
    }
    return false;
  }

  static bool check_collision_with_edge(const QRect &newgeo) {
    if (newgeo.top() < 0 || newgeo.bottom() > Row * SegHeight ||
        newgeo.left() < 0 || newgeo.right() > Col * SegWidth) {
      return true;
    }
    return false;
  }

  static bool
  check_collision_with_alltank(const QRect &newgeo,
                               std::vector<Baseblock *> &EnemyTankList,
                               Baseblock &player) {
    if (check_collision(newgeo, player)) {
      return true;
    }

    for (auto &enemy : EnemyTankList) {
      if (check_collision(newgeo, *enemy)) {
        return true;
      }
    }
    return false;
  }
};

#endif // CHECK_COLLISION_H
