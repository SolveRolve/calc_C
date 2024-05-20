#ifndef GRAF_H
#define GRAF_H

#include <QWidget>

namespace Ui {
class graf;
}

class graf : public QWidget {
  Q_OBJECT

 public:
  explicit graf(QWidget *parent = nullptr);
  ~graf();

 private:
  Ui::graf *ui;
  double xBegin, xEnd, h, X;
  int K;
  QVector<double> x, y;
};

#endif  // GRAF_H
