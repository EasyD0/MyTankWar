#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(Game *thegame,QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  Game *Thegame;
  QTimer *timer;


protected slots:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void myupdate();
};
#endif // MAINWINDOW_H
