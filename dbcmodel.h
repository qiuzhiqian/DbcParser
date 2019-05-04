#ifndef DBCMODEL_H
#define DBCMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include "parser.h"

class DbcModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DbcModel(QObject* parent = nullptr);
    DbcModel(QList<BO_>* list,QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QList<BO_>* m_boList;
    QStringList m_hHeader;

Q_SIGNALS:
    //void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) const;
};

#endif // DBCMODEL_H
