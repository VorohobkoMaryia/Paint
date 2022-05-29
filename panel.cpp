#include "panel.h"
#include "main_window.h"
#include <QColorDialog>

Panel::Panel(MainWindow* main_window) : main_window(main_window) {
  layout.addWidget(&done_button);
  layout.addWidget(&list);
  layout.addWidget(&color_button);
  layout.addWidget(&delete_button);
  layout.addWidget(&rotate_label);
  layout.addWidget(&rotate_slider);
  layout.addWidget(&size_label);
  layout.addWidget(&size_slider);

  rotate_slider.setRange(0, 360);
  size_slider.setRange(0, 700);

  connect(&color_button, SIGNAL(clicked(bool)), this, SLOT(ColorButtonClicked()));
  connect(&delete_button, SIGNAL(clicked(bool)), this, SLOT(DeleteButtonClicked()));
  connect(&rotate_slider, SIGNAL(valueChanged(int)), this, SLOT(SetNewAngle(int)));
  connect(&size_slider, SIGNAL(valueChanged(int)), this, SLOT(SetNewScale(int)));
  connect(&done_button, SIGNAL(clicked(bool)), this, SLOT(DoneButtonClicked()));
  connect(&list, SIGNAL(currentRowChanged(int)), this, SLOT(NewRowChosen(int)));

  NewRowChosen(-1);
}

void Panel::ColorButtonClicked() {
  Item* cur_item = dynamic_cast<Item*>(list.item(list.currentRow()));
  if (cur_item == nullptr) {
    return;
  }
  cur_item->figure->color = QColorDialog::getColor(cur_item->figure->GetColor(), main_window);
  main_window->Repaint();
}

void Panel::DeleteButtonClicked() {
  Item* cur_item = dynamic_cast<Item*>(list.takeItem(list.currentRow()));
  if (cur_item == nullptr) {
    return;
  }
  main_window->DeleteFigure(cur_item->figure);
  delete cur_item;
  list.setCurrentItem(nullptr);
  main_window->Repaint();
}

void Panel::SetNewAngle(int angle) {
  Item* cur_item = dynamic_cast<Item*>(list.currentItem());
  if (cur_item == nullptr) {
    return;
  }
  cur_item->figure->angle = angle;
  main_window->Repaint();
}

void Panel::SetNewScale(int percent) {
  Item* cur_item = dynamic_cast<Item*>(list.currentItem());
  if (cur_item == nullptr) {
    return;
  }
  cur_item->figure->scale = (double ) percent / 100;
  main_window->Repaint();
}

void Panel::DoneButtonClicked() {
  list.setCurrentItem(nullptr);
}

void Panel::NewRowChosen(int row) {
  if (row < 0) {
    size_slider.setValue(100);
    rotate_slider.setValue(0);
  } else {
    auto cur_item = dynamic_cast<Item*>(list.item(row));
    rotate_slider.setValue(cur_item->figure->angle);
    size_slider.setValue(lround(cur_item->figure->scale * 100));
  }
}
