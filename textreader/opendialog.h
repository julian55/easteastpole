//
// Created by lesiamis on 4/6/17.
//

#ifndef POOL1_OPENDIALOG_H
#define POOL1_OPENDIALOG_H

#include <QObject>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
class QTextEdit;
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

//local class forward declartion
class textfile;

class openDialog : public QDialog{
    Q_OBJECT
public :
    openDialog(textfile *editor);
    textfile * tfile;

private slots:
    void intro();
    void browse();
    void tips();
    void openFile(QTreeWidgetItem *item);
    void updateresult(); // flush the searching result window

private:

    QVBoxLayout *holisticlayout;
    QHBoxLayout *fnamelayout;
    QHBoxLayout *searchdirlayout;
  /**/
    QLabel *fnamelabel;
    QLabel * dirlabel;
    QComboBox *filenames;
    QComboBox *dirs;
    QDialogButtonBox *boxbuttons;
    QTreeWidget *foundFiles;
    QToolButton *browseButton;

    void createLayout();
    void createLabels();
    void createButtons();
    void createComboBoxes();
    void createFilesTree();

    void searchFile();
    void showFiles(const QStringList &files);
};


#endif //POOL1_OPENDIALOG_H
