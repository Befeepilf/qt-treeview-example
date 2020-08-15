#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "store.hpp"
#include "gui/treeItem.hpp"
#include "scene/itemVariant.hpp"

#include <QAbstractItemModel>
#include <QMap>
#include <QMimeData>
#include <QModelIndex>
#include <QModelIndexList>
#include <QStringList>
#include <QVariant>

#include <vector>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    
    public:
        explicit TreeModel(QObject* parent = nullptr);
        ~TreeModel();

        void update(store::model state);
        void parseSceneTree(TreeItem* parentItem, std::vector<Scene::ItemVariant> sceneTree);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        QModelIndex parent(const QModelIndex& index) const override;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

        QVariant headerData(int column, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        bool setHeaderData(int column, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

        QVariant data(const QModelIndex& index, int role) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
        bool setItemData(const QModelIndex& index, const QMap<int, QVariant>& roles) override;

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

        QStringList mimeTypes(void) const override;
        QMimeData* mimeData(const QModelIndexList& indexes) const override;
        bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent = QModelIndex()) override;
        TreeItem* mimeDataToTreeItem(const QMimeData* mimeData);

    private:
        TreeItem* rootItem;
};

#endif