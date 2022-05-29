#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

#include "figure.h"

class MainWindow;

class Item : public QListWidgetItem {
 public:
  Item(const QString& str, Figure* figure) : QListWidgetItem(str), figure(figure) {}
  Figure* figure;
  ~Item() override = default;
};

class Panel : public QWidget {
  Q_OBJECT
 public:
  Panel(MainWindow* main_window);

 public slots:
  void ColorButtonClicked();
  void DeleteButtonClicked();
  void SetNewAngle(int angle);
  void SetNewScale(int percent);
  void DoneButtonClicked();
  void NewRowChosen(int row);

 private:
  MainWindow* main_window;

  QGridLayout layout{this};
  QPushButton done_button{"Готово (перейти к рисованию)", this};
  QListWidget list{this};
  QPushButton color_button{"Задать цвет", this};
  QPushButton delete_button{"Удалить", this};
  QLabel rotate_label{"Задать поворот (в градусах)", this};
  QSlider rotate_slider{Qt::Horizontal, this};
  QLabel size_label{"Задать размер в %", this};
  QSlider size_slider{Qt::Horizontal, this};

  friend class MainWindow;
};

#endif //PANEL_H
