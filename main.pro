TEMPLATE = app

TARGET = treeview
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/objects/
DESTDIR = $$PWD/build/

INCLUDEPATH += $$PWD/include/

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS +=  include/treeItem.hpp \
            include/treeModel.hpp
           

SOURCES +=  src/main.cpp \
            src/treeItem.cpp \
            src/treeModel.cpp