#include "painting-zone.h"

PaintingZone::PaintingZone(QWidget *parent) : QWidget(parent) {
  wid_top_ = new GLWidget(parent);
  wid_perspective_ = new GLWidget(parent);
  wid_front_ = new GLWidget(parent);
  wid_right_ = new GLWidget(parent);
  sp_global_ = new QSplitter(Qt::Vertical);
  sp_top_ = new QSplitter(Qt::Horizontal);
  sp_down_ = new QSplitter(Qt::Horizontal);
  lay_global_ = new QVBoxLayout();
  wid_top_->SetProjection(VIEW_TOP);
  wid_perspective_->SetProjection(VIEW_PERSPECTIVE);
  wid_front_->SetProjection(VIEW_FRONT);
  wid_right_->SetProjection(VIEW_RIGHT);
  SaveProjectionLastState();
  sp_top_->addWidget(wid_top_);
  sp_top_->addWidget(wid_perspective_);
  sp_down_->addWidget(wid_front_);
  sp_down_->addWidget(wid_right_);
  sp_global_->addWidget(sp_top_);
  sp_global_->addWidget(sp_down_);
  lay_global_->addWidget(sp_global_);
  this->setLayout(lay_global_);
}

void PaintingZone::Update() {
  wid_perspective_->repaint();
  wid_top_->repaint();
  wid_front_->repaint();
  wid_right_->repaint();
}

void PaintingZone::SetMaximum(int i) {
  switch (i) {
    case VIEW_FRONT:SetAllUnvisible(true);
      wid_front_->setVisible(true);
      break;
    case VIEW_TOP:SetAllUnvisible(true);
      wid_top_->setVisible(true);
      break;
    case VIEW_RIGHT:SetAllUnvisible(true);
      wid_right_->setVisible(true);
      break;
    case VIEW_PERSPECTIVE:SetAllUnvisible(true);
      wid_perspective_->setVisible(true);
      break;
  }
}

void PaintingZone::SetAllUnvisible(bool a) {
  wid_top_->setHidden(a);
  wid_front_->setHidden(a);
  wid_right_->setHidden(a);
  wid_perspective_->setHidden(a);
}

void PaintingZone::SaveProjectionLastState() {
  wid_perspective_->SaveLastState();
  wid_top_->SaveLastState();
  wid_front_->SaveLastState();
  wid_right_->SaveLastState();
}

void PaintingZone::LoadProjectionLastState() {
  wid_perspective_->LoadLastState();
  wid_top_->LoadLastState();
  wid_front_->LoadLastState();
  wid_right_->LoadLastState();
}
