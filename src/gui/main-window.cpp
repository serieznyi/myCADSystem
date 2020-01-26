#include <QtWidgets/QMessageBox>
#include "main-window.h"

MainWindow::MainWindow(int max_width, int max_height, QWidget *parent) : QMainWindow(parent) {
    //инициализация переменных
    cur_event_ = CAMERA_TRANSLATE;
  selected_prim_ = -1;
  work_created_ = false;
  prev_event_ = 0;
  current_work_ = new Work(this);
  painting_zone_ = new PaintingZone(this);
  status_bar_ = new StatusBar();
  menu_bar_ = new MenuBar(this);

    this->setMenuBar(menu_bar_);
    this->setCentralWidget(painting_zone_);
    this->setStatusBar(status_bar_);

    //настройки окна
    this->resize(900, 700);
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(700, 500);
    this->setWindowTitle("MyCADSystem v1");
    this->show();
}

int *MainWindow::GetCurEvent() {
    return &cur_event_;
}

void MainWindow::SetCurEvent(int event) {
  cur_event_ = event;
}

int *MainWindow::GetPrevEvent() {
    return &prev_event_;
}

void MainWindow::SetPrevEvent(int event) {
  prev_event_ = event;
}

Work *MainWindow::GetWork() {
    return current_work_;
}

void MainWindow::Update() {
    painting_zone_->wid_front_->repaint();
    painting_zone_->wid_top_->repaint();
    painting_zone_->wid_right_->repaint();
    painting_zone_->wid_perspective_->repaint();
}

PaintingZone *MainWindow::GetPaintingZone() {
    return painting_zone_;
}

StatusBar *MainWindow::GetStatusBar() {
    return status_bar_;
}

void MainWindow::ShowAbout() {
    QMessageBox::about(this, tr("About Recent Files"),
                       tr("The <b>Recent Files</b> example demonstrates how to provide a "
                          "recently used file menu in a Qt application."));
}

void MainWindow::SaveTo() {
    QString path = QFileDialog::getSaveFileName();
    qDebug() << path;
    path.append(".mycs");
    this->saved_path_ = path;
    QFile *fopen = new QFile(saved_path_);
    fopen->open(QIODevice::WriteOnly);
    QDataStream out(fopen);
    QList<Container *> *list = this->current_work_->GetList();
    out << list;
    fopen->close();
}

void MainWindow::Save() {

}

void MainWindow::Open() {

}

QDataStream &operator<<(QDataStream &out, const QList<Container *> *list) {
    if (list->size() > 0) {
        out << list->size();
        for (int i = 0; i < list->size(); i++) {
            out << list->at(i);
        }
    }
    return out;
}
