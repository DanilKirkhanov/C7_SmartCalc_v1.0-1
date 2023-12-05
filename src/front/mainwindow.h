#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "./ui_mainwindow.h"
#include "credit.h"

#define X_0 -10
#define Y_0 -10
#define X_END 10
#define Y_END 10
#define X_Y_MIN -1000000
#define X_Y_MAX 1000000
#define STEP 0.01

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

extern "C" {
#include "../s21_calc.h"
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void digits();
  void oper();
  void func();
  void enter();
  void clean();
  void brackets();
  int leksema(Ui::MainWindow *ui);
  void dot();
  void plot(char *c_str);

  void on_pushButton_credit_clicked();

 private:
  Ui::MainWindow *ui;
  Credit *credit;
  int credit_window;
  int brackets_count;
  int dot_flag;
  double X, y_calculated;
  double x_0, x_end, y_0, y_end;
  int steps;
  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
