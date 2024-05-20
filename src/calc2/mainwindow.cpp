#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  {
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(dig_num()));  // ON
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(dig_num()));  // AC
    connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_33, SIGNAL(clicked()), this, SLOT(dig_num()));
    connect(ui->pushButton_34, SIGNAL(clicked()), this, SLOT(dig_num()));
  }
}
MainWindow::~MainWindow() { delete ui; }
int MainWindow::flag() {
  char buffer_1[256] = {0};
  strcpy(buffer_1, ui->label->text().toUtf8().data());
  int len = strlen(buffer_1);
  int len_oper = 0;
  char b[9] = "+-)%(/%*";
  int flag_num = 0;
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < 9; j++) {
      if (b[j] == buffer_1[i]) len_oper = i;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (buffer_1[len - 1] == b[i]) flag_num = 1;
  }
  for (int i = len_oper; i < len; i++) {
    if (buffer_1[i] == '.') flag_num = 1;
  }
  if (buffer_1[len - 1] == '.' || buffer_1[len - 1] == 'x' || len == 0 ||
      len == len_oper)
    flag_num = 1;

  return flag_num;
}
int MainWindow::flag_1() {
  char buffer_1[256] = {0};
  strcpy(buffer_1, ui->label->text().toUtf8().data());
  int len = strlen(buffer_1), flag_num = 0, len_oper = 0;
  if (buffer_1[len - 1] == '*' || buffer_1[len - 1] == '+' ||
      buffer_1[len - 1] == '%' || buffer_1[len - 1] == '^' ||
      buffer_1[len - 1] == '-' || buffer_1[len - 1] == '/' || len == 0 ||
      len == len_oper)
    flag_num = 1;
  if ((buffer_1[len - 1] == '+' || buffer_1[len - 1] == '-') && len == 1)
    flag_num = 0;

  return flag_num;
}
void MainWindow::dig_num() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label;
  int err = 0, flag_num = flag(), fl = flag_1();
  double result = 0;
  char butom[100] = "tansincoslnlogasinacosatan\0\0", but[10] = {0};
  strcpy(but, button->text().toUtf8().data());
  if (ui->label->text() == "error" || ui->label->text() == "nan" ||
      ui->label->text() == "inf")
    ui->label->setText("");
  else if (button->text() == "/" || button->text() == "^" ||
           button->text() == "*" || button->text() == "+" ||
           button->text() == "-" || button->text() == '%') {
    if (!fl)
      new_label = (ui->label->text() + button->text());
    else
      new_label = (ui->label->text());
  } else if (button->text() == "√")
    new_label = (ui->label->text() + "sqrt(");
  else if (strstr(butom, but) != NULL)
    new_label = (ui->label->text() + button->text() + '(');
  else if (button->text() == "AC")
    clear_graf();
  else if (button->text() == "OFF")
    MainWindow::close();
  else if (button->text() == "Backspace") {
    new_label = ui->label->text();
    backspace(&new_label);
  } else if (button->text() == ".") {
    if (!flag_num)
      new_label = (ui->label->text() + ".");
    else
      new_label = (ui->label->text());
  } else if (button->text() == '=') {
    clear_graf();
    char buffer[256] = {0};
    strcpy(buffer, ui->label->text().toUtf8().data());
    if (strchr(buffer, 'x') != NULL) {
      graf_plot(buffer, &new_label);
    } else if (!flag_1()) {
      solv(buffer, &err, &result);
      if (!err && !flag_1())
        result_print(&new_label, result);
      else
        new_label = "error";
    }
    /*else new_label = (ui->label->text() + button->text());*/}
   else
      new_label = (ui->label->text() + button->text());
    ui->label->setText(new_label);
}
double MainWindow::graf_painter(char* str, double x) {
    char buf[400] = {0};
    char num[50] = {0};
    sprintf(num, "(%lf)", x);
    int len = strlen(num);
    char* p_buf = buf;
    while (*str != 0) {
      if (*str == 'x') {
        for (int i = 0; i < len; i++) {
          *p_buf = num[i];
          p_buf++;
        }

      } else {
        *p_buf = *str;
        p_buf++;
      }
      str++;
    }
    int err = 0;
    double res = 0;
    solv(buf, &err, &res);
    return res;
}
void MainWindow::on_lineEdit_editingFinished() {
    float x = ui->lineEdit->text().toFloat();

    ui->widget->xAxis->setRange(-x, x);
}
void MainWindow::on_lineEdit_2_editingFinished() {
    float x = ui->lineEdit_2->text().toFloat();
    ui->widget->yAxis->setRange(-x, x);
}
void MainWindow::graf_plot(char* buffer, QString* new_label) {
    float xs = ui->lineEdit->text().toFloat();
    double h = xs / 200 * 2;
    double f = ui->lineEdit->text().toFloat() * (-1.0);
    double ff = -f;
    float s = ui->lineEdit_3->text().toFloat();
    char s_[100] = {0};
    strcpy(s_, ui->lineEdit_3->text().toUtf8().data());
    if (s_[0] == 'x') {
      while (f < ff) {
        f = f + h;
        y.push_back(graf_painter(buffer, (double)f));
        x.push_back(f);
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
      ui->widget->replot();
      *new_label = ui->label->text();
    } else {
      *new_label = QString::number(graf_painter(buffer, s), 'f', 6);
    }
}
void MainWindow::clear_graf() {
    x.clear();
    y.clear();
    ui->widget->clearGraphs();
    ui->widget->replot();
}
void MainWindow::result_print(QString* new_label, double result) {
    if (result > 100000000)
      *new_label = QString::number(result, 'f', 0);
    else if (result > 1000000)
      *new_label = QString::number(result, 'f', 2);
    else if (result <= 0.000001)
      *new_label = QString::number(result, 'f', 9);
    else
      *new_label = QString::number(result, 'f', 6);
}
void MainWindow::backspace(QString* new_label) {
    char buffer_1[256] = {0}, oper[12] = "+-/*)%  \0";
    strcpy(buffer_1, ui->label->text().toUtf8().data());
    int len = strlen(buffer_1);
    int len_chop = 0;
    for (int i = len - 1; i >= 0; i--) {
      for (int j = 9; j >= 0; j--) {
        if (!len_chop && buffer_1[i] == oper[j]) {
          len_chop = i;
        };
      }
    }
    new_label->chop(len - len_chop);
}
float MainWindow::on_lineEdit_3_editingFinished() {
    float s = ui->lineEdit_3->text().toFloat();
    return s;
}

void MainWindow::on_pushButton_35_clicked() { credit.show(); }
