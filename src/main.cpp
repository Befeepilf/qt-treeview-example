#include "treeModel.hpp"

#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QToolBar>
#include <QTreeView>

#include <iostream>

int main(int argc, char** argv)
{
    QApplication app (argc, argv);

    QMainWindow window;
    window.setWindowState(Qt::WindowMaximized);
    window.setWindowTitle("TreeView Example");


    TreeModel* treeModel = new TreeModel;

    QTreeView* treeView = new QTreeView;
    treeView->setModel(treeModel);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setDragEnabled(false);
    treeView->setAcceptDrops(true);
    treeView->setDefaultDropAction(Qt::MoveAction);
    treeView->setDragDropMode(QAbstractItemView::DragDrop);
    treeView->setDropIndicatorShown(true);

    window.setCentralWidget(treeView);

    QToolBar* toolbar = window.addToolBar("Add items to tree");
    QAction* addItemAct = new QAction("Create item");
    QObject::connect(addItemAct, &QAction::triggered, treeModel, [=] () {
        TreeItem* newItem = new TreeItem("New Item", TreeItemMesh);
        treeModel->appendChild(newItem);
    });
    toolbar->addAction(addItemAct);


    window.show();

    return app.exec();
}