//
// Created by lesiamis on 4/6/17.
//
#include <QFile>
#include <QTextEdit>
#include <QString>
#include <QFileInfo>
#include "textfile.h"
#include <cassert>

textfile::textfile(QWidget* parentw) : QTextEdit(parentw)
{
    setReadOnly(true);
    p_hex = NULL;
    p_ascii = NULL ;
}

//filename is the full path of the file
void setcontent(textfile*owner,  const QString &filename)
{
    assert(owner);
    QFileInfo   fi(filename);
    QFile       file(filename) ;

    if(false != file.open(QIODevice::ReadOnly))
    {
        printf("wang wang wang !\n" );

        QByteArray temp = file.readAll();
        const std::string s0(temp.constData(),temp.length());
        QByteArray temp1 =  temp.toHex();
        const std::string s1(temp1.constData(),temp1.length());

        QString atemp0 = QString::fromStdString(s0);
        QString atemp1 = QString::fromStdString(s1);
        if(owner->p_hex){
          delete owner->p_hex;
        }
        if(owner->p_ascii){
          delete owner->p_ascii;
        }

        owner->p_hex  = new QString(atemp0);
        owner->p_ascii = new QString(atemp1);
        owner->updatetext();
    }
    else{
        // exception handling
    }
}
void textfile::showAscii()
{
    if(!p_ascii){
        return ;
    }
    setPlainText(*p_ascii) ;
}
void textfile::showHex()
{
    if(!p_hex){
        return ;
    }
    setPlainText(*p_hex) ;
}
void textfile::switchEncoding()
{
    if(isHexData){
        setAscii();
        showAscii();
    }
    else{
        setHex();
        showHex();
    }
}
void textfile::updatetext()
{
  if(isHexData)
  {
    setPlainText(*p_hex);
  }
  else{
    setPlainText(*p_ascii);
  }
}
void textfile::setHex()
{
    isHexData = true;
}
void textfile::setAscii()
{
    isHexData = false;
}
