#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "Game.h"



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game Thegame;
  MainWindow w(&Thegame,nullptr);
  w.show();
  return a.exec();
}
