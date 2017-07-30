//
// Created by lesiamis on 4/6/17.
//

#include <QObject>
#include <QWidget>
#include "subwindow.h"

#ifndef POOL1_TEXTREADER_H
#define POOL1_TEXTREADER_H

QT_BEGIN_NAMESPACE

class QWidget;
class QMenu;
class QMenuBar;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QAction;
class QGroupBox;
template <class T> class QList;
QT_END_NAMESPACE

class textfile ;
class subwindow;
class openDialog;

class textreader : public QWidget
{
    Q_OBJECT
public :
      textreader();

private slots:
  void updateLayout(); //
  void updateLayout(subwindow* );
  void addsubwindow();
  void closeTab(subwindow *todelete);
  void howtoUse(); 


private:
    openDialog *openfile;
    void makeMenus();
    void makemenubar();
    void makeActions();
    void makelayout();
    QMenu *filemenu;
    QMenu *helpmenu;
    QMenuBar *bar;

//  QAction *acexit;
    QAction *acopen;
    QAction *actip;

    QHBoxLayout *mainlayout;
    QList<subwindow *> windowlist;

};

#endif //POOL1_TEXTREADER_H
