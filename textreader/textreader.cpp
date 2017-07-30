//
// Created by lesiamis on 4/6/17.
//

#include <QDialogButtonBox>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QQueue>
#include <QList>
#include <QMessageBox>
#include <QKeySequence>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QWidget>

#include "textreader.h"
#include "subwindow.h"
#include "textfile.h"
#include "openDialog.h"

textreader::textreader(void)
{
        makemenubar();
        makeActions();
        makeMenus();
        mainlayout = new QHBoxLayout;
        openfile = NULL;
        makelayout();
}

void textreader::makemenubar()
{
  bar = new QMenuBar(this);
}

void textreader::makeMenus()
{
    filemenu = new QMenu(tr("FILE"),this);
    filemenu -> addAction(acopen) ;
    helpmenu = new QMenu(tr("TIPS"), this);
    helpmenu -> addAction(actip);
    bar->addMenu(filemenu);
    bar->addMenu(helpmenu);
}

void textreader::makeActions()
{

    acopen = new QAction(tr("&Open"),this);
    acopen -> setShortcuts(QKeySequence::Open); // end the whole program
    connect(acopen , SIGNAL(triggered()), this, SLOT(addsubwindow()));

    actip = new QAction(tr("&Tips"),this);
    actip -> setShortcuts(QKeySequence::HelpContents);
    connect(actip , SIGNAL(triggered()), this, SLOT(howtoUse()));
}

void textreader::addsubwindow()
{
    subwindow *nw = new subwindow(this);
    windowlist.append(nw);
    if(NULL!=openfile) delete openfile;
    textfile * temp = nw -> filecontent;
    openfile = new openDialog(temp);
    openfile->exec();

    updateLayout(); //



}

void textreader::closeTab(subwindow *todelete)
{
    if(-1 == windowlist.QList<subwindow*>::indexOf(todelete)){
        return ;
    }
    else{
        windowlist.removeOne(todelete);
        updateLayout(todelete); // use pointer !!
    }
}

void textreader::updateLayout()
{
        if(windowlist.isEmpty())
        {
          return ;
        }
        this->mainlayout->addWidget(windowlist.at(windowlist.length()-1));
        windowlist.at(windowlist.length()-1)->show();
}

void textreader::updateLayout(subwindow* sb)
{
      //remove this subwindow
      printf("test\n" );
      if(-1 == windowlist.indexOf(sb))
      {
        return ;
      }
      mainlayout->removeWidget(sb);
}

/*show tips about how to use simple reader */
void textreader::howtoUse()
{
    QMessageBox tips;
    tips.setDetailedText(QString(tr("open file : CTRL-O \n/"
                                           "quit program : CTRL-Q\n"
                                           "close file : Push the Close Button")));
    tips.setStandardButtons(QMessageBox::Close);
    tips.exec();
}

void textreader::makelayout()
{
    mainlayout =new QHBoxLayout(this);
    setLayout(mainlayout);
}
