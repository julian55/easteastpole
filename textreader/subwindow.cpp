//
//  Created by Leisamis in 7/4/2017
//

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QGroupBox>
#include <QTextEdit>
#include <QWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "subwindow.h"
#include "textfile.h"

subwindow::subwindow(QWidget* par):QWidget(par)
{
    box = new QGroupBox(tr("Operations\n")) ;
    ///  assert(box);
    boxLayout = new QHBoxLayout(box);
    subwindowlayout = new QVBoxLayout ;
    this->setLayout(subwindowlayout);
    // set butTons
    closebutton = new QPushButton(tr("clsoe"), this);
    connect(closebutton,SIGNAL(clicked()),this,SLOT(close()));

    switchbutton = new QPushButton(tr("switch encoding"), this);

    boxLayout -> addWidget(closebutton) ;
    boxLayout -> addWidget(switchbutton) ;
    box->setLayout(boxLayout) ;
    subwindowlayout -> addWidget(box);

    textfile *newfile = new textfile(this);

    subwindowlayout -> addWidget(newfile);
    connect(switchbutton,SIGNAL(clicked()),newfile,SLOT(switchEncoding()));

    filecontent = newfile;
};
