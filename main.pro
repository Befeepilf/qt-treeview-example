TEMPLATE = app

CONFIG += c++17

TARGET = treeview
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/objects/
DESTDIR = $$PWD/build/

INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/extras/cereal/include/
INCLUDEPATH += $$PWD/extras/lager/

QT += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS +=  include/gui/treeItem.hpp \
            include/gui/treeModel.hpp \
            include/gui/treeView.hpp \
            include/scene/camera.hpp \
            include/scene/item.hpp \
            include/scene/group.hpp \
            include/scene/light.hpp \
            include/scene/mesh.hpp \
            include/store.hpp
           

SOURCES +=  src/gui/treeItem.cpp \
            src/gui/treeModel.cpp \
            src/gui/treeView.cpp \
            src/main.cpp \
            src/scene/camera.cpp \
            src/scene/item.cpp \
            src/scene/light.cpp \
            src/scene/mesh.cpp \
            src/store.cpp