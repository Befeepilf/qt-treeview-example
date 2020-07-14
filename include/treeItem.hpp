#ifndef TREE_ITEM_H
#define TREE_ITEM_H

#include <QIcon>
#include <QString>
#include <QVariant>
#include <QVector>

enum TreeItemType {TreeItemGroup, TreeItemMesh, TreeItemCamera};

class TreeItem
{
    public:
        explicit TreeItem(QString name, TreeItemType type, QVector<QVariant> data = {}, TreeItem* parent = nullptr);
        ~TreeItem();

        TreeItem* parent(void) const;
        void setParent(TreeItem* parent);
        TreeItem* child(int row) const;

        int childrenCount(void) const;
        int columnCount(void) const;
        int row(void) const;

        QVariant data(int column, int role) const;
        Qt::ItemFlags dataFlags(int column) const;
        bool setData(int column, int role, const QVariant& value);
        bool insertEmptyData(int column, int count);
        bool removeData(int column, int count);

        void appendChild(TreeItem* child);
        bool insertEmptyChildren(int row, int count);
        bool setChild(int row, TreeItem* child);
        bool removeChildren(int row, int count);


    private:
        QString m_name;
        TreeItemType m_type;
        QVector<QVariant> m_data;
        TreeItem* m_parent;
        QVector<TreeItem*> m_children;

        QIcon icon(void) const;
};

#endif