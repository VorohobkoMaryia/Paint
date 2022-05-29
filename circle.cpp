#include "circle.h"

Circle::Circle(double x, double y, double r)
    : x(x), y(y), r(r) {
  type = circle_t;
}

void Circle::Draw(QPainter& painter) {
  int window_width = painter.window().width();
  int window_height = painter.window().height();
  painter.drawEllipse((x - r * scale) / max_x * window_width,
                      (y - r * scale) / max_y * window_height,
                      2 * r * scale / max_x * window_width,
                      2 * r * scale / max_y * window_height);
}

void Circle::MoveBy(const QPointF& point) {
  x += point.x();
  y += point.y();
}

