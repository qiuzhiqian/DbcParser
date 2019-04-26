#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showDbcInfo(Parser* ps);
    void showSgInfo(Parser *ps,int row);
    void showEditor(Parser *ps,int row);
    void addBORow(int row,quint16 id,const QString &name,int len,quint16 period);
    void addSGRow(int row, const QString &name, quint8 start, quint8 len, quint8 format, double factor, double offset, double min, double max);

private:
    Ui::MainWindow *ui;
    QString m_dbcfile;
    Parser* m_ps;

    int m_BOCurrentRow;

public slots:
    void slt_openDbc();
    void slt_BOCellClick(int row,int column);
};

#endif // MAINWINDOW_H
