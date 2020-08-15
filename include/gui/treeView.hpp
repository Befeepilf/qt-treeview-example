#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "treeModel.hpp"
#include <QTreeView>

class TreeView : public QTreeView
{
    public:
        TreeView(TreeModel* treeModel);
        ~TreeView();
};

#endif // TREEVIEW_H