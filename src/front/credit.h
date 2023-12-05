#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private:
  Ui::Credit *ui;

 public slots:
  // void on_pushButton_close_clicked();

 private slots:
  void on_pushButton_calc_credit_clicked();
};

#endif  // CREDIT_H
