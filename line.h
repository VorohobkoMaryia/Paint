#ifndef LINE_H
#define LINE_H

#include "figure.h"

class Line : public Figure {
 public:
  Line(double x1, double y1, double x2, double y2);
  void Draw(QPainter& painter) override;
  void MoveBy(const QPointF& point) override;

 private:
  double x1, y1, x2, y2;
};

#endif //LINE_H
