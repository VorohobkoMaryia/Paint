#include <QMouseEvent>

#include "canvas.h"
#include "main_window.h"

void Canvas::ChoseFigure(TypeOfFigure kind) {
  static const QString prefix = "Текущий инструмент: ";
  cur_figure_type = kind;
  main_window->ShowMessageInStatusBar(prefix + Figure::names.at(kind));
}

void Canvas::ChooseLine() {
  ChoseFigure(line_t);
}

void Canvas::ChooseCurve() {
  ChoseFigure(free_drawing_t);
}

void Canvas::ChooseCircle() {
  ChoseFigure(circle_t);
}

void Canvas::ChooseRectangle() {
  ChoseFigure(rectangle_t);
}

void Canvas::mousePressEvent(QMouseEvent* event) {
  last_click_pos = FromScreenCoord(event->pos());
  last_move_pos = last_click_pos;
  if (main_window->ChosenFigure() != nullptr) {
    return;
  }
  switch (cur_figure_type) {
    case line_t:
      main_window->AddFigure(new Line(last_click_pos.x(), last_click_pos.y(),
                                      last_click_pos.x(), last_click_pos.y()));
      break;
    case circle_t:
      main_window->AddFigure(new Circle(last_click_pos.x(), last_click_pos.y(), 0));
      break;
    case rectangle_t:
      main_window->AddFigure(new Rectangle(last_click_pos.x(), last_click_pos.y(), 0, 0));
      break;
    case image_t:
      main_window->AddFigure(new Image(last_click_pos.x(), last_click_pos.y(), 0, 0,
                                       main_window->GetLoadedPicture()));
      break;
    case free_drawing_t:
      main_window->AddFigure(new FreeDrawing(last_click_pos));
      break;
  }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
  QPointF cur_pos = FromScreenCoord(event->pos());
  auto chosen_figure = main_window->ChosenFigure();
  if (chosen_figure == nullptr) {
    switch (cur_figure_type) {
      case line_t: {
        *(main_window->GetLastFigure<Line>()) = Line(last_click_pos.x(), last_click_pos.y(),
                                                     cur_pos.x(), cur_pos.y());
        break;
      }
      case circle_t: {
        double dx = cur_pos.x() - last_click_pos.x();
        double dy = cur_pos.y() - last_click_pos.y();
        *(main_window->GetLastFigure<Circle>()) = Circle(last_click_pos.x(),
                                                         last_click_pos.y(),
                                                         sqrt(dx * dx + dy * dy));
        break;
      }
      case rectangle_t: {
        *(main_window->GetLastFigure<Rectangle>()) = Rectangle(last_click_pos.x(), last_click_pos.y(),
                                                               cur_pos.x() - last_click_pos.x(),
                                                               cur_pos.y() - last_click_pos.y());
        break;
      }
      case image_t: {
        *(main_window->GetLastFigure<Image>()) = Image(last_click_pos.x(), last_click_pos.y(),
                                                       cur_pos.x() - last_click_pos.x(),
                                                       cur_pos.y() - last_click_pos.y(),
                                                       main_window->GetLoadedPicture());
        break;
      }
      case free_drawing_t: {
        main_window->GetLastFigure<FreeDrawing>()->AddPoint(FromScreenCoord(event->pos()));
        break;
      }
    }
  } else {
    chosen_figure->MoveBy(cur_pos - last_move_pos);
  }
  last_move_pos = cur_pos;
  repaint();
}

void Canvas::paintEvent(QPaintEvent* event) {
  main_window->Repaint(this);
  QWidget::paintEvent(event);
}

QPointF Canvas::FromScreenCoord(const QPoint& point) {
  return {(double) point.x() / width() * Figure::max_x, (double) point.y() / height() * Figure::max_y};
}

Canvas::Canvas(MainWindow* main_window) : main_window(main_window) {
  ChoseFigure(free_drawing_t);
}
