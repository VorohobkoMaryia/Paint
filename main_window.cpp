#include <QPainter>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QMouseEvent>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include <QImage>

#include "main_window.h"
#include "canvas.h"
#include "panel.h"

MainWindow* MainWindow::instance{};

MainWindow::MainWindow() : canvas(new Canvas(this)), panel(new Panel(this)) {
  instance = this;
  setCentralWidget(new QWidget());
  auto* layout = new QGridLayout(centralWidget());
  layout->addWidget(canvas, 0,0,2,2);
  canvas->setAutoFillBackground(true);
  canvas->setPalette(QPalette(Qt::white));
  layout->addWidget(panel, 0, 2, 1, 1);
  panel->setFixedSize(300, 300);
  canvas->setMinimumSize(500,300);

  resize(1580, 790);
  setMenuBar(new QMenuBar());
  statusBar()->setStyleSheet(
      "QStatusBar { background-color: rgba(50, 50, 50, 50)}");

  Connect();
  setWindowTitle("Paint");
}

void MainWindow::Connect() {
  connect(&color_dialog, SIGNAL(colorSelected(const QColor&)),
          this, SLOT(ChangeColor(const QColor&)));

  auto* file_menu = new QMenu("Загрузить");
  menuBar()->addMenu(file_menu);
  auto* figure_menu = new QMenu("Инструмент");
  menuBar()->addMenu(figure_menu);
  auto settings_menu = new QMenu("Настройки");
  menuBar()->addMenu(settings_menu);

  connect(file_menu->addAction("Загрузить картинку из файла"), SIGNAL(triggered(bool)),
          this, SLOT(PictureFromFile()));
  connect(file_menu->addAction("Загрузить картинку в файл"), SIGNAL(triggered(bool)),
          this, SLOT(PictureToFile()));
  connect(figure_menu->addAction("Линия"), SIGNAL(triggered(bool)),
          canvas, SLOT(ChooseLine()));
  connect(figure_menu->addAction("Линия произвольной конфигурации"), SIGNAL(triggered(bool)),
          canvas, SLOT(ChooseCurve()));
  connect(figure_menu->addAction("Круг"), SIGNAL(triggered(bool)),
          canvas, SLOT(ChooseCircle()));
  connect(figure_menu->addAction("Прямоугольник"), SIGNAL(triggered(bool)),
          canvas, SLOT(ChooseRectangle()));
  connect(figure_menu->addAction("Назад"), SIGNAL(triggered(bool)),
          this, SLOT(Back()));
  connect(settings_menu->addAction("Изменить толщину"), SIGNAL(triggered(bool)),
          this, SLOT(ChangePenWidthPressed()));
  connect(settings_menu->addAction("Изменить цвет"), SIGNAL(triggered(bool)),
          &color_dialog, SLOT(show()));
}

void MainWindow::ChangeColor(const QColor& col) {
  color = col;
}

void MainWindow::Back() {
  if (!figures.empty()) {
    if (dynamic_cast<FreeDrawing*>(figures.back()) == nullptr) {
      delete panel->list.takeItem(panel->list.row(fig_to_item[figures.back()]));
      fig_to_item.erase(figures.back());
    }
    delete figures.back();
    figures.pop_back();
    panel->list.setCurrentItem(nullptr);
    Repaint();
  }
}

void MainWindow::AddFigure(Figure* figure) {
  static uint64_t counter = 0;
  figures.push_back(figure);
  if (dynamic_cast<FreeDrawing*>(figure) != nullptr) {
    return;
  }
  auto item = new Item("Фигура #" + QString::number(counter++) + "(" +
      Figure::names.at(figure->Type()) + ")", figure);
  panel->list.insertItem(0, item);
  fig_to_item[figure] = item;
  panel->list.setCurrentItem(nullptr);
}

MainWindow::~MainWindow() {
  for (auto& figure: figures) {
    delete figure;
  }
}

QColor MainWindow::GetCurrentColor() {
  return color;
}

int MainWindow::GetCurrentPenWidth() {
  return pen_width;
}


void MainWindow::PictureFromFile() {
  QString file = QFileDialog::getOpenFileName(this, "", "", tr("Images (*.png *.xpm *.jpg *jpeg *bmp)"));
  if (!file.isNull()) {
    loaded_picture = QPixmap(file);
    canvas->ChoseFigure(image_t);
  }
}

void MainWindow::PictureToFile() {
  QImage image(1500, 1500 * Figure::max_y / Figure::max_x, QImage::Format_RGB32);
  image.fill(Qt::white);
  Repaint(&image);
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                  QString(),
                                                  tr("Images (*.png)"));
  if (!fileName.isEmpty()) {
    image.save(fileName);
  }
}

void MainWindow::Repaint(QPaintDevice* paint_device) {
  QPainter painter(paint_device);
  for (int i = 0; i < figures.size(); i++) {
    painter.setPen(QPen(figures[i]->GetColor(), figures[i]->GetPenWidth()));
    figures[i]->Draw(painter);
  }
}

void MainWindow::ChangePenWidthPressed() {
  pen_width = QInputDialog::getInt(this, "Толщина пера", "Установите значение толщины", pen_width, 1, 100);
}

QPixmap MainWindow::GetLoadedPicture() {
  return loaded_picture;
}

void MainWindow::ShowMessageInStatusBar(const QString& message) {
  statusBar()->showMessage(message);
}

void MainWindow::DeleteFigure(Figure* figure) {
  figures.erase(std::find(figures.begin(), figures.end(), figure));
}

Figure* MainWindow::ChosenFigure() {
  auto item = dynamic_cast<Item*>(panel->list.item(panel->list.currentRow()));
  if (item == nullptr) {
    return nullptr;
  }
  return item->figure;
}

void MainWindow::Repaint() {
  canvas->repaint();
}
