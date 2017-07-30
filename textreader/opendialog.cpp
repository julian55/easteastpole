//
// Created by lesiamis on 4/6/17.
//

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QTextEdit>
#include <QMessageBox>
#include <QStringList>
#include <QSizePolicy>
#include <QGroupBox>
#include <QComboBox>
#include <QRegExp>
#include <QToolButton>
#include <QPushButton>
#include <QDialogButtonBox>
#include <cassert>
#include "opendialog.h"
#include "textfile.h"


openDialog::openDialog( textfile *tf )
{
    tfile = tf;  // set the parent textfile widget
    assert(tfile);
    createLabels(); // create open file dialog basic functions
    createFilesTree();
    createComboBoxes();
    createButtons();
    createLayout();

    setWindowTitle(tr(" ~ ~ Find File Dialog ~ ~ "));
}
void openDialog::browse()
{
    QString curDir = dirs -> currentText();
    QString newDir = QFileDialog::getExistingDirectory(this,tr("Select Directory"), curDir);
    if(!newDir.isEmpty())
    {
        dirs -> addItem(QDir::toNativeSeparators(newDir));
        dirs -> setCurrentIndex(dirs -> count() - 1 );
        updateresult();
    }
}

void openDialog::intro()
{
    tips();
}

void openDialog::openFile(QTreeWidgetItem *item)
{
      if(!item) {
        item = foundFiles ->currentItem();
        if(!item )
            return;
    }
    QString fname = item -> text(0);
    QString fpath = dirs -> currentText() + QDir::separator();

    setcontent(this->tfile,fpath + fname) ;
    close(); //
}
void openDialog::updateresult()
{
    searchFile() ;
    boxbuttons -> button(QDialogButtonBox::Open)->setEnabled(foundFiles -> topLevelItemCount() > 0 );
}
void openDialog::createLayout()
{
    holisticlayout = new  QVBoxLayout;
    fnamelayout = new  QHBoxLayout;
    searchdirlayout = new  QHBoxLayout;

    fnamelayout -> addWidget(fnamelabel);
    fnamelayout -> addWidget(filenames) ;

    searchdirlayout -> addWidget(dirlabel);
    searchdirlayout -> addWidget(dirs);
    searchdirlayout -> addWidget(browseButton);

    holisticlayout -> addLayout(fnamelayout) ;
    holisticlayout -> addLayout(searchdirlayout) ;
    holisticlayout -> addWidget(foundFiles) ;
    holisticlayout -> addStretch() ;
    holisticlayout -> addWidget(boxbuttons) ;
    setLayout(holisticlayout);
}
void openDialog::createLabels()
{
    fnamelabel = new QLabel(tr("File Name(WildCard) :"));
    dirlabel = new QLabel(tr("Search Directory : "));
}
void openDialog::createButtons()
{
    browseButton = new QToolButton;
    browseButton -> setText(tr("Go Get It"));
    connect(browseButton,SIGNAL(clicked()),this,SLOT(browse()));
    /*button box*/
    boxbuttons = new QDialogButtonBox(QDialogButtonBox::Open \
                                      | QDialogButtonBox::Cancel \
                                      | QDialogButtonBox::Help);
    connect(boxbuttons->buttons().at(1),SIGNAL(clicked()),this,SLOT(reject()));
    ///connect(boxbuttons,SIGNAL(accepted()),this,SLOT(openFile(QTreeWidgetItem*)));
    connect(boxbuttons,SIGNAL(helpRequested()),this,SLOT(tips()));
}
void openDialog::createComboBoxes()
{
    filenames = new QComboBox;
    dirs = new QComboBox ;
    filenames -> setEditable(true);
    filenames ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    dirs -> setMinimumContentsLength(30);
    dirs -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(filenames , SIGNAL(editTextChanged(QString)), this, SLOT(updateresult()
    ));
    connect(dirs , SIGNAL(currentIndexChanged(QString)), this, SLOT(updateresult()
    ));
}

void openDialog::showFiles(const QStringList &files)
{
    foundFiles -> clear() ;
    for ( int i = 0 ; i<files.count(); ++i)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(foundFiles);
        item ->setText(0,files[i]);
    }
    if(files.count() > 0 )
        foundFiles -> setCurrentItem(foundFiles ->topLevelItem(0));
}
void openDialog::searchFile()
{
    QRegExp pattern("*" + filenames->currentText() + "*");
    pattern.setPatternSyntax(QRegExp::Wildcard);
    QDir selecteddir(dirs -> currentText() );
    QStringList allfiles = selecteddir.entryList(QDir::Files | QDir::NoSymLinks);
    QStringList matchedfiles;
    foreach(QString name, allfiles)
    {
        if(pattern.exactMatch(name)){
            matchedfiles << name;
        }
    }
    showFiles(matchedfiles);
}

void openDialog::createFilesTree()
{
    foundFiles = new QTreeWidget;
    foundFiles->setColumnCount(1);
    foundFiles->setHeaderLabels(QStringList(tr("Matching Files")));
    foundFiles->setRootIsDecorated(false) ;
    foundFiles ->setSelectionMode (QAbstractItemView::SingleSelection);
    connect( foundFiles, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(openFile(QTreeWidgetItem*)));
}

void openDialog::tips()
{
    QMessageBox tipdialog;
    tipdialog.setDetailedText(QString(tr("open file : CTRL-O \n/"
                                           "quit program : CTRL-Q\n"
                                           "close file : Push the Close Button")));
    tipdialog.setStandardButtons(QMessageBox::Close);
    tipdialog.exec();
}
