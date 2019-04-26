#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->editorList->setRowCount(1);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            ui->editorList->setColumnWidth(i*8+j+1,20);
        }
        ui->editorList->setSpan(0,i*8+1,1,8);

        QString textStr="Byte "+QString::number(i);

        QTableWidgetItem*    newItem = new QTableWidgetItem();
        ui->editorList->setItem(0, i*8+1, newItem);
        newItem->setTextAlignment(Qt::AlignCenter);
        newItem->setText(textStr);
        if( i%2 == 0 ){
            newItem->setBackgroundColor(QColor(200,200,200));
        }

        //itemGet->setTextAlignment(Qt::AlignHCenter);
        //itemGet->setText("byte0");
    }


    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slt_openDbc()));

    connect(ui->boList,SIGNAL(cellClicked(int,int)),this,SLOT(slt_BOCellClick(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slt_openDbc(){
    QString homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
    m_dbcfile = QFileDialog::getOpenFileName(this,
          tr("Open Dbc File"), homePath, tr("Dbc Files (*.dbc)"));
    ui->label->setText(m_dbcfile);
    m_ps = new Parser();
    m_ps->doThing(m_dbcfile);

    showDbcInfo(m_ps);
    showEditor(m_ps,m_BOCurrentRow);
}

void MainWindow::showDbcInfo(Parser *ps){
    int row = 0;
    for(auto item:ps->getBOList()){
        qDebug()<<"id:"<<item.m_id<<" name:"<<item.m_name <<" len:"<<item.m_length<<" period:"<<item.m_period;
        addBORow(row,item.m_id,item.m_name,item.m_length,item.m_period);
        for(auto var:item.m_sgList){
            qDebug()<<"name:"<<var.m_name <<" start:"<<var.m_startBit<<" len:"<<var.m_bitLen<<" type:"<<var.m_type
                   <<" factor:"<<var.m_factor<<" offset:"<<var.m_offset<<" min:"<<var.m_min<<" max:"<<var.m_max<<" unit:"<<var.m_uint;
            int i=0;
            for(auto enumVal:var.m_valList){
                qDebug()<<"["<<i<<"]"<<" val:"<<enumVal.val <<" name:"<<enumVal.name ;
                i++;
            }
        }
        row++;
    }

    m_BOCurrentRow = ui->boList->currentRow();
    if(m_BOCurrentRow<0){
        m_BOCurrentRow = 0;
        ui->boList->setCurrentCell(0,0);
    }
    qDebug()<<"current row:"<<m_BOCurrentRow;
    showSgInfo(ps,m_BOCurrentRow);
}

void MainWindow::showSgInfo(Parser *ps,int row){
    int index = 0;
    ui->sgList->setRowCount(0);
    for(auto var:ps->getBOList().at(row).m_sgList){
        addSGRow(index,var.m_name,var.m_startBit,var.m_bitLen,var.m_type,var.m_factor,var.m_offset,var.m_min,var.m_max);
        index++;
    }
}

void MainWindow::showEditor(Parser *ps, int row){
    ui->editorList->setRowCount(1);
    ui->editorList->setSpan(0,3,1,5);
}

void MainWindow::addBORow(int row,quint16 id,const QString &name,int len,quint16 period){
    ui->boList->insertRow(row);
    QTableWidgetItem *rowLine = new QTableWidgetItem();
    rowLine->setText(QString::number(row+1));
    ui->boList ->setItem(row, 0, rowLine);

    QTableWidgetItem *idLine = new QTableWidgetItem();
    idLine->setText(QString::number(id,16).toUpper());
    ui->boList ->setItem(row, 1, idLine);

    QTableWidgetItem *nameLine = new QTableWidgetItem();
    nameLine->setText(name);
    ui->boList ->setItem(row, 2, nameLine);

    QTableWidgetItem *lenLine = new QTableWidgetItem();
    lenLine->setText(QString::number(len));
    ui->boList ->setItem(row, 3, lenLine);

    QTableWidgetItem *periodLine = new QTableWidgetItem();
    periodLine->setText(QString::number(period));
    ui->boList ->setItem(row, 4, periodLine);
}

void MainWindow::addSGRow(int row,const QString &name,quint8 start,quint8 len,quint8 format,double factor,double offset,double min,double max){
    ui->sgList->insertRow(row);
    QTableWidgetItem *nameLine = new QTableWidgetItem();
    nameLine->setText(name);
    ui->sgList ->setItem(row, 0, nameLine);

    QTableWidgetItem *startLine = new QTableWidgetItem();
    startLine->setText(QString::number(start));
    ui->sgList ->setItem(row, 1, startLine);

    QTableWidgetItem *lenLine = new QTableWidgetItem();
    lenLine->setText(QString::number(len));
    ui->sgList ->setItem(row, 2, lenLine);

    QTableWidgetItem *formatLine = new QTableWidgetItem();
    formatLine->setText(QString::number(format));
    ui->sgList ->setItem(row, 3, formatLine);

    QTableWidgetItem *factorLine = new QTableWidgetItem();
    factorLine->setText(QString::number(factor,'f'));
    ui->sgList ->setItem(row, 4, factorLine);

    QTableWidgetItem *offsetLine = new QTableWidgetItem();
    offsetLine->setText(QString::number(offset,'f'));
    ui->sgList ->setItem(row, 5, offsetLine);

    QTableWidgetItem *minLine = new QTableWidgetItem();
    minLine->setText(QString::number(min,'f'));
    ui->sgList ->setItem(row, 6, minLine);

    QTableWidgetItem *maxLine = new QTableWidgetItem();
    maxLine->setText(QString::number(max,'f'));
    ui->sgList ->setItem(row, 7, maxLine);
}

void MainWindow::slt_BOCellClick(int row,int column){
    qDebug()<< "row:"<<row<<" column:"<<column;
    if(row!= m_BOCurrentRow){
        m_BOCurrentRow = row;
        showSgInfo(m_ps,m_BOCurrentRow);
    }
}
