#include "src/domain/primitive.h"

Primitive::Primitive() : Element() {
  id_colors_arr_ = new QStack<Mcolor *>();
}

void Primitive::Apply(int mode) {
  SetPaintMode(mode);
  Draw();
}

void Primitive::SetIdColor(Mcolor *color) {
  id_colors_arr_->push(color);
  id_color_ = color;
}

void Primitive::SetColor(Mcolor *color) {
  this->color_ = color;
}

Mcolor *Primitive::GetIdColor() {
  return this->id_color_;
}

Mcolor *Primitive::GetColor() {
  return this->color_;
}

void Primitive::SetPaintMode(int mode) {
  this->paint_mode_ = mode;
}

int Primitive::GetPaintMode() {
  return paint_mode_;
}

void Primitive::Draw() {

}
