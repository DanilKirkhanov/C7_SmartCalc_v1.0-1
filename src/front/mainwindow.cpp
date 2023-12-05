#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  brackets_count = 0;
  dot_flag = 0;
  credit_window = 0;
  ui->lineEdit_x1->setRange(X_Y_MIN, X_Y_MAX);
  ui->lineEdit_y1->setRange(X_Y_MIN, X_Y_MAX);

  ui->lineEdit_x1->setValue(X_0);
  ui->lineEdit_x2->setValue(X_END);
  ui->lineEdit_y1->setValue(Y_0);
  ui->lineEdit_y2->setValue(Y_END);

  ui->widget->addGraph();
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(oper()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(oper()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(oper()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(oper()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(oper()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(oper()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));
  connect(ui->pushButton_lb, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->pushButton_rb, SIGNAL(clicked()), this, SLOT(brackets()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clean()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(enter()));
}

void MainWindow::digits() {
  ui->Label_res->setText("");
  if (!(ui->Label->text().endsWith(")") || ui->Label->text().endsWith("X"))) {
    QString label = ui->Label->text();
    QPushButton *button = (QPushButton *)sender();
    if ((button->text() == "X" && MainWindow::leksema(ui) != 2) ||
        button->text() != "X") {
      label = label + button->text();
      ui->Label->setText(label);
    }
  }
}

void MainWindow::oper() {
  ui->Label_res->setText("");
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->Label->text();
  if (button->text() == "-" &&
      (ui->Label->text().endsWith("(") || MainWindow::leksema(ui) == 1)) {
    label = label + "-";
    ui->Label->setText(label);
  }
  if (MainWindow::leksema(ui) == 2 || ui->Label->text().endsWith(")") ||
      ui->Label->text().endsWith("X")) {
    label = label + button->text();
    ui->Label->setText(label);
    dot_flag = 0;
  }
}

void MainWindow::func() {
  ui->Label_res->setText("");
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->Label->text();
  if (!(ui->Label->text().endsWith(")") || MainWindow::leksema(ui) == 2)) {
    brackets_count++;
    label = label + button->text() + "(";
    ui->Label->setText(label);
    dot_flag = 0;
  }
}

void MainWindow::brackets() {
  ui->Label_res->setText("");
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->Label->text();
  if (button->text() == "(" &&
      (ui->Label->text().endsWith("(") || MainWindow::leksema(ui) == 3 ||
       MainWindow::leksema(ui) == 1)) {
    brackets_count++;
    label = label + button->text();
    ui->Label->setText(label);
    dot_flag = 0;
  }
  if (button->text() == ")" && brackets_count > 0 &&
          (MainWindow::leksema(ui) == 2) ||
      ui->Label->text().endsWith(")")) {
    brackets_count--;
    label = label + button->text();
    ui->Label->setText(label);
    dot_flag = 0;
  }
}

void MainWindow::enter() {
  if (brackets_count == 0 &&
      (ui->Label->text().endsWith(")") || MainWindow::leksema(ui) == 2)) {
    QString label = ui->Label->text();
    std::string str = label.toStdString();
    QString x_str = ui->lineEdit->text();
    char *c_str = &str[0];
    double x = 0.0;
    if (x_str != "") x = x_str.toDouble();
    double res = smart_calc(c_str, x);
    QString res_label = nullptr;
    if (res != INFINITY && !isnan(res) && res != -INFINITY)
      res_label = QString::number(res, 'g', 15);
    else
      res_label = "ERROR";
    MainWindow::plot(c_str);
    ui->Label_res->setText(res_label);
    brackets_count = 0;
    dot_flag = 0;
  } else
    ui->Label_res->setText("Check equation");
}

void MainWindow::dot() {
  ui->Label_res->setText("");
  if (!ui->Label->text().endsWith("X") && MainWindow::leksema(ui) == 2 &&
      !dot_flag) {
    QString label = ui->Label->text();
    label = label + ".";
    ui->Label->setText(label);
    dot_flag = 1;
  }
}
int MainWindow::leksema(Ui::MainWindow *ui) {
  int res = 0;
  if (ui->Label->text() == "") res = 1;
  if (ui->Label->text().endsWith("0") || ui->Label->text().endsWith("1") ||
      ui->Label->text().endsWith("2") || ui->Label->text().endsWith("3") ||
      ui->Label->text().endsWith("4") || ui->Label->text().endsWith("5") ||
      ui->Label->text().endsWith("6") || ui->Label->text().endsWith("7") ||
      ui->Label->text().endsWith("8") || ui->Label->text().endsWith("9") ||
      ui->Label->text().endsWith("X"))
    res = 2;
  if (ui->Label->text().endsWith("+") || ui->Label->text().endsWith("-") ||
      ui->Label->text().endsWith("*") || ui->Label->text().endsWith("/") ||
      ui->Label->text().endsWith("^") || ui->Label->text().endsWith("mod"))
    res = 3;
  return res;
}

void MainWindow::clean() {
  brackets_count = 0;
  dot_flag = 0;
  ui->Label_res->setText("");
  ui->Label->setText("");
}

void MainWindow::plot(char *c_str) {
  if (c_str) {
    x_0 = ui->lineEdit_x1->text().toDouble();
    x_end = ui->lineEdit_x2->text().toDouble();
    y_0 = ui->lineEdit_y1->text().toDouble();
    y_end = ui->lineEdit_y2->text().toDouble();

    if (x_end <= x_0) x_0 = x_end + 10;
    if (y_end <= y_0) y_0 = y_end + 10;

    ui->widget->xAxis->setRange(x_0, x_end);
    ui->widget->yAxis->setRange(y_0, y_end);
    x.clear();
    y.clear();
    for (X = x_0; X <= x_end + STEP; X += STEP) {
      x.push_back(X);
      y_calculated = smart_calc(c_str, X);
      y.push_back(y_calculated);
      X += STEP;
    }
    if (ui->widget) {
      ui->widget->graph(0)->setData(x, y);
      ui->widget->replot();
    }
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  if (credit_window == 0) credit = new Credit(this);
  credit->show();
  credit_window = 1;
}

MainWindow::~MainWindow() { delete ui; }
