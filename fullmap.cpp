#include "fullmap.h"
#include <QtLogging>
#include <qlogging.h>
#include <qpainter.h>
#include <vector>

Fullmap::Fullmap() { // 默认初始化为空的地图
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      _fullseg[i][j] = nullptr;
    }
  }
}

Fullmap::~Fullmap() {
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      if (_fullseg[i][j] != nullptr) {
        delete _fullseg[i][j];
      }
    }
  }
}

bool Fullmap::load_map(unsigned _num, QPainter &_painter) {
  clear(); // 清空图层
           //
  // 如果超过最大关卡, 应该取模
  if (_num == 0) {
    qWarning("错误的关卡");
    return false;
  }

  if (_num > MAX_game_level) {
    qInfo("已经通关了,这是循环的关卡");
    _num = _num - MAX_game_level;
  }

  using std::vector;
  vector<vector<int>> map(Col, vector(Row, 0));

  switch (_num) {
  case 1:
    map = {
        // 1,2,3,4,5,6,7,8,9,0,1,2,3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 2},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    };
    break;
  case 2:
    map = {
        // 1,2,3,4,5,6,7,8,9,0,1,2,3
        {0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0}, // 1行
        {3, 3, 0, 1, 1, 1, 0, 1, 1, 1, 0, 3, 3}, // 2
        {3, 3, 0, 1, 0, 1, 0, 1, 0, 1, 0, 3, 3}, // 3
        {3, 3, 0, 1, 1, 1, 0, 1, 0, 1, 0, 3, 3}, // 4
        {3, 3, 0, 0, 0, 1, 0, 1, 0, 1, 0, 3, 3}, // 5
        {3, 3, 0, 1, 1, 1, 0, 1, 1, 1, 0, 3, 3}, // 6
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, // 7
        {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2}, // 8
        {5, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 5}, // 9
        {5, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 5}, // 10
        {5, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 5}, // 11
        {5, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 5}, // 12
        {5, 5, 5, 0, 0, 1, 0, 1, 0, 0, 5, 5, 0}, // 13
    };
    break;
  default:
    break;
  };

  for (int i = 0; i < Row; ++i)
    for (int j = 0; j < Col; ++j) {
      _fullseg[i][j] = new Mapseg(i * SegWidth, j * SegHeight,
                                  static_cast<MapBlock>(map[i][j]));
    };

  display(_painter); // TODO
  return true;
}

void Fullmap::display(QPainter &_painter) const {
  // 地图边框
  _painter.setBrush(Qt::black);
  _painter.setPen(Qt::black);
  _painter.drawRect(0, 0, Width, Height);

  //地图色块
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      if (_fullseg[i][j] != nullptr) {
        _fullseg[i][j]->display(_painter);
      }
    }
  }
}