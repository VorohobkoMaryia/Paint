#include "figure.h"
#include "main_window.h"
#include <iostream>

const double Figure::max_x = 5;
const double Figure::max_y = 3;

const std::map<TypeOfFigure, QString> Figure::names =
    {
      {line_t, "Линия"},
      {image_t, "Изображение"},
      {rectangle_t, "Прямоугольник"},
      {free_drawing_t, "Линия произвольной конфигурации"},
      {circle_t, "Круг"}
    };

Figure::Figure() {
  color = MainWindow::instance->GetCurrentColor();
  pen_width = MainWindow::instance->GetCurrentPenWidth();
}

QColor Figure::GetColor() const {
  return color;
}

int Figure::GetPenWidth() const {
  return pen_width;
}

TypeOfFigure Figure::Type() const {
  return type;
}
