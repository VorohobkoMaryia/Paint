#include "image.h"

Image::Image(double x, double y, double w, double h, const QPixmap& pixmap)
    : x(std::min(x, x + w)), y(std::min(y, y + h)),
      width(fabs(w)), height(fabs(h)), pixmap(pixmap) {
  type = image_t;
}

void Image::Draw(QPainter& painter) {
  double x_coeff = scale / max_x * painter.window().width();
  double y_coeff = scale / max_y * painter.window().height();
  painter.translate((x + width / 2) / max_x * painter.window().width(),
                    (y + height / 2) / max_y * painter.window().height());
  painter.rotate(angle);
  painter.drawPixmap(lround(-width / 2 * x_coeff), lround(-height / 2 * y_coeff),
                    lround(width * x_coeff), lround(height * y_coeff), pixmap);
  painter.rotate(-angle);
  painter.translate(-(x + width / 2) / max_x * painter.window().width(),
                    -(y + height / 2) / max_y * painter.window().height());
}

void Image::MoveBy(const QPointF& point) {
  x += point.x();
  y += point.y();
}
