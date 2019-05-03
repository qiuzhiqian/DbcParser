#ifndef DBCEDITOR_H
#define DBCEDITOR_H

#include <QWidget>

#include "parser.h"

namespace Ui {
class DbcEditor;
}

class DbcEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DbcEditor(QWidget *parent = nullptr);
    ~DbcEditor();

    void showDbcInfo(Parser* ps);
    void showSgInfo(Parser *ps,int row);
    void showEditor(Parser *ps,int row);
    void addBORow(int row,quint16 id,const QString &name,int len,quint16 period);
    void addSGRow(int row, const QString &name, quint8 start, quint8 len, quint8 format, double factor, double offset, double min, double max, const QString &unit);
    void addEditorRow(int row, const QString &name, quint8 start, quint8 len, quint8 format);
    void loadDbc(const QString& fileNmae);

private:
    Ui::DbcEditor *ui;

    QString m_dbcfile;
    Parser* m_ps;
    int m_BOCurrentRow;
public slots:
    void slt_BOCellClick(int row,int column);
};

#endif // DBCEDITOR_H
