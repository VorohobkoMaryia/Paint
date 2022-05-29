#ifndef IMAGE_H
#define IMAGE_H

#include "figure.h"

class Image : public Figure {
 public:
  Image(double x, double y, double w, double h, const QPixmap& pixmap);
  void Draw(QPainter& painter) override;
  void MoveBy(const QPointF& point) override;

 private:
  double x, y, width, height;
  QPixmap pixmap;
};

#endif //IMAGE_H

