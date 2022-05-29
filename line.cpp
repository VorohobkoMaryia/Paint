#include "line.h"

Line::Line(double x1, double y1, double x2, double y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
  type = line_t;
}

void Line::Draw(QPainter& painter) {
  double x_coeff = scale / max_x * painter.window().width();
  double y_coeff = scale / max_y * painter.window().height();
  painter.translate((x1 + x2) / 2 / max_x * painter.window().width(),
                    (y1 + y2) / 2 / max_y * painter.window().height());
  painter.rotate(angle);
  painter.drawLine(-(x2 - x1) / 2 * x_coeff, -(y2 - y1) / 2 * y_coeff,
                   (x2 - x1) / 2 * x_coeff, (y2 - y1) / 2 * y_coeff);
  painter.rotate(-angle);
  painter.translate(-(x1 + x2) / 2 / max_x * painter.window().width(),
                    -(y1 + y2) / 2 / max_y * painter.window().height());


}

void Line::MoveBy(const QPointF& point) {
  x1 += point.x();
  x2 += point.x();
  y1 += point.y();
  y2 += point.y();
}
