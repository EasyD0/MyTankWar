#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <qcolor.h>
#include <QKeyEvent>
#include <QTimer>
#include "Game.h"

//extern Game Thegame;

MainWindow::MainWindow(Game *thegame, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), Thegame(thegame) {
  //ui->setupUi(this);
  // setWindowIcon(QIcon(":/png/tank/p1tankU.png"));
  setWindowTitle("Tank War"); // 设置标题
  setGeometry(100, 100, Width*1.5, Height*1.5); // 设置位置和大小
  setFixedSize(Width * 1.5, Height * 1.5);      // 固定大小

  timer = new QTimer(this);
  timer->setInterval(70); // 70ms

  // timer每过Interval触发一次timeout, 然后调用update(), 从而导致paintEvent()被调用
  connect(timer, &QTimer::timeout, this, &MainWindow::myupdate);
  timer->start();
}

MainWindow::~MainWindow() {
  delete ui;
  timer->stop();
  delete timer;
}


void MainWindow::paintEvent(QPaintEvent *event) {
    Thegame->Gamepainter.begin(this);

    //Thegame->Gamepainter.drawRect(100, 100, 200, 100);
    //Thegame->Gamepainter.drawImage(0, 0,QImage(":/mapseg/png/mapseg/wall.png"));
    Thegame->game_update(); // TODO
    Thegame->Gamepainter.end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_W) {
    Thegame->PlayerTank->set_dir(Up);
    Thegame->PlayerTank->move(*Thegame);
  }

  if (event->key() == Qt::Key_S) {
    Thegame->PlayerTank->set_dir(Down);
    Thegame->PlayerTank->move(*Thegame);
  }
  if (event->key() == Qt::Key_A) {
    Thegame->PlayerTank->set_dir(Left);
    Thegame->PlayerTank->move(*Thegame);
  }
  if (event->key() == Qt::Key_D) {
    Thegame->PlayerTank->set_dir(Right);
    Thegame->PlayerTank->move(*Thegame);
  }

  if (event->key() == Qt::Key_J) {
    Missile *tmp = Thegame->PlayerTank->fire(*Thegame);
    if (tmp != nullptr)
      Thegame->MissileList.push_back(tmp);
  }
}

void MainWindow::myupdate(){
    update();
}
