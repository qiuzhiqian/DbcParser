#ifndef SGMODEL_H
#define SGMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include "parser.h"

class SgModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SgModel(QObject* parent = nullptr);
    SgModel(QList<SG_>* list,QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QList<SG_>* m_sgList;
    QStringList m_hHeader;
};

#endif // SGMODEL_H
