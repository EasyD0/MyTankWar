#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <qcolor.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  // TODO: 需要添加一些绘图的代码, 用于更新地图
  

  
  /*
  QImage image(":/png/mapseg/1.png");
  painter.drawImage(QRect(0, 0, 50, 50), image);


  QPen pen; // 画笔
  pen.setColor(QColor(255, 0, 0));
  QBrush brush(QColor(0, 255, 0, 125)); // 画刷
  painter.setPen(pen);                  // 添加画笔
  painter.setBrush(brush);              // 添加画刷
  painter.drawRect(50, 50, 200, 100);   // 绘制矩形

  QBrush brush2(QColor(0, 0, 255, 125)); // 画刷
  painter.setPen(pen);                  // 添加画笔
  painter.setBrush(brush2);              // 添加画刷
  painter.drawRect(100, 100, 200, 100); // 绘制矩形
*/
}
