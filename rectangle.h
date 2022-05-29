#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure {
 public:
  Rectangle(double x, double y, double w, double h);
  void Draw(QPainter& painter) override;
  void MoveBy(const QPointF& point) override;

 private:
  double x, y, width, height;
};

#endif //RECTANGLE_H
