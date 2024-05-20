#ifndef CREDIT_H
#define CREDIT_H
#include <QWidget>
#include <cmath>

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  double on_lineEdit_editingFinished();
  double on_lineEdit_2_editingFinished();
  double on_lineEdit_3_editingFinished();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
