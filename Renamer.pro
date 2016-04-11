#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T15:30:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Renamer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    file.cpp \
    filedata.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    file.h \
    filedata.h \
    qcustomplot.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release):
LIBS += -L$$PWD/../../../../../local/boost_1_59_0/stage/lib/
-lboost_filesystem-vc140-mt-gd-1_59
-lboost_system-vc140-mt-gd-1_59

else:win32:CONFIG(debug, debug|release):
LIBS += -L$$PWD/../../../../../local/boost_1_59_0/stage/lib/
-lboost_filesystem-vc140-mt-gd-1_59d
-lboost_system-vc140-mt-gd-1_59


else:unix:
LIBS += -L$$PWD/../../../../../local/boost_1_59_0/stage/lib/
-lboost_filesystem-vc140-mt-gd-1_59

INCLUDEPATH += $$PWD/../../../../../local/boost_1_59_0/
DEPENDPATH += $$PWD/../../../../../local/boost_1_59_0/
