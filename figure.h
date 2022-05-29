#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <utility>
#include <QPainter>
#include <QListWidgetItem>
#include <cmath>
#include "type_of_figure.h"


class Figure {
 public:
  Figure();
  virtual void Draw(QPainter& painter) = 0;
  virtual ~Figure() = default;
  virtual void MoveBy(const QPointF& point) = 0;
  QColor GetColor() const;
  int GetPenWidth() const;
  TypeOfFigure Type() const;

  static const double max_x;
  static const double max_y;
  static const std::map<TypeOfFigure, QString> names;

 protected:
  QColor color;
  int pen_width;
  int angle = 0;
  double scale = 1;
  TypeOfFigure type;

  friend class Panel;
};

#endif //FIGURE_H
