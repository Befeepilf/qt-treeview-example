#include "gui/treeModel.hpp"
#include "gui/treeView.hpp"

#include <QAbstractItemModel>


TreeView::TreeView(TreeModel* treeModel)
{
    setModel(treeModel);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragEnabled(false);
    setAcceptDrops(true);
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
}

TreeView::~TreeView()
{
}