#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMenuBar>
#include <QMainWindow>
#include <QColorDialog>
#include <QSlider>
#include <QInputDialog>
#include <QMessageBox>

#include "figure.h"
#include "circle.h"
#include "free_drawing.h"
#include "rectangle.h"
#include "image.h"
#include "line.h"
#include "free_drawing.h"
#include "type_of_figure.h"

class Canvas;
class Panel;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  void AddFigure(Figure* figure);

  template<class Fig>
  Fig* GetLastFigure() {
    if (figures.empty()) {
        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setWindowTitle("Error");
        error.setText("No Figures");
        error.exec();
    }
    return dynamic_cast<Fig*>(figures.back());
  }

  void DeleteFigure(Figure* figure);
  void ShowMessageInStatusBar(const QString& message);
  void Repaint(QPaintDevice* paint_device);
  void Connect();
  QColor GetCurrentColor();
  int GetCurrentPenWidth();
  QPixmap GetLoadedPicture();
  Figure* ChosenFigure();
  void Repaint();

  ~MainWindow() override;

 public slots:
  void ChangePenWidthPressed();
  void ChangeColor(const QColor &);
  void PictureFromFile();
  void PictureToFile();
  void Back();

 public:
  static MainWindow* instance;

  Canvas* canvas;
  Panel* panel;

  std::vector<Figure*> figures{};
  int pen_width = 2;
  QColor color = Qt::black;
  QPixmap loaded_picture{};
  QColorDialog color_dialog{};

  std::unordered_map<Figure*, QListWidgetItem*> fig_to_item{};

  friend class Figure;
};

#endif //MAIN_WINDOW_H
