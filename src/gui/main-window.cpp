#include <QtWidgets/QMessageBox>
#include "main-window.h"

MainWindow::MainWindow(int max_width, int max_height, QWidget *parent) : QMainWindow(parent) {
    //инициализация переменных
    cur_event = CAMERA_TRANSLATE;
    selected_prim = -1;
    WORK_CREATED = false;
    prev_event = 0;
    currentWork = new Work(this);
    paintingZone = new PaintingZone(this);
    statusBar = new StatusBar();
    menuBar = new MenuBar(this);

    this->setMenuBar(menuBar);
    this->setCentralWidget(paintingZone);
    this->setStatusBar(statusBar);

    //настройки окна
    this->resize(900, 700);
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(700, 500);
    this->setWindowTitle("MyCADSystem v1");
    this->show();
}

int *MainWindow::getCurEvent() {
    return &cur_event;
}

void MainWindow::setCurEvent(int a) {
    cur_event = a;
}

int *MainWindow::getPrevEvent() {
    return &prev_event;
}

void MainWindow::setPrevEvent(int a) {
    prev_event = a;
}

Work *MainWindow::getWork() {
    return currentWork;
}

void MainWindow::Update() {
    paintingZone->widFront->repaint();
    paintingZone->widTop->repaint();
    paintingZone->widRight->repaint();
    paintingZone->widPerspective->repaint();
}

PaintingZone *MainWindow::getPaintingZone() {
    return paintingZone;
}

StatusBar *MainWindow::getStatusBar() {
    return statusBar;
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("About Recent Files"),
                       tr("The <b>Recent Files</b> example demonstrates how to provide a "
                          "recently used file menu in a Qt application."));
}

void MainWindow::saveTo() {
    QString path = QFileDialog::getSaveFileName();
    qDebug() << path;
    path.append(".mycs");
    this->savedPath = path;
    QFile *fopen = new QFile(savedPath);
    fopen->open(QIODevice::WriteOnly);
    QDataStream out(fopen);
    QList<Container *> *list = this->currentWork->getList();
    out << list;
    fopen->close();
}

void MainWindow::save() {

}

void MainWindow::open() {

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
