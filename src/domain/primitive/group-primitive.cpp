#include "group-primitive.h"

GroupPrimitive::GroupPrimitive(Container *con_1, Container *con_2) : Primitive() {
  this->SetTypeName(MEL_GROUP);
  container_1_ = con_1;
  container_2_ = con_2;
}

void GroupPrimitive::Draw() {
  container_1_->Draw(GetPaintMode());
  container_2_->Draw(GetPaintMode());
}

void GroupPrimitive::SyncData() {
  container_1_->GetPrimitive()->SetIdColor(this->GetIdColor());
  //   container1->GetPrimitive()->SetColor(this->GetColor());

  container_2_->GetPrimitive()->SetIdColor(this->GetIdColor());
  //  container2->GetPrimitive()->SetColor(this->GetColor());

  if (container_1_->GetPrimitive()->GetTypeName() == MEL_GROUP) {
    GroupPrimitive *gp = dynamic_cast<GroupPrimitive *>(container_1_->GetPrimitive());
    gp->SyncData();

  }
  if (container_2_->GetPrimitive()->GetTypeName() == MEL_GROUP) {
    GroupPrimitive *gp = dynamic_cast<GroupPrimitive *>(container_2_->GetPrimitive());
    gp->SyncData();
  }
}
