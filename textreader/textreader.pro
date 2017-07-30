TEMPLATE = app
QT+=core
QT+=widgets
QT+=gui

SOURCES+=main.cpp \
         textfile.cpp \
         textreader.cpp \
         opendialog.cpp \
         subwindow.cpp

 HEADERS+=textfile.h  \
          textreader.h\
          opendialog.h\
          subwindow.h 

target.path = /Volumes/BOOTCAMP/xxxxx/OOP/poo/pool1
INSTALL+=target
