#include "gl-widget.h"
#include "src/gui/painting-zone.h"
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include "src/gui/main-window.h"

//  Главные

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  // ПОЧИСТИТЬ!
  koef_ = 1;
  p_mw_ = dynamic_cast<MainWindow *>(parent);
  context_menu_primitive_ = new ContextMenu(MCM_PRIMITIVE, this);
  current_ortho_ = Ortho();
  //color_selected_prim = {0};
  this->selected_ = false;
  this->axes_ = true;
  this->plane_ = true;
  this->painting_mode_ = MODE_REAL;
  last_projection_ = 0;
  current_work_ = p_mw_->GetWork();
  curren_event_ = p_mw_->GetCurEvent();
  previous_event_ = p_mw_->GetPrevEvent();
  n_ = 0;
  x_rot_ = 0;
  y_rot_ = 0;
  z_rot_ = 0;
  x_translate_ = 0;
  y_translate_ = 0;
  z_translate_ = 0;
  g_scale_ = 1;
  current_pos_ = QPoint();
  last_pos_ = QPoint();
  combo_box_ = new QComboBox();
  lay_global_v_ = new QVBoxLayout();
  lay_global_h_ = new QHBoxLayout();
  combo_box_->addItem("Перспектива");
  combo_box_->addItem("Верх");
  combo_box_->addItem("Бок");
  combo_box_->addItem("Перед");
  combo_box_->addItem("Во весь экран");
  combo_box_->addItem("Сброс");
  lay_global_h_->addWidget(combo_box_);
  lay_global_h_->addStretch(3);
  lay_global_v_->addLayout(lay_global_h_);
  lay_global_v_->addStretch(3);
  this->setLayout(lay_global_v_);

  ////////////////////////
  mx_ = 0;
  my_ = 0;           // Позиция Курсора (обработанная)
  prev_mx_ = 0;
  prev_my_ = 0;   // Предыдущая позиция курсора?

  connect(combo_box_, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeProection(int)));

  setMouseTracking(true);
}

void GLWidget::initializeGL() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);                  // цвет "очистки порта вида"
  glEnable(GL_DEPTH_TEST);                            // буфер глубины
  //glStencilMask(l);// число битов, задающее маску
  glEnable(GL_STENCIL_TEST);                          // буфер трафарета
  glClearStencil(0); // значение заполнения буфера трафарета при очистке
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_MODELVIEW);                     // включить матрицу вида
}

void GLWidget::resizeGL(int w_arg, int h_arg) {
  int w = w_arg, h = h_arg;
  if (w != 0 && h != 0) {
    current_ortho_.width_ = w;
    current_ortho_.height_ = h;
  } else {
    current_ortho_.width_ = current_ortho_.last_width_;
    current_ortho_.height_ = current_ortho_.last_height_;
    w = current_ortho_.last_width_;
    h = current_ortho_.last_height_;
  }

  current_ortho_.left_val_ = -w / h * 2;
  current_ortho_.right_val_ = w / h * 2;
  current_ortho_.top_val_ = -w / h;
  current_ortho_.down_val_ = w / h;
  current_ortho_.near_val_ = -10;
  current_ortho_.far_val_ = 10;

  glViewport(0, 0, current_ortho_.width_, current_ortho_.height_);                         // Размер порта вида
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(current_ortho_.left_val_,
          current_ortho_.right_val_,
          current_ortho_.top_val_,
          current_ortho_.down_val_,
          current_ortho_.near_val_,
          current_ortho_.far_val_);                                  // Размер ортогональной проекции
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //  glGetDoublev(GL_MODELVIEW_MATRIX, &startMatrix[0][0]);
  //  CopyMatrix(inversStartMatrix, startMatrix);
  //  InversMatrix(inversStartMatrix);
}

void GLWidget::paintGL() {
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);   // Очистка буферов
  glPolygonMode(GL_FRONT, GL_FILL);          // Режим отрисовки

  glScalef(g_scale_, g_scale_, g_scale_);
  glTranslatef(x_translate_, y_translate_, z_translate_);
  glRotatef(x_rot_ / 16.0, 1.0, 0.0, 0.0);
  glRotatef(y_rot_ / 16.0, 0.0, 1.0, 0.0);
  glRotatef(z_rot_ / 16.0, 0.0, 0.0, 1.0);

  if (this->GetProjection() == VIEW_FRONT) {
    glPushMatrix();
    glTranslated(0, 0, -current_ortho_.far_val_);
    glRotated(-90, 1, 0, 0);
    if (painting_mode_ != MODE_FICTIVE)
      this->DrawPlane();
    glPopMatrix();
  } else if (this->GetProjection() == VIEW_RIGHT) {
    glPushMatrix();
    glTranslated(current_ortho_.far_val_, 0, 0);
    glRotatef(90, 0, 0, 1);
    if (painting_mode_ != MODE_FICTIVE)
      this->DrawPlane();
    glPopMatrix();
  } else {
    if (painting_mode_ != MODE_FICTIVE)
      this->DrawPlane();
  }

  if (painting_mode_ == MODE_FICTIVE)
    glDisable(GL_LIGHTING);
  else
    glEnable(GL_LIGHTING);

  current_work_->DrawWork(painting_mode_);
  if (painting_mode_ != MODE_FICTIVE) {
    glDisable(GL_LIGHTING);
    DrawAxes();
  }
  /*
  GLUquadric *quad = gluNewQuadric();

  glStencilFunc(GL_NEVER, 1, 1); // значение mask не используется
  glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);


  glColor3d(1,0,0);
  gluSphere(quad, 1.0, 20, 20);


  glTranslated(0.7, 0, 0);

  glStencilFunc(GL_NOTEQUAL, 1, 1); // значение mask не используется
  glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

  glColor3d(0,1,0);
  gluSphere(quad, 1.0, 20, 20);*/


}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  GetSelectedPrimitiveId(event);

  if (event->button() == Qt::RightButton && selected_) {
    context_menu_primitive_->exec(event->globalPos());
  }

  switch (*curren_event_) {
    case MEL_SPHERE:
    case MEL_CUBE:
    case MEL_PYRAMID:
    case MEL_CYLINDER:AddPrimitive();
      previous_event_ = curren_event_;
      p_mw_->SetCurEvent(CAMERA_TRANSLATE);
      break;
    case ACTION_ROTATE:
      if (selected_)
        AddAction(ACTION_ROTATE);
      break;
    case ACTION_TRANSLATE:
      if (selected_)
        AddAction(ACTION_TRANSLATE);
      break;
    case ACTION_SCALE:
      if (selected_)
        AddAction(ACTION_SCALE);
      break;
    case ACTION_STRETCH:
      if (selected_)
        AddAction(ACTION_STRETCH);
      break;

    case ACTION_GROUP: {
      if (current_work_->GetGroupObj1() == -1)
        current_work_->SetGroupObj1(p_mw_->selected_prim_);
      else if (current_work_->GetGroupObj2() == -1)
        current_work_->SetGroupObj2(p_mw_->selected_prim_);

      if (current_work_->GetGroupObj1() > -1 && current_work_->GetGroupObj2() > -1)
        EventGroupPrimitive(current_work_->GetGroupObj1(), current_work_->GetGroupObj2());

      break;
    }
    case ACTION_SUBSTRACT: {
      if (current_work_->GetGroupObj1() == -1)
        current_work_->SetGroupObj1(p_mw_->selected_prim_);
      else if (current_work_->GetGroupObj2() == -1)
        current_work_->SetGroupObj2(p_mw_->selected_prim_);

      if (current_work_->GetGroupObj1() > -1 && current_work_->GetGroupObj2() > -1)
        EventSubstractPrimitive(current_work_->GetGroupObj1(), current_work_->GetGroupObj2());

      break;
    }
    case ACTION_INTERSECT: {
      if (current_work_->GetGroupObj1() == -1)
        current_work_->SetGroupObj1(p_mw_->selected_prim_);
      else if (current_work_->GetGroupObj2() == -1)
        current_work_->SetGroupObj2(p_mw_->selected_prim_);

      if (current_work_->GetGroupObj1() > -1 && current_work_->GetGroupObj2() > -1)
        EventIntersectPrimitive(current_work_->GetGroupObj1(), current_work_->GetGroupObj2());

      break;
    }
    default:break;
  }

  last_pos_ = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  current_pos_.setX(event->x() - last_pos_.x());
  current_pos_.setY(event->y() - last_pos_.y());
  if (event->buttons() && Qt::LeftButton)
    SelectEvent(event, current_pos_);
  last_pos_ = event->pos();

  p_mw_->GetStatusBar()->showMessage(
      "Window: " + QString::number(event->pos().x()) + "   " + QString::number(event->pos().y()) +
          "      OpenGL: " + QString::number(ScreenToOgl(event->pos().x(), COORD_X)) + "   "
          + QString::number(ScreenToOgl(event->pos().y(), COORD_Y))
          + "      Событие: " + GetTextEvent(*curren_event_));
}

void GLWidget::SetProjection(int i) {
  this->projection_type_ = i;
  glLoadIdentity();
  switch (i) {
    case VIEW_FRONT:x_rot_ = 0;
      y_rot_ = 0;
      z_rot_ = 0;
      this->combo_box_->setCurrentIndex(3);
      break;
    case VIEW_TOP:x_rot_ = -90.0f * 16;
      y_rot_ = 0;
      z_rot_ = 0;
      this->combo_box_->setCurrentIndex(1);
      break;
    case VIEW_RIGHT:x_rot_ = 0;
      y_rot_ = 90.0f * 16;
      z_rot_ = 0;
      this->combo_box_->setCurrentIndex(2);
      break;
    case VIEW_PERSPECTIVE:x_rot_ = 10.0f * 16;
      y_rot_ = 10.0f * 16;
      z_rot_ = 0;
      this->combo_box_->setCurrentIndex(0);
      break;
  }
  this->update();
}

int GLWidget::GetProjection() {
  return projection_type_;
}

void GLWidget::ChangeProection(int n) {
  switch (n) {
    case VIEW_PERSPECTIVE:SetProjection(VIEW_PERSPECTIVE);
      break;
    case VIEW_TOP:SetProjection(VIEW_TOP);
      break;
    case VIEW_RIGHT:SetProjection(VIEW_RIGHT);
      break;
    case VIEW_FRONT:SetProjection(VIEW_FRONT);
      break;
    case VIEW_FULL_SCREEN:
      //pMW->GetPaintingZone()->SaveProjectionLastState();
      p_mw_->GetPaintingZone()->SetMaximum(this->projection_type_);
      break;
    case VIEW_RESET:
      p_mw_->GetPaintingZone()->SetAllUnvisible(false);
      p_mw_->GetPaintingZone()->LoadProjectionLastState();
      break;
  }
}

void GLWidget::SaveLastState() {
  current_ortho_.last_height_ = current_ortho_.height_;
  current_ortho_.last_width_ = current_ortho_.width_;
  this->last_projection_ = GetProjection();

}

void GLWidget::LoadLastState() {
  current_ortho_.height_ = current_ortho_.last_height_;
  current_ortho_.width_ = current_ortho_.last_width_;
  SetProjection(this->last_projection_);
}

void GLWidget::SelectEvent(QMouseEvent *event, QPoint current) {
  switch (*curren_event_) {
    case CAMERA_TRANSLATE:EventTranslateCamera(event, current);
      break;

    case ACTION_TRANSLATE:
      if (selected_)
        EventTranslatePrimitive(event);
      else
        EventTranslateCamera(event, current);
      break;

    case CAMERA_ROTATE:EventRotateCamera(event, current);
      break;

    case ACTION_ROTATE:
      if (selected_)
        EventRotatePrimitive(event, current);
      else
        EventRotateCamera(event, current);
      break;

    case CAMERA_ZOOM:EventZoomCamera(event, current);
      break;

    case ACTION_SCALE:
      if (selected_)
        EventScalePrimitive(current);
      else
        EventZoomCamera(event, current);
      break;
    case ACTION_STRETCH:
      if (selected_)
        EventStretchPrimitive(current);
      break;

  }
}

//  Камера

void GLWidget::EventTranslateCamera(QMouseEvent *event, QPoint current) {
  if (this->GetProjection() == VIEW_TOP) {
    if (current.x() > 0) {
      x_translate_ += step_translate_;
    } else if (current.x() < 0) {
      x_translate_ -= step_translate_;
    }
    if (current.y() > 0) {
      y_translate_ -= step_translate_;
    } else if (current.y() < 0) {
      y_translate_ += step_translate_;
    }
    this->update();
    return;
  }

  if (this->GetProjection() == VIEW_RIGHT) {
    if (current.x() > 0) {
      x_translate_ += step_translate_;
    } else if (current.x() < 0) {
      x_translate_ -= step_translate_;
    }
    if (current.y() > 0) {
      y_translate_ -= step_translate_;
    } else if (current.y() < 0) {
      y_translate_ += step_translate_;
    }

    this->update();
    return;
  }

  if (this->GetProjection() == VIEW_FRONT) {
    if (current.x() > 0) {
      x_translate_ += step_translate_;
    } else if (current.x() < 0) {
      x_translate_ -= step_translate_;
    }
    if (current.y() > 0) {
      y_translate_ -= step_translate_;
    } else if (current.y() < 0) {
      y_translate_ += step_translate_;
    }
    this->update();
    return;
  }

  if (this->GetProjection() == VIEW_PERSPECTIVE) {
    if (current.x() > 0) {
      x_translate_ += step_translate_;
      //xCamPos -= step_translate;
      //xCamLook -= step_translate;
    } else if (current.x() < 0) {
      x_translate_ -= step_translate_;
      //xCamPos += step_translate;
      //xCamLook += step_translate;
    }
    if (current.y() > 0) {
      y_translate_ -= step_translate_;
      //zCamPos -= step_translate;
      //zCamLook -= step_translate;
    } else if (current.y() < 0) {
      y_translate_ += step_translate_;
      //zCamPos += step_translate;
      //zCamLook += step_translate;
    }
    this->update();
    return;
  }

  //R = sqrt((xCamLook-xCamPos)*(xCamLook-xCamPos)+(zCamLook-zCamPos)*(zCamLook-zCamPos));
}

void GLWidget::EventZoomCamera(QMouseEvent *event, QPoint current) {
  if (this->GetProjection() == VIEW_TOP) {
    if (current.y() > 0)
      g_scale_ -= step_scale_;
    else if (current.y() < 0)
      g_scale_ += step_scale_;

    this->update();
  } else if (this->GetProjection() == VIEW_RIGHT) {
    if (current.y() > 0)
      g_scale_ -= step_scale_;
    else if (current.y() < 0)
      g_scale_ += step_scale_;
    this->update();
  } else if (this->GetProjection() == VIEW_FRONT) {
    if (current.y() > 0)
      g_scale_ -= step_scale_;
    else if (current.y() < 0)
      g_scale_ += step_scale_;

    this->update();
  }
  /*
  else if(isPerspectiveW){
      if(current.y()>0){
          yCamPos -= step_translate;
          zCamPos -= step_translate;
      }
      else if(current.y()<0){
          yCamPos += step_translate;
          zCamPos += step_translate;
      }
      this->update();
      return;
  }
*/

  koef_ = CalcKoef();
}

void GLWidget::EventRotateCamera(QMouseEvent *event, QPoint current) {
  if (this->GetProjection() == VIEW_TOP)
    SetYRotation(y_rot_ + 8 * current.x());

  if (this->GetProjection() == VIEW_FRONT)
    SetZRotation(z_rot_ + (-8) * current.x());

  if (this->GetProjection() == VIEW_RIGHT) {
    SetXRotation(x_rot_ + 8 * current.x());
  }

  if (this->GetProjection() == VIEW_PERSPECTIVE) {

    GLdouble matrix[4][4], workMatrix[4][4];

    glGetDoublev(GL_MODELVIEW_MATRIX, &matrix[0][0]);
    CopyMatrix(workMatrix, invers_start_matrix_);
    MultiMatrix(workMatrix, matrix);
    glLoadMatrixd(&start_matrix_[0][0]);

    if (prev_mx_ != event->x()) {
      glRotated((double) (last_pos_.x() - event->x()), 0, -1, 0);
    }
    if (prev_my_ != event->y()) {
      glRotated((double) (last_pos_.y() - event->y()), -1, 0, 0);
    }
/*


        if(current.x()>0)
        {
            setYRotation(yRot + 8 * current.x());
            //n += 3.14/sector;
            //xCamLook +=R*sin(n);
            //zCamLook +=R*cos(n);
        }
        if(current.x()<0)
        {
            SetYRotation(yRot + 8 * current.x());
            //n -= 3.14/sector;
            //xCamLook -=R*sin(n);
            // zCamLook -=R*cos(n);
        }
        if(current.y()>0)
        {
            setZRotation(zRot + 8 * current.x());
            //n += 3.14/sector;
            //xCamLook +=R*sin(n);
            //zCamLook +=R*cos(n);
        }
        if(current.y()<0)
        {
            SetZRotation(zRot + 8 * current.x());
        }
*/

    glMultMatrixd(&workMatrix[0][0]);
  }

  this->update();
  return;
}

//  Примитивы

void GLWidget::AddPrimitive(QPoint pos) {
  if (pos.x() == 0 && pos.y() == 0)
    current_work_->AddPrimitive(*curren_event_);
  else {
    double x = ScreenToOgl(pos.x(), COORD_X);
    double y = ScreenToOgl(pos.y(), COORD_Y);
    qDebug() << x << " " << y;
    current_work_->AddPrimitive(*curren_event_, QPoint(x, y));
  }

  p_mw_->Update();
}

void GLWidget::AddPrimitive(int i) {
  current_work_->AddAction(i);
  p_mw_->Update();
}

void GLWidget::AddAction(int i) {
  current_work_->AddAction(*curren_event_);
}

void GLWidget::DeletePrimitive() {
  current_work_->DeletePrimitive(p_mw_->selected_prim_);
  p_mw_->Update();
}

void GLWidget::EventTranslatePrimitive(QMouseEvent *event) {
  Translate *translate = current_work_->GetList()->at(p_mw_->selected_prim_)->GetTranslate();

  double new_Mx = current_ortho_.width_ / 2 - event->pos().x();
  double new_My = event->pos().y() - current_ortho_.height_ / 2;
  mx_ = prev_mx_ - new_Mx;
  my_ = prev_my_ - new_My;
  prev_mx_ = new_Mx;
  prev_my_ = new_My;

  if (event->buttons() && Qt::LeftButton && this->GetProjection() == VIEW_TOP) {
    translate->Move(ScreenToOgl(mx_, COORD_X), 0, ScreenToOgl(my_, COORD_Y));
    p_mw_->Update();
    return;
  }

  if (event->buttons() && Qt::LeftButton && this->GetProjection() == VIEW_FRONT) {
    translate->Move(ScreenToOgl(mx_, COORD_X), ScreenToOgl(my_, COORD_Y), 0);
    p_mw_->Update();
    return;
  }

  if (event->buttons() && Qt::LeftButton && this->GetProjection() == VIEW_RIGHT) {
    translate->Move(0, ScreenToOgl(my_, COORD_Y), ScreenToOgl(mx_, COORD_X));
    p_mw_->Update();
    return;
  }
}

void GLWidget::EventRotatePrimitive(QMouseEvent *event, QPoint current) {
  Rotate *rotate = current_work_->GetList()->at(p_mw_->selected_prim_)->GetRotate();
  switch (GetProjection()) {
    case VIEW_TOP:
      if (current.x() > 0) {
        rotate->RotateY(step_rotate_);
      } else if (current.x() < 0) {
        rotate->RotateY(-1 * step_rotate_);
      }
      if (current.y() > 0) {
        rotate->RotateY(step_rotate_);
      } else if (current.y() < 0) {
        rotate->RotateY(-1 * step_rotate_);
      }

      p_mw_->Update();
      break;
    case VIEW_FRONT:
      if (current.x() < 0) {
        rotate->RotateZ(step_rotate_);
      } else if (current.x() > 0) {
        rotate->RotateZ(-1 * step_rotate_);
      }
      if (current.y() < 0) {
        rotate->RotateZ(step_rotate_);
      } else if (current.y() > 0) {
        rotate->RotateZ(-1 * step_rotate_);
      }
      p_mw_->Update();
      break;
    case VIEW_RIGHT:
      if (current.x() > 0) {
        rotate->RotateX(step_rotate_);
      } else if (current.x() < 0) {
        rotate->RotateX(-1 * step_rotate_);
      }
      if (current.y() > 0) {
        rotate->RotateX(step_rotate_);
      } else if (current.y() < 0) {
        rotate->RotateX(-1 * step_rotate_);
      }
      p_mw_->Update();
      break;
    case VIEW_PERSPECTIVE:break;
  }
}

void GLWidget::EventGroupPrimitive(long obj_1, long obj_2) {
  if (obj_1 == obj_2) {
    QMessageBox::critical(this, "Ошибка",
                          "Невозможно групировать с самим собой!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }
  if (IntersectionGroupObj(obj_1, obj_2)) {
    AddPrimitive(ACTION_GROUP);
    QMessageBox::about(this, "Операция выполнена",
                       "Объекты сгрупированы!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
  } else {
    QMessageBox::critical(this, "Ошибка",
                          "Объекты не пересекаются!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }
}

void GLWidget::EventSubstractPrimitive(long obj_1, long obj_2) {
  if (obj_1 == obj_2) {
    QMessageBox::critical(this, "Ошибка",
                          "Невозможно вычесть из самого себя!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }
  if (IntersectionGroupObj(obj_1, obj_2)) {
    AddPrimitive(ACTION_SUBSTRACT);
    QMessageBox::about(this, "Операция выполнена",
                       "Объект вычтен!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
  } else {
    QMessageBox::critical(this, "Ошибка",
                          "Объекты не пересекаются!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }

}

void GLWidget::EventIntersectPrimitive(long obj_1, long obj_2) {
  if (obj_1 == obj_2) {
    QMessageBox::critical(this, "Ошибка",
                          "Невозможно пересечь с самим сабой!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }
  if (IntersectionGroupObj(obj_1, obj_2)) {
    AddPrimitive(ACTION_INTERSECT);
    QMessageBox::about(this, "Операция выполнена",
                       "Объекты пересечены!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
  } else {
    QMessageBox::critical(this, "Ошибка",
                          "Объекты не пересекаются!");
    current_work_->SetGroupObj1(-1);
    current_work_->SetGroupObj2(-1);
    return;
  }
}

void GLWidget::EventScalePrimitive(QPoint point) {
  Scale *scale = current_work_->GetList()->at(p_mw_->selected_prim_)->GetScale();

  if (point.y() < 0) {
    scale->ScaleYxy(step_scale_, step_scale_, step_scale_);
  } else if (point.y() > 0) {
    scale->ScaleYxy(-1 * step_scale_, -1 * step_scale_, -1 * step_scale_);
  }

  p_mw_->Update();
}

void GLWidget::EventStretchPrimitive(QPoint point) {
  Scale *scale = current_work_->GetList()->at(p_mw_->selected_prim_)->GetScale();

  switch (GetProjection()) {
    case VIEW_TOP:
      if (point.x() > 0) {
        scale->ScaleX(step_scale_);
      } else if (point.x() < 0) {
        scale->ScaleX(-1 * step_scale_);
      }
      if (point.y() < 0) {
        scale->ScaleZ(step_scale_);
      } else if (point.y() > 0) {
        scale->ScaleZ(-1 * step_scale_);
      }

      p_mw_->Update();
      break;
    case VIEW_FRONT:
      if (point.x() > 0) {
        scale->ScaleX(step_scale_);
      } else if (point.x() < 0) {
        scale->ScaleX(-1 * step_scale_);
      }
      if (point.y() < 0) {
        scale->ScaleY(step_scale_);
      } else if (point.y() > 0) {
        scale->ScaleY(-1 * step_scale_);
      }

      p_mw_->Update();
      break;
    case VIEW_RIGHT:
      if (point.x() > 0) {
        scale->ScaleZ(step_scale_);
      } else if (point.x() < 0) {
        scale->ScaleZ(-1 * step_scale_);
      }
      if (point.y() < 0) {
        scale->ScaleY(step_scale_);
      } else if (point.y() > 0) {
        scale->ScaleY(-1 * step_scale_);
      }

      p_mw_->Update();
      break;
  }

  p_mw_->Update();
}

//  Рисование
void GLWidget::DrawAxes() {
  glLoadIdentity();
  glTranslated(2.9, -1.4, 5);
  glScaled(0.5, 0.5, 0.5);
  glRotatef(x_rot_ / 16.0, 1.0, 0.0, 0.0);
  glRotatef(y_rot_ / 16.0, 0.0, 1.0, 0.0);
  glRotatef(z_rot_ / 16.0, 0.0, 0.0, 1.0);

  glLineWidth(2);
  glBegin(GL_LINES);
  glColor3ub(255, 0, 0);//Цвет оси X
  // Ось X
  glVertex3d(0, 0, 0);
  glVertex3d(1, 0, 0);
  glPushMatrix();
  glLineWidth(3);
  glTranslated(1.2, 0, 0);
  glScaled(0.2, 0.2, 0.2);
  //DrawX();
  glLineWidth(2);
  glPopMatrix();
  glColor3ub(0, 255, 0);//Цвет оси Y
  // Ось Y
  glVertex3d(0, 0, 0);
  glVertex3d(0, 1, 0);
  glPushMatrix();
  glLineWidth(3);
  glTranslated(0, 1.2, 0);
  glScaled(0.3, 0.3, 0.3);
  glLineWidth(2);
  //   DrawY();
  glPopMatrix();
  glColor3ub(0, 0, 255);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, 1);
  glPushMatrix();
  glLineWidth(3);
  glTranslated(0, 0, 1.2);
  glScaled(0.3, 0.3, 0.3);
  glLineWidth(2);
  //  DrawZ();
  glPopMatrix();
  glEnd();
  glLineWidth(1);
}

void GLWidget::DrawX() {
  // Буква X
  glBegin(GL_LINES);
  glVertex3d(-1, 1, 0);
  glVertex3d(1, -1, 0);

  glVertex3d(-1, -1, 0);
  glVertex3d(1, 1, 0);
  glEnd();
}

void GLWidget::DrawY() {
  glBegin(GL_LINES);
  glVertex3d(-1, 1, 0);
  glVertex3d(1, 1, 0);
  glVertex3d(-1, -1, 0);
  glVertex3d(1, -1, 0);
  glVertex3d(-1, -1, 0);
  glVertex3d(1, -1, 0);
  glEnd();
}

void GLWidget::DrawZ() {
  glBegin(GL_LINE);
  glVertex3d(-0.8, 1, 0);
  glVertex3d(0, 0, 0);

  glVertex3d(0.8, 1, 0);
  glVertex3d(0, 0, 0);

  glVertex3d(0, 0, 0);
  glVertex3d(0, -1, 0);
  glEnd();
}

void GLWidget::DrawPlane() {
  glColor3f(0.0f, 0.0f, 0.0f);

  for (double i = PLANE_MIN_X; i <= PLANE_MAX_X; i += 0.5) {
    glBegin(GL_LINES);
    glVertex3d(PLANE_MIN_X, 0, i);
    glVertex3d(PLANE_MAX_X, 0, i);

    glVertex3d(i, 0, PLANE_MIN_Z);
    glVertex3d(i, 0, PLANE_MAX_Z);
    glEnd();
  }
}

//  Дополнительные

double GLWidget::ScreenToOgl(int coord, int type) {

  double opengl_pix;

  switch (type) {
    case COORD_X: {
      double proj_x = (current_ortho_.width_ / current_ortho_.height_ * (double) 4);
      opengl_pix = (proj_x / current_ortho_.width_);
      break;
    }
    case COORD_Y: {
      double proj_y = ((current_ortho_.width_ / current_ortho_.height_) * (double) 2);
      opengl_pix = (proj_y / current_ortho_.height_);
      break;
    }
  }

  return opengl_pix * (double) coord;
}

double GLWidget::ScreenToOgLv2(int last, int coord, int type) {

  double opengl_pix;
  double result = 0;

  switch (type) {

    case COORD_X: {
      double proj_x = (current_ortho_.width_ / current_ortho_.height_ * (double) 4);
      opengl_pix = (proj_x / current_ortho_.width_);
      if (coord > last) {
        result = opengl_pix * ((double) coord - ((double) last));
      } else if (coord < last) {
        result = opengl_pix * ((double) coord - (double) last);
      }

      break;
    }
    case COORD_Y: {
      double proj_y = ((current_ortho_.width_ / current_ortho_.height_) * (double) 2);
      opengl_pix = (proj_y / current_ortho_.height_);

      if (coord > last) {
        result = (-1) * opengl_pix * ((double) coord - ((double) last));
      } else if (coord < last) {
        result = (-1) * opengl_pix * ((double) coord - ((double) last));
      }

      break;
    }
  }

  return result;
}

void GLWidget::SetXRotation(int angle) {
  QNormalizeAngle(angle);
  if (angle != x_rot_) {
    x_rot_ = angle;
    update();
  }
}

void GLWidget::SetYRotation(int angle) {
  QNormalizeAngle(angle);
  if (angle != y_rot_) {
    y_rot_ = angle;
    update();
  }
}

void GLWidget::SetZRotation(int angle) {
  QNormalizeAngle(angle);
  if (angle != z_rot_) {
    z_rot_ = angle;
    update();
  }
}

void GLWidget::QNormalizeAngle(int &angle) {
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360 * 16)
    angle -= 360 * 16;
}

// TEMP

long GLWidget::GetSelectedPrimitiveId(QMouseEvent *event) {
  painting_mode_ = MODE_FICTIVE;
  update();
  glReadPixels(event->pos().x(), current_ortho_.height_ - event->pos().y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel_);
  painting_mode_ = MODE_REAL;
  update();

  QList<Container *> *elements = current_work_->GetList();

  if (elements->size() > 0) {

    for (int i = 0; i < elements->size(); i++) {
      Container *cont = elements->at(i);
      Mcolor *color = 0;// Цвет примитива из контейнера
      GLubyte ba[3] = {0};
      color = cont->GetPrimitive()->GetIdColor();
      ba[0] = (GLubyte) color->red_;
      ba[1] = (GLubyte) color->green_;
      ba[2] = (GLubyte) color->blue_;

      if (ba[0] == pixel_[0] && ba[1] == pixel_[1] && ba[2] == pixel_[2]) {
        selected_ = true;
        //делаем точку в которой кликнули началом системы координат
        prev_mx_ = current_ortho_.width_ / 2 - event->pos().x();
        prev_my_ = event->pos().y() - current_ortho_.height_ / 2;
        p_mw_->selected_prim_ = i;
        return i;

      } else {
        selected_ = false;
      }
    }
  }

  return -1;

}

double GLWidget::CalcKoef() {
  if (g_scale_ < 1) {
    return 1 + (1 - g_scale_);
  }
  qDebug() << koef_;
  return 1;
}

bool GLWidget::IntersectionGroupObj(long obj_1, long obj_2) {/*
    Element *prim1 = currentWork->element_list->at(obj1);
    Element *prim2 = currentWork->element_list->at(obj2);
    switch(prim1->GetTypeName())
    {
        case MEL_CUBE:
        //     prim1->
            break;
        case MEL_SPHERE:
            break;
    }
*/
  return true;
}

QString GLWidget::GetTextEvent(int event) {
  switch (event) {
    case ACTION_ROTATE:return "Поворот примитива";
    case ACTION_TRANSLATE:return "Перемещение примитива";
    case ACTION_SCALE:return "Масштабирование примитива";
    case ACTION_SUBSTRACT:return "Вычитание примитивов";
    case ACTION_STRETCH:return "Растягивание примитива";
    case ACTION_GROUP:return "Групировка примитивов";
    case ACTION_INTERSECT:return "Пересечение";
    case CAMERA_ZOOM:return "Масшат камеры";
    case CAMERA_TRANSLATE:return "Перемещени камеры";
    case CAMERA_ROTATE:return "Поворот камеры";
    case MEL_CUBE:return "Куб";
    case MEL_PYRAMID:return "Пирамида";
    case MEL_SPHERE:return "Сфера";
    case MEL_CYLINDER:return "Цилиндр";
    default:return "ERROR";
  }
}
