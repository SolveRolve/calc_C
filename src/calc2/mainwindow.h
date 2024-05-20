#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>

#include "credit.h"
#include "qcustomplot.h"
#ifdef __cplusplus

extern "C" {
#include "../stack.h"
char *solv(char *Str_postfix, int *err, double *result);
#endif

#ifdef __cplusplus
}

#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  credit credit;
  QVector<double> x, y;
  double xBegin, xEnd;

 public slots:
  void dig_num();
  int flag();
  int flag_1();
  double graf_painter(char *str, double x);
  void graf_plot(char *buffer, QString *new_label);
  void clear_graf();
  void result_print(QString *new_label, double result);
  void backspace(QString *new_label);
  void on_lineEdit_editingFinished();
  void on_lineEdit_2_editingFinished();
  float on_lineEdit_3_editingFinished();

  //    double solver(char* str);

 private slots:

  void on_pushButton_35_clicked();
};
#endif  // MAINWINDOW_H
