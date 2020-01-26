#include <src/domain/primitive/sphere.h>
#include <src/domain/primitive/cube.h>
#include <src/domain/primitive/pyramid.h>
#include <src/domain/primitive/group-primitive.h>
#include <src/domain/primitive/substract-primitive.h>
#include <src/domain/primitive/intersect-primitive.h>
#include "work.h"
#include "src/gui/main-window.h"
#include "QDebug"

Work::Work(QWidget *parent) {
  p_mw_ = dynamic_cast<MainWindow *>(parent);
  element_list_ = new QList<Container *>;
  current_free_id_ = 0;
  current_free_color_[0] = 0;
  current_free_color_[1] = 0;
  current_free_color_[2] = 0;
  for_group_id_[0] = -1;
  for_group_id_[1] = -1;

  quadric_ = gluNewQuadric();
}

void Work::DrawWork(bool mode) {
  glPushMatrix();

  for (int i = 0; i < element_list_->size(); i++) {
    Container *cont = element_list_->at(i);
    cont->Draw(mode);
    switch (cont->GetPrimitive()->GetTypeName()) {
      case MEL_PRIMITIVE:
      case MEL_CUBE:
      case MEL_PYRAMID:
      case MEL_SPHERE:
      case MEL_GROUP:
      case MEL_CYLINDER:glPopMatrix();
        glPushMatrix();
      default:break;
    }
  }
  glPopMatrix();
}

void Work::AddPrimitive(int i, QPoint pos) {
  switch (i) {
    case MEL_SPHERE: {
      Sphere *sphere = new Sphere(quadric_, 1.0f);
      sphere->SetGid(GenerateGid());
      sphere->SetIdColor(GenerateIdColor());
      sphere->SetColor(GenerateColor());
      element_list_->append(new Container(sphere));
      break;
    }
    case MEL_CUBE: {
      Cube *cube = new Cube(1.0f);
      cube->SetGid(GenerateGid());
      cube->SetIdColor(GenerateIdColor());
      cube->SetColor(GenerateColor());
      if (pos.x() != 0 && pos.y() != 0)
        element_list_->append(new Container(cube, new Translate(pos.x(), pos.y(), 0)));
      else
        element_list_->append(new Container(cube));
      break;
    }
    case MEL_PYRAMID: {
      Pyramid *pyramid = new Pyramid(2.0f);
      pyramid->SetGid(GenerateGid());
      pyramid->SetIdColor(GenerateIdColor());
      pyramid->SetColor(GenerateColor());
      element_list_->append(new Container(pyramid));
      break;
    }
    case MEL_CYLINDER: {

      break;
    }
  }
}

void Work::DeletePrimitive(long index) {
  element_list_->removeAt(index);
}

void Work::AddAction(int i) {
  switch (i) {
    case ACTION_GROUP: {
      Container *obj1 = element_list_->at(GetGroupObj1());
      Container *obj2 = element_list_->at(GetGroupObj2());

      GroupPrimitive *groupPrim = new GroupPrimitive(obj1, obj2);
      groupPrim->SetGid(GenerateGid());
      groupPrim->SetIdColor(GenerateIdColor());
      groupPrim->SetColor(GenerateColor());
      groupPrim->SyncData();
      element_list_->removeOne(obj1);
      element_list_->removeOne(obj2);
      element_list_->append(new Container(groupPrim));
      break;
    }
    case ACTION_SUBSTRACT: {
      Container *obj1 = element_list_->at(GetGroupObj1());
      Container *obj2 = element_list_->at(GetGroupObj2());

      SubstractPrimitive *substractPrim = new SubstractPrimitive(obj1, obj2);
      substractPrim->SetGid(GenerateGid());
      substractPrim->SetIdColor(GenerateIdColor());
      substractPrim->SetColor(GenerateColor());
      substractPrim->SyncData();
      element_list_->removeOne(obj1);
      element_list_->removeOne(obj2);
      element_list_->append(new Container(substractPrim));
      break;
    }
    case ACTION_TRANSLATE: {
      Translate *translate = new Translate(0, 0, 0);
      translate->SetGid(GenerateGid());
      element_list_->at(p_mw_->selected_prim_)->AddTranslate(translate);
      break;
    }
    case ACTION_SCALE:
    case ACTION_STRETCH: {
      Scale *scale = new Scale(1, 1, 1);
      scale->SetGid(GenerateGid());
      element_list_->at(p_mw_->selected_prim_)->AddScale(scale);
      break;
    }

    case ACTION_ROTATE: {
      Rotate *rotate = new Rotate(0, 0, 0);
      rotate->SetGid(GenerateGid());
      element_list_->at(p_mw_->selected_prim_)->AddRotate(rotate);
      break;
    }
    case ACTION_INTERSECT: {
      Container *obj1 = element_list_->at(GetGroupObj1());
      Container *obj2 = element_list_->at(GetGroupObj2());

      IntersectPrimitive *intersectPrim = new IntersectPrimitive(obj1, obj2);
      intersectPrim->SetGid(GenerateGid());
      intersectPrim->SetIdColor(GenerateIdColor());
      intersectPrim->SetColor(GenerateColor());
      intersectPrim->SyncData();
      element_list_->removeOne(obj1);
      element_list_->removeOne(obj2);
      element_list_->append(new Container(intersectPrim));
      break;
    }
    default:break;
  }
}

long Work::GenerateGid() {
  return current_free_id_++;
}

Mcolor *Work::GenerateIdColor() {
  int arr[3] = {0};

  if (this->current_free_color_[2] < 255) {
    arr[2] = current_free_color_[2]++;
  } else if (this->current_free_color_[1] < 255) {
    arr[1] = current_free_color_[1]++;
  } else if (this->current_free_color_[0] < 255) {
    arr[0] = current_free_color_[0]++;
  }
  Mcolor *color;
  color = new Mcolor(arr[0], arr[1], arr[2]);
  return color;
}

Mcolor *Work::GenerateColor() {
  int arr[3] = {0};
  Mcolor *color;
  for (int i = 0; i < 3; i++) {
    arr[i] = (0 + rand() % 255);
    srand(time(NULL));
  }
  color = new Mcolor(arr[0], arr[1], arr[2]);
  return color;
}

QList<Container *> *Work::GetList() {
  return element_list_;
}

void Work::SetGroupObj1(long i) {
  for_group_id_[0] = i;
}

void Work::SetGroupObj2(long i) {
  for_group_id_[1] = i;
}

long Work::GetGroupObj1() {
  return for_group_id_[0];
}

long Work::GetGroupObj2() {
  return for_group_id_[1];
}
