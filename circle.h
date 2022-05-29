#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure {
 public:
  Circle(double x, double y, double r);
  void Draw(QPainter& painter) override;
  void MoveBy(const QPointF& point) override;

 private:
  double x, y, r;
};

#endif //CIRCLE_H
