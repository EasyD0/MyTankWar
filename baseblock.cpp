#include "baseblock.h"

bool Baseblock::isCollision(const Baseblock &other) const {
  return _geo.intersects(other.geometry());
}