#ifndef FULLMAP_H
#define FULLMAP_H

#include <QObject>
#include <qpainter.h>
#include "mapseg.h"
#include "Gamesetting.h"

class Fullmap {
private:
  Mapseg* _fullseg[Row][Col];

private:
  void display(QPainter &_painter) const;

public:
  Fullmap();
  ~Fullmap();

  bool load_map(unsigned num, QPainter &_painter);
  void load_default_map(QPainter &_painter) { load_map(1, _painter); }
  void clear(); // TODO
  auto get_map()  { return _fullseg; }
};

#endif // FULLMAP_H
