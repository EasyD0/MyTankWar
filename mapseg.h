#ifndef MAPSEG_H
#define MAPSEG_H

#include "baseblock.h"
#include <QObject>

enum MapBlock { nothing, grass, sand, wall, steel, water, boss };

class Mapseg : public Baseblock {
  Q_OBJECT
  
private:
  MapBlock _seg_kind = nothing; // 地块类型
  unsigned _life = 0;            // 地块生命
  bool _penetration = 0;        // 导弹可穿透等级 0 可直接穿透,
  bool _pass = true;            // 坦克可通行? false 不可穿透,

private:
  void init_kind(MapBlock kind); // 根据种类初始化地块

public:
  //--- 构造器和析构器
  Mapseg(const QPoint &pos, MapBlock segkind = nothing);

  Mapseg(const int &x = 0, const int &y = 0, MapBlock segkind = nothing)
      : Mapseg(QPoint{x, y}, segkind) {}


  //删除拷贝构造器 和 拷贝运算
  Mapseg(const Mapseg &) = delete;
  Mapseg& operator=(const Mapseg &) =delete;

  virtual ~Mapseg() override = default;


  // 接口函数
  MapBlock get_kind() const { return _seg_kind; }
  //void modify_seg(); //todo

  virtual void display(QPainter &_painter) const override;

  //void update_life(); //更新生命值
  void update();
  int life() const { return _life; }
};

#endif // MAPSEG_H
