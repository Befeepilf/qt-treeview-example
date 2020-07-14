#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "treeItem.hpp"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    
    public:
        TreeModel();
        ~TreeModel();

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        QModelIndex parent(const QModelIndex& index) const override;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

        QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        bool setHeaderData(int column, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

        QVariant data(const QModelIndex& index, int role) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

        Qt::ItemFlags flags(const QModelIndex& index) const override;

        bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
        bool setRow(int row, TreeItem* item, const QModelIndex& parent = QModelIndex());
        bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
        bool removeRow(int row, const QModelIndex& parent = QModelIndex());
        bool insertColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
        bool removeColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
        bool removeColumn(int column, const QModelIndex& parent = QModelIndex());

        void appendChild(TreeItem* child, const QModelIndex& parent = QModelIndex());

        Qt::DropActions supportedDragActions(void) const;
        Qt::DropActions supportedDropActions(void) const;

    private:
        TreeItem* rootItem;
};

#endif