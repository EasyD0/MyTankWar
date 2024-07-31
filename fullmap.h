#ifndef FULLMAP_H
#define FULLMAP_H

#include <QObject>
#include <qpainter.h>
#include "mapseg.h"
#include "Gamesetting.h"

class Fullmap {
private:
  Mapseg* _fullseg[Row][Col];

public:
  void display(QPainter &_painter) const;

public:
  Fullmap();
  ~Fullmap();

  bool load_map(unsigned num, QPainter &_painter);
  void load_default_map(QPainter &_painter) { load_map(1, _painter); }
  void clear() {
    for (int i = 0; i < Row; i++) {
	  for (int j = 0; j < Col; j++) {
		if (_fullseg[i][j] != nullptr) {
		  delete _fullseg[i][j];
		  _fullseg[i][j] = nullptr;
		}
	  }
	}
  };
  auto get_map() { return _fullseg; }

  void update_map() {
    for (int i = 0; i < Row; i++) {
      for (int j = 0; j < Col; j++) {
        _fullseg[i][j]->update();
        if (_fullseg[i][i]->is_disappear()) {
          delete _fullseg[i][j];
          _fullseg[i][j] = nullptr;
        }
      }
  	}
  }

};

#endif // FULLMAP_H
