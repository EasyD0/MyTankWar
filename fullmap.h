#ifndef FULLMAP_H
#define FULLMAP_H

#include <QObject>
#include <qpainter.h>
#include "mapseg.h"
#include "Gamesetting.h"

class Fullmap {
private:
  using MapsegP = Mapseg*;
  MapsegP _fullseg[Row][Col];

public:
  void display(QPainter &_painter) const;

public:
  Fullmap();
  ~Fullmap();

  bool load_map(int num);
  void load_default_map() { load_map(1); }

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

  void update_map();

};

#endif // FULLMAP_H
