#include "treeItem.hpp"
#include "treeModel.hpp"

#include <QByteArray>
#include <QMap>
#include <QMimeData>
#include <QModelIndex>
#include <QModelIndexList>
#include <QStringList>
#include <QVariant>

#include <iostream>


TreeModel::TreeModel(QObject* parent) : QAbstractItemModel(parent)
{
    rootItem = new TreeItem("Name", TreeItemGroup, {"Test1", "Test2"});

    TreeItem* a = new TreeItem("A", TreeItemGroup, {"Item", 1});
    TreeItem* b = new TreeItem("B", TreeItemMesh, {"Item", 2});
    TreeItem* c = new TreeItem("C", TreeItemGroup, {"Item", 3});
    TreeItem* d = new TreeItem("D", TreeItemCamera, {"Item", 4});

    a->appendChild(b);
    c->appendChild(d);

    rootItem->appendChild(a);
    rootItem->appendChild(c);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}


int TreeModel::rowCount(const QModelIndex& parent) const
{
    // the children of a treeItem are stored in the first column
    // only treeItems have children and therefore multiple rows
    // data is stored in columns after the first column
    // data does not have children and therefore no rows
    if (parent.column() > 0)
        return 0;

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childrenCount();
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->columnCount();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();


    TreeItem* parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}


QVariant TreeModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && (role == Qt::DisplayRole || role == Qt::EditRole))
        return rootItem->data(column, role);
    return QVariant();
}

bool TreeModel::setHeaderData(int column, Qt::Orientation orientation, const QVariant& value, int role)
{
    if (rootItem->setData(column, role, value))
    {
        emit headerDataChanged(orientation, column, column);
        return true;
    }

    return false;
}


QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::DecorationRole && role != Qt::EditRole)
        return QVariant();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    if (!childItem)
        return QVariant();

    return childItem->data(index.column(), role);
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());

    if (childItem == nullptr)
        return false;

    if (childItem->setData(index.column(), role, value))
    {
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

bool TreeModel::setItemData(const QModelIndex& index, const QMap<int, QVariant>& roles)
{
    if (!index.isValid())
        return false;

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());

    if (childItem == nullptr)
        return false;


    QMap<int, QVariant>::const_iterator i = roles.constBegin();
    bool res = true;

    while (i != roles.constEnd())
    {
        res &= childItem->setData(index.column(), i.key(), i.value());
        i++;
    }

    return res;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        // allow for dropping on empty areas
        return Qt::ItemIsDropEnabled;

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    if (childItem)
        return childItem->dataFlags(index.column());
    return Qt::NoItemFlags;
}


bool TreeModel::insertRows(int row, int count, const QModelIndex& parent)
{
    TreeItem* parentItem;
    
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    beginInsertRows(parent, row, row + count - 1);
    bool res = parentItem->insertEmptyChildren(row, count);
    endInsertRows();

    return res;
}

bool TreeModel::setRow(int row, TreeItem* item, const QModelIndex& parent)
{
    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->setChild(row, item);
}

bool TreeModel::removeRows(int row, int count, const QModelIndex& parent)
{
    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    beginRemoveRows(parent, row, row + count - 1);
    bool res = parentItem->removeChildren(row, count);
    endRemoveRows();

    return res;
}

bool TreeModel::removeRow(int row, const QModelIndex& parent)
{
    return removeRows(row, 1, parent);
}

bool TreeModel::insertColumns(int column, int count, const QModelIndex& parent)
{
    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    beginInsertColumns(parent, column, column + count - 1);
    bool res = parentItem->insertEmptyData(column, count);
    endInsertColumns();

    return res;
}

bool TreeModel::removeColumns(int column, int count, const QModelIndex& parent)
{
    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    beginRemoveColumns(parent, column, column + count - 1);
    bool res = parentItem->removeData(column, count);
    endRemoveColumns();

    return res;
}

bool TreeModel::removeColumn(int column, const QModelIndex& parent)
{
    return removeColumns(column, 1, parent);
}


void TreeModel::appendChild(TreeItem* childItem, const QModelIndex& parent)
{
    emit layoutAboutToBeChanged({parent});

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    
    parentItem->appendChild(childItem);
    emit layoutChanged({parent});
}


Qt::DropActions TreeModel::supportedDragActions(void) const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::DropActions TreeModel::supportedDropActions(void) const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList TreeModel::mimeTypes(void) const
{
    return treeItemMimes.values();
}

QMimeData* TreeModel::mimeData(const QModelIndexList& indexes) const
{
    if (indexes.empty() || mimeTypes().empty())
        return nullptr;

    TreeItem* parentItem;

    if (!indexes.first().isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(indexes.first().internalPointer());

    TreeItem* childItem = parentItem->child(indexes.first().row());

    if (childItem == nullptr)
        return nullptr;

    QByteArray encodedData = {};
    for (int i = 0; i < childItem->columnCount(); i++)
    {
        encodedData.push_back(childItem->data(i, Qt::DisplayRole).toByteArray());
    }

    QMimeData* mimeData = new QMimeData;
    mimeData->setData(treeItemMimes[childItem->type()], encodedData);

    return mimeData;
}