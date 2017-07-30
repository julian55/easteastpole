#include <QApplication>
#include <QWidget>
#include "textreader.h"

int main(int argc , char *argv[])
{
    QApplication app(argc, argv);
    textreader *mainwindow = new textreader;
    mainwindow -> show();
    return app.exec();
}
