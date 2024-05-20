#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

double credit::on_lineEdit_editingFinished() {
  return ui->lineEdit->text().toDouble();
}

double credit::on_lineEdit_2_editingFinished() {
  return ui->lineEdit_2->text().toDouble();
}

double credit::on_lineEdit_3_editingFinished() {
  return ui->lineEdit_3->text().toDouble();
}

void credit::on_pushButton_clicked() {
  double summ_credit = on_lineEdit_editingFinished();
  double mes_credit = on_lineEdit_2_editingFinished();
  double percent_credit = on_lineEdit_3_editingFinished() / 1200;
  double mes_money =
      summ_credit *
      (percent_credit +
       percent_credit / (pow((1.0 + percent_credit), mes_credit) - 1));
  double credit_all = mes_money * mes_credit - summ_credit;
  summ_credit += credit_all;
  ui->label->setText(QString::number(mes_money, 'f', 2));
  ui->label_2->setText(QString::number(credit_all, 'f', 2));
  ui->label_3->setText(QString::number(summ_credit, 'f', 2));
}

void credit::on_pushButton_2_clicked() {
  double summ_credit = on_lineEdit_editingFinished();
  double mes_credit = on_lineEdit_2_editingFinished();
  double percent_credit = on_lineEdit_3_editingFinished();
  double Cd = 0;
  if (ui->label->text() == "")
    Cd = summ_credit / mes_credit;
  else
    Cd = ui->label->text().toDouble();
  double Cp = (summ_credit * (percent_credit / 100) * 30.41) / 365;
  summ_credit = summ_credit - (Cd);
  ui->lineEdit->setText(QString::number(summ_credit, 'f', 2));
  if (ui->label->text() == "") ui->label->setText(QString::number(Cd, 'f', 2));
  Cp += ui->label_2->text().toDouble();
  ui->label_2->setText(QString::number(Cp, 'f', 2));
  ui->label_3->setText(QString::number(summ_credit, 'f', 2));
}

void credit::on_pushButton_3_clicked() {
  ui->label->clear();
  ui->label_2->clear();
  ui->label_3->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit->clear();
}
