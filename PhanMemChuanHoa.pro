#-------------------------------------------------
#
# Project created by Hoang Tran Hao and Nguyen Kim Tien.
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhanMemChuanHoa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    aboutus.cpp \
    cachhoatdong.cpp \
    timkiem.cpp \
    adds.cpp \
    botuviettat.cpp \
    thaythe.cpp \
    review.cpp \
    duan.cpp

HEADERS  += mainwindow.h \
    settings.h \
    aboutus.h \
    cachhoatdong.h \
    timkiem.h \
    adds.h \
    botuviettat.h \
    thaythe.h \
    review.h \
    duan.h

FORMS    += mainwindow.ui \
    settings.ui \
    aboutus.ui \
    cachhoatdong.ui \
    timkiem.ui \
    adds.ui \
    botuviettat.ui \
    thaythe.ui \
    review.ui \
    duan.ui

RESOURCES += \
    res.qrc \
    icon.qrc
