#include "gui/treeItem.hpp"

#include <QIcon>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QVector>

#include <iostream>


QMap <TreeItemType, QString> treeItemMimes {
    {TreeItemGroup, "application/vnd.crevis.scene.group"},
    {TreeItemMesh, "application/vnd.crevis.scene.light"},
    {TreeItemMesh, "application/vnd.crevis.scene.mesh"},
    {TreeItemCamera, "application/vnd.crevis.scene.camera"}
};


TreeItem::TreeItem(QString name, TreeItemType type, QVector<QVariant> data, TreeItem* parent) : m_name(name), m_type(type), m_data(data), m_parent(parent), m_children({})
{

}

TreeItem::~TreeItem()
{
    qDeleteAll(m_children);
}


TreeItemType TreeItem::type(void) const
{
    return m_type;
}

QIcon TreeItem::icon(void) const
{
    switch (m_type)
    {
        case TreeItemGroup:
            return QIcon::fromTheme("folder");
        case TreeItemMesh:
            return QIcon::fromTheme("emblem-shared");
        case TreeItemCamera:
            return QIcon::fromTheme("camera-video");
        default:
            return QIcon::fromTheme("dialog-question");
    }
}

TreeItem* TreeItem::parent(void) const
{
    return m_parent;
}

void TreeItem::setParent(TreeItem* parent)
{
    m_parent = parent;
}

TreeItem* TreeItem::child(int row) const
{
    if (row < 0 || row >= childrenCount())
        return nullptr;
    return m_children[row];
}

int TreeItem::childrenCount(void) const
{
    return m_children.size();
}

int TreeItem::columnCount(void) const
{
    return m_data.size() + 1;
}

int TreeItem::row(void) const
{
    if (m_parent)
        return m_parent->m_children.indexOf(const_cast<TreeItem*>(this));

    // if this instance is the rootItem of a TreeModel set its row to 0
    // this choice is arbitrary and insignificant because this information is never used by the model
    return 0;
}


QVariant TreeItem::data(int column, int role) const
{
    if (column < 0 || column >= columnCount())
        return QVariant();

    if (column == 0)
    {
        if (role == Qt::DecorationRole)
            return icon();
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return m_name;
        return QVariant();
    }

    return m_data[column - 1];
}

Qt::ItemFlags TreeItem::dataFlags(int column) const
{
    Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;

    if (m_type != TreeItemGroup)
        defaultFlags |= Qt::ItemNeverHasChildren;
    else
        defaultFlags |= Qt::ItemIsDropEnabled;

    if (column == 0)
        return Qt::ItemIsEditable | defaultFlags;
    return Qt::ItemNeverHasChildren | defaultFlags;
}

bool TreeItem::setData(int column, int role, const QVariant& value)
{
    if (column < 0 || column >= columnCount())
        return false;

    if (column == 0)
    {
        if (role == Qt::EditRole)
        {
            m_name = value.toString();
            return true;
        }
        return false;
    }
        
    m_data[column - 1] = value;
    return true;
}

bool TreeItem::insertEmptyData(int column, int count)
{
    // new columns cannot be created before the first column displaying the name
    if (column < 1 || column > columnCount())
        return false;

    m_data.insert(column - 1, count, QVariant());
    return true;
}

bool TreeItem::setChild(int row, TreeItem* child)
{
    if (row < 0 || row >= childrenCount())
        return false;

    child->setParent(this);
    m_children[row] = child;
    
    return true;
}

bool TreeItem::removeData(int column, int count)
{
    if (column < 1 || column - 1 >= columnCount() || column + count - 2 >= columnCount())
        return false;

    m_data.remove(column - 1, count);
    return true;
}


void TreeItem::appendChild(TreeItem* child)
{
    child->setParent(this);
    m_children.push_back(child);
}

bool TreeItem::insertEmptyChildren(int row, int count)
{
    if (row < 0 || row > childrenCount())
        return false;
    
    m_children.insert(row, count, nullptr);
    return true;
}

bool TreeItem::removeChildren(int row, int count)
{
    if (row < 0 || row >= childrenCount() || row + count - 1 >= childrenCount())
        return false;

    m_children.remove(row, count);
    return true;
}