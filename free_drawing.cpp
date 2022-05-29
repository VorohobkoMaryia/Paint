#include "free_drawing.h"

FreeDrawing::FreeDrawing(const QPointF& point) : points({point}) {
  type = free_drawing_t;
}

void FreeDrawing::AddPoint(const QPointF& point) {
  points.push_back(point);
}

void FreeDrawing::Draw(QPainter& painter) {
  int window_width = painter.window().width();
  int window_height = painter.window().height();
  std::vector<QPoint> points_screen_coordinates;
  points_screen_coordinates.resize(points.size());
  for (int i = 0; i < points.size(); i++) {
    points_screen_coordinates[i] = QPoint(points[i].x() / max_x * window_width,
                                          points[i].y() / max_y * window_height);
  }
  painter.drawPolyline(points_screen_coordinates.data(), points.size());
}

void FreeDrawing::MoveBy(const QPointF& point) {}
