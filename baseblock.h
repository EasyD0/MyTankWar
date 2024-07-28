#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QObject>

enum Direction { Up, Right, Down, Left };

class Baseblock
    : public QObject { // 当类型使用QT的一些功能时，需要继承QObject,
                       // 并加上宏Q_OBJECT , 在它的派生类也要加上Q_OBJECT
  Q_OBJECT

protected:
  QPoint _position{};      // 位置
  QRect _geo{};            // 几何形状
  Direction _dir = Up;     // 方位
  bool _disappear = false; // 是否消失?

public:
  Baseblock() = default;
  Baseblock(const Baseblock &) = delete;
  virtual ~Baseblock() = default;

  virtual void display(QPainter &_painter) const = 0; // 显示方块

  inline QPoint position() const { return _position; }
  inline bool is_disappear() const { return _disappear; }
  inline QRect geometry() const { return _geo; }

  bool isCollision(const Baseblock &other) const; // 是否碰撞
};

#endif // BASEBLOCK_H
