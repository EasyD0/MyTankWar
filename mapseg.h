#ifndef MAPSEG_H
#define MAPSEG_H

#include "baseblock.h"
#include <QObject>

enum MapBlock { nothing, wall, steel, sand, water, grass, boss };

class Mapseg : public Baseblock {
  Q_OBJECT

private:
  MapBlock _seg_kind = nothing; // 地块类型
  int _life = 0;                // 地块生命
  unsigned _penetration = 0;    // 导弹可穿透等级 0 可直接穿透,
  bool _pass = true;            // 坦克可通行? false 不可穿透,

private:
  void init_kind(MapBlock kind); // 根据种类初始化地块

public:
  //--- 构造器和析构器
  Mapseg(const QPoint &pos, MapBlock segkind = nothing);

  Mapseg(const int &x = 0, const int &y = 0, MapBlock segkind = nothing)
      : Mapseg(QPoint{x, y}, segkind) {}

  // 删除拷贝构造器 和 拷贝运算
  Mapseg(const Mapseg &) = delete;
  Mapseg &operator=(const Mapseg &) = delete;

  virtual ~Mapseg() override = default;

  // 接口函数
  MapBlock get_kind() const { return _seg_kind; }
  bool is_pass() const { return _pass; }
  int penetration() const { return _penetration; }

  virtual void display(QPainter &_painter) const override;

  void update_seg();
  int life() const { return _life; }
  void set_life(int l) { _life = l; }
  void set_disappear(bool a) { _disappear = a; }

  // using Baseblock::is_disappear;
  // bool is_disappear() const { return _disappear; }
};

#endif // MAPSEG_H
