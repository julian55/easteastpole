//
// Created by lesiamis on 4/6/17.
//

#ifndef POOL1_TEXTFILE_H
#define POOL1_TEXTFILE_H
#include <QObject>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QTextEdit;
class QByteArray;
class QPushButton;
QT_END_NAMESPACE

class textfile : public QTextEdit{
    Q_OBJECT
public:
  QString* p_hex;
  QString* p_ascii;

    textfile(QWidget* parent = 0 );
    void updatetext();

private slots:
    void switchEncoding();

private:
    bool isHexData;

    void showHex();
    void showAscii();
    void setAscii();
    void setHex();
};

//stand alone setcontent file
void setcontent(textfile* , const QString &filename);

#endif //POOL1_TEXTFILE_H
