#include "intersect-primitive.h"

IntersectPrimitive::IntersectPrimitive(Container *con_1, Container *con_2) : GroupPrimitive(con_1, con_2) {
  this->SetTypeName(MEL_INTERSECT);
  container_1_ = con_1;
  container_2_ = con_2;
}

void IntersectPrimitive::Draw() {
  glEnable(GL_STENCIL_TEST);                          // буфер трафарета
  glStencilFunc(GL_NEVER, 1, 1);
  glStencilOp(GL_REPLACE, GL_KEEP, GL_REPLACE);
  container_1_->Draw(GetPaintMode());
  glStencilFunc(GL_NEVER, 1, 1);
  glStencilOp(GL_INCR, GL_KEEP, GL_REPLACE);
  container_2_->Draw(GetPaintMode());

  glStencilFunc(GL_EQUAL, 2, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  container_1_->Draw(GetPaintMode());
  glStencilFunc(GL_EQUAL, 2, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  container_2_->Draw(GetPaintMode());
  glDisable(GL_STENCIL_TEST);                          // буфер трафарета
}

void IntersectPrimitive::SyncData() {
  container_1_->GetPrimitive()->SetIdColor(this->GetIdColor());
  container_1_->GetPrimitive()->SetColor(this->GetColor());

  container_2_->GetPrimitive()->SetIdColor(this->GetIdColor());
  container_2_->GetPrimitive()->SetColor(this->GetColor());

  if (container_1_->GetPrimitive()->GetTypeName() == MEL_INTERSECT) {
    IntersectPrimitive *gp = dynamic_cast<IntersectPrimitive *>(container_1_->GetPrimitive());
    gp->SyncData();

  }
  if (container_2_->GetPrimitive()->GetTypeName() == MEL_INTERSECT) {
    IntersectPrimitive *gp = dynamic_cast<IntersectPrimitive *>(container_2_->GetPrimitive());
    gp->SyncData();
  }
}
