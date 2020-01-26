#include <QApplication>
#include <QtWidgets/QDesktopWidget>
#include "src/gui/main-window.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QRect desktop_geometry = QApplication::desktop()->screenGeometry();

    auto *main_window = new MainWindow(desktop_geometry.width(), desktop_geometry.height());

    main_window->show();

    return QApplication::exec();
}
