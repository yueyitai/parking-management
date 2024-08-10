#include "addstaffwindow.h"

addstaffwindow::addstaffwindow(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant addstaffwindow::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex addstaffwindow::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex addstaffwindow::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int addstaffwindow::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int addstaffwindow::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant addstaffwindow::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
