#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T23:39:23
#
#-------------------------------------------------

QT       += core gui widgets network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += __DTSRC_ _PERSONNAL _AFU _SILVANA _JANNE

DEFINES += "SVN_REV=\"\\\"$$system(svn info --show-item=revision)\\\"\""
SVN_REV=$$system(svn info --show-item=revision)

VERSION = 4.0.0.$$SVN_REV

TARGET = Datas
TEMPLATE = app

INCLUDEPATH += . #../Include

SOURCES += \
    CDatatypes.cpp \
#    CBooleanType.cpp \
#    CDateTimeType.cpp \
#    CDoubleType.cpp \
#    CFileListType.cpp \
#    CIntegerType.cpp \
#    CLinkedList.cpp \
#    CPFileType.cpp \
#    CRoundType.cpp \
#    CStrType.cpp \
#    CVariantType.cpp \
#    CDebug.cpp \
#    CError.cpp \
    mainwindow.cpp \
    main.cpp

HEADERS  += \
    CDatatypes.h \
#    CBooleanType.h \
#    CDateTimeType.h \
#    CDoubleType.h \
#    CFileListType.h \
#    CIntegerType.h \
#    CPFileType.h \
#    CRoundType.h \
#    CStrType.h \
#    CVariantType.h \
#    #Versao.h \
#    CDebug.h \
#    CError.h \
    CLinkedList.h \
    mainwindow.h

FORMS    += mainwindow.ui

win32: {
    QMAKE_CXXFLAGS += /Zc:strictStrings-
}

RESOURCES += Datas.qrc
win32:RC_ICONS = Imagens/Datas.ico

