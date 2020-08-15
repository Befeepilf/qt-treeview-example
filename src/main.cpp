#include "store.hpp"
#include "gui/treeModel.hpp"
#include "gui/treeView.hpp"
#include "scene/mesh.hpp"

#include <QAction>
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QToolBar>

#include <lager/event_loop/qt.hpp>
#include <lager/store.hpp>
#include <lager/util.hpp>

#include <variant>
#include <iostream>


int main(int argc, char** argv)
{
    QApplication app (argc, argv);

    auto store = lager::make_store<store::action>(
        store::model{},
        store::update,
        lager::with_qt_event_loop{app}
    );


    QMainWindow window;
    window.setWindowState(Qt::WindowMaximized);
    window.setWindowTitle("TreeView Example");


    TreeModel* treeModel = new TreeModel;
    TreeView* treeView = new TreeView(treeModel);
    window.setCentralWidget(treeView);

    watch(store, [&](store::model state) {
        treeModel->update(state);
    });

    QToolBar* toolbar = window.addToolBar("Add items to tree");

    QAction* addItemAct = new QAction("Create item");
    QObject::connect(addItemAct, &QAction::triggered, [&] () {
        std::cout << "btn" << std::endl;

        Scene::Mesh mesh = Scene::Mesh("Test mesh");
        store.dispatch(store::addMesh_action{mesh});
    });
    toolbar->addAction(addItemAct);


    window.show();

    return app.exec();
}