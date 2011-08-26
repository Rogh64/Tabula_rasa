######################################################################
# Automatically generated by qmake (2.01a) dim. juil. 24 15:58:06 2011
######################################################################

TEMPLATE = app
TARGET = tabula_Rasa
DEPENDPATH += . Interface Ressources
INCLUDEPATH += . Interface
#QMAKE_CXXFLAGS += -std=c++0x
CONFIG += debug
RC_FILE = iconSetter.rc
QT += xml

# Input
HEADERS += Interface/mainwindow.hpp \
    Pictogramme/pictogramme.hpp \
    Pictogramme/pictoAction.hpp \
    Pictogramme/labelItem.hpp \
    Pictogramme/pictoProcedure.hpp \
    Pictogramme/pictoIteration.hpp \
    Pictogramme/liaisonItem.hpp \
    Pictogramme/ancreItem.hpp \
    Pictogramme/pictoCondition.hpp \
    Interface/algorithmeScene.hpp \
    Pictogramme/pictoSortie.hpp \
    Pictogramme/pictoConditionMultiple.hpp \
    Interface/tabWidget.hpp \
    Interface/resizeDialog.hpp \
    aboutDialog.hpp \
    Interface/aboutDialog.hpp \
    Pictogramme/pictoBuilder.hpp
FORMS += Interface/mainwindow.ui \
    Interface/resizeDialog.ui \
    aboutDialog.ui
SOURCES += main.cpp Interface/mainwindow.cpp \
    Pictogramme/pictogramme.cpp \
    Pictogramme/pictoAction.cpp \
    Pictogramme/labelItem.cpp \
    Pictogramme/pictoProcedure.cpp \
    Pictogramme/pictoIteration.cpp \
    Pictogramme/liaisonItem.cpp \
    Pictogramme/ancreItem.cpp \
    Pictogramme/pictoCondition.cpp \
    Interface/algorithmeScene.cpp \
    Pictogramme/pictoSortie.cpp \
    Pictogramme/pictoConditionMultiple.cpp \
    Interface/tabWidget.cpp \
    Interface/resizeDialog.cpp \
    aboutDialog.cpp \
    Pictogramme/pictoBuilder.cpp
RESOURCES += Ressources/ressources.qrc

OTHER_FILES +=
