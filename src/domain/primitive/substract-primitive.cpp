#include "substract-primitive.h"

SubstractPrimitive::SubstractPrimitive(Container *con_1, Container *con_2) : GroupPrimitive(con_1, con_2) {
  this->SetTypeName(MEL_SUBSTRACT);
  container_1_ = con_1;
  container_2_ = con_2;
}

void SubstractPrimitive::Draw() {
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_NEVER, 1, 1); // значение mask не используется
  glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

  container_2_->Draw(GetPaintMode());

  glStencilFunc(GL_EQUAL, 0, 1); // значение mask не используется
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

  container_1_->Draw(GetPaintMode());
  glDisable(GL_STENCIL_TEST);
}

void SubstractPrimitive::SyncData() {
  container_1_->GetPrimitive()->SetIdColor(this->GetIdColor());

  if (container_1_->GetPrimitive()->GetTypeName() == MEL_SUBSTRACT) {
    SubstractPrimitive *gp = dynamic_cast<SubstractPrimitive *>(container_1_->GetPrimitive());
    gp->SyncData();
  }
}
