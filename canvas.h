#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

#include "type_of_figure.h"

class MainWindow;

class Canvas : public QWidget {
  Q_OBJECT
 public:
  explicit Canvas(MainWindow* main_window);

  void mousePressEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent* ) override;
  void paintEvent(QPaintEvent *event) override;

  void ChoseFigure(TypeOfFigure type);
  QPointF FromScreenCoord(const QPoint& point);

 public slots:
  void ChooseLine();
  void ChooseCurve();
  void ChooseCircle();
  void ChooseRectangle();

 private:
  MainWindow* main_window;

  TypeOfFigure cur_figure_type;
  QPointF last_click_pos;
  QPointF last_move_pos;

  friend class MainWindow;
};

#endif //CANVAS_H
