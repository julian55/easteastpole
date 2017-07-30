#ifndef POOL_SUBWINDOW_H
#define POOL_SUBWINDOW_H
#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QMenu;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QAction;
class QGroupBox;
QT_END_NAMESPACE

class textfile;

class subwindow : public  QWidget
{
  Q_OBJECT
public:
    subwindow(QWidget *);
    QGroupBox   *box;
    QHBoxLayout *boxLayout;
    QVBoxLayout *subwindowlayout;
    QPushButton *closebutton;
    QPushButton *switchbutton;
    textfile    *filecontent;

};

#endif
