#include "src/domain/container.h"

Container::Container(Primitive *prim) {
  primitive_ = prim;
  rotate_list_ = new QList<Rotate *>();
  translate_list_ = new QList<Translate *>();
  scale_list_ = new QList<Scale *>();
}

Container::Container(Primitive *prim, Translate *translate) {
  primitive_ = prim;
  rotate_list_ = new QList<Rotate *>();
  translate_list_ = new QList<Translate *>();
  scale_list_ = new QList<Scale *>();

  AddTranslate(translate);
}

void Container::AddTranslate(Translate *trans) {
  translate_list_->append(trans);
}

void Container::AddRotate(Rotate *rot) {
  rotate_list_->append(rot);
}

void Container::AddScale(Scale *scale) {
  scale_list_->append(scale);
}

QList<Translate *> *Container::GetTranslateList() {
  return translate_list_;
}

QList<Rotate *> *Container::GetRotateList() {
  return rotate_list_;
}

QList<Scale *> *Container::GetScaleList() {
  return scale_list_;
}

Translate *Container::GetTranslate() {
  return translate_list_->last();
}

Scale *Container::GetScale() {
  return scale_list_->last();
}

Rotate *Container::GetRotate() {
  return rotate_list_->last();
}

Primitive *Container::GetPrimitive() {
  return primitive_;
}

void Container::Draw(int mode) {
  for (int i = 0; i < translate_list_->size(); i++)
    translate_list_->at(i)->Apply(mode);

  for (int i = 0; i < rotate_list_->size(); i++)
    rotate_list_->at(i)->Apply(mode);

  for (int i = 0; i < scale_list_->size(); i++)
    scale_list_->at(i)->Apply(mode);

  primitive_->Apply(mode);
}

QDataStream &operator<<(QDataStream &out, const Container *painting) {
  //out << painting->GetPrimitive();
  //out << painting->GetRotateList();
  // out << painting->GetTranslate();
  //out << painting->GetScaleList();
  return out;
}
