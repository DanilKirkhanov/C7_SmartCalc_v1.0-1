#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget* parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

// void CreditWindow::on_pushButton_close_clicked() { close(); }

// void CreditWindow::on_pushButton_calculate_clicked() {
//   CreditWindow::calculate_credit();
// }

// void Credit::calculate_credit() {
//   double percent = ui->lineEdit_percent->text().toDouble();
//   double credit_sum = ui->lineEdit_sum->text().toDouble();
//   double months = 0.0;
//   if (ui->comboBox->currentText() == "Месяцев") {
//     months = ui->lineEdit_months->text().toDouble();
//   } else if (ui->comboBox->currentText() == "Лет") {
//     months = ui->lineEdit_months->text().toDouble() * 12;
//   }
//   if (months <= 0 || percent <= 0 || credit_sum <= 0 ||
//       credit_sum >= __INT64_MAX__ || percent >= 100 || months >= 50 * 12 + 1)
//       {
//     ui->monthly_payment_output->setText("Ошибка. проверьте введенные
//     значения"); ui->overpayment_output->setText("Ошибка. проверьте введенные
//     значения"); ui->sum_to_pay_output->setText("Ошибка. проверьте введенные
//     значения");
//   } else {
//   }
// }

void Credit::on_pushButton_calc_credit_clicked() {
  QString res;
  double P = ui->doubleSpinBox_ammount->text().toDouble();
  double proc = ui->doubleSpinBox_proc->text().toDouble() / 12.0 / 100.;
  int m = ui->spinBox_term->text().toInt();
  ui->tableWidget->setRowCount(m);
  ui->tableWidget->setColumnCount(1);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Payment");
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

  double month_pay = 0;
  double total_pay = 0;
  if (ui->radioButton_1->isChecked()) {
    for (int i = 0; i < m; i++) {
      month_pay = (P * proc * pow(1 + proc, m)) / (pow(1 + proc, m) - 1);
      QTableWidgetItem* tbl =
          new QTableWidgetItem(QString::number(month_pay, 'f', 2));
      ui->tableWidget->setItem(0, i, tbl);
    }
    total_pay = round(month_pay * 100) / 100 * m;
  } else if (ui->radioButton_2->isChecked()) {
    for (int i = 0; i < m; i++) {
      month_pay = P / m + ((P - ((P * (i)) / m)) * proc);
      QTableWidgetItem* tbl =
          new QTableWidgetItem(QString::number(month_pay, 'f', 2));
      ui->tableWidget->setItem(0, i, tbl);
      total_pay += round(month_pay * 100) / 100;
    }
  }

  res = QString::number(total_pay, 'f', 2);
  ui->label_total->setText(res);
  res = QString::number(total_pay - P, 'f', 2);
  ui->label_overpay->setText(res);
}
