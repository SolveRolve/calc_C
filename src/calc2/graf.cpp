#include "graf.h"

#include "ui_graf.h"
graf::graf(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::graf)

{
  ui->setupUi(this);
  h = 1.0;
  xBegin = -1000000;
  xEnd = 1000000;
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(xBegin, xEnd);
}

graf::~graf() { delete ui; }
