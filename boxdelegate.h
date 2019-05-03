#ifndef BOXDELEGATE_H
#define BOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class BoxDelegate:public QItemDelegate
{
public:
    BoxDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setValidator(QValidator* valid);
    void setItemEnum(const QStringList& strList);
private:
    QValidator* m_valid;
    QStringList m_enum;
};

#endif // BOXDELEGATE_H
