#include "boxdelegate.h"
#include <QComboBox>

BoxDelegate::BoxDelegate(QObject *parent): QItemDelegate(parent),m_valid(nullptr)
{

}

QWidget *BoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    //QSpinBox *editor = new QSpinBox(parent);
    //editor->setMinimum(1);
    //editor->setMaximum(100);
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(m_enum);
    return editor;
}
void BoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //int value = index.model()->data(index, Qt::EditRole).toInt();
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *boxEdit = static_cast<QComboBox*>(editor);
    if(m_valid != nullptr){
        boxEdit->setValidator(m_valid);
    }

    boxEdit->setCurrentText(value);
}
void BoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->interpretText();
    //int value = spinBox->value();
    //model->setData(index, value, Qt::EditRole);
    QComboBox *boxEdit = static_cast<QComboBox*>(editor);
    QString value = boxEdit->currentText();
    model->setData(index,value,Qt::EditRole);
}
void BoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void BoxDelegate::setValidator(QValidator* valid){
    m_valid = valid;
}

void BoxDelegate::setItemEnum(const QStringList& strList){
    m_enum = strList;
}
