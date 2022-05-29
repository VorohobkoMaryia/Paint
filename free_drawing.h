#ifndef FREE_DRAWING_H
#define FREE_DRAWING_H

#include "figure.h"

class FreeDrawing : public Figure {
 public:
  FreeDrawing(const QPointF& point);
  void AddPoint(const QPointF& point);
  void Draw(QPainter& painter) override;
  virtual void MoveBy(const QPointF& point);

 private:
  std::vector<QPointF> points;
};

#endif //FREE_DRAWING_H
