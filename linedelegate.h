#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QLineEdit>
#include <QSpinBox>

class LineDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    LineDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
            const QModelIndex &index) const
        {
            //QSpinBox *editor = new QSpinBox(parent);
            //editor->setMinimum(1);
            //editor->setMaximum(100);
            QLineEdit *editor = new QLineEdit(parent);
            return editor;
        }
        void setEditorData(QWidget *editor, const QModelIndex &index) const
        {
            //int value = index.model()->data(index, Qt::EditRole).toInt();
            //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
            //spinBox->setValue(value);
            QString value = index.model()->data(index, Qt::EditRole).toString();
            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            if(m_valid != nullptr){
                lineEdit->setValidator(m_valid);
            }

            lineEdit->setText(value);
        }
        void setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex &index) const
        {
            //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
            //spinBox->interpretText();
            //int value = spinBox->value();
            //model->setData(index, value, Qt::EditRole);
            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            QString value = lineEdit->text();
            model->setData(index,value,Qt::EditRole);
        }
        void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index) const
        {
            editor->setGeometry(option.rect);
        }

        void setValidator(QValidator* valid){
            m_valid = valid;
        }
private:
        QValidator* m_valid;
};

#endif // LINEDELEGATE_H
