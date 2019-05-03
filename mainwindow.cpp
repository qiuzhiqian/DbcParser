#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QFileInfo>

#include "dbceditor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_dbcList.clear();
    //ui->splitter->setStretchFactor(0,3);
    //ui->splitter->setStretchFactor(1,7);
    ui->tabWidget->clear();
    //ui->tabWidget->removeTab(0);
    //ui->tabWidget->removeTab(0);
    QList<int> sizes;
    sizes.append(200);
    sizes.append(700);
    ui->splitter->setSizes(sizes);

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slt_openDbc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slt_openDbc(){
    QString homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0);
    QStringList dbcfileList = QFileDialog::getOpenFileNames(this,
          tr("Open Dbc File"), homePath, tr("Dbc Files (*.dbc)"));

    for(auto item:dbcfileList){
        m_dbcList.append(item);
        QFileInfo fi(item);
        DbcEditor* editor=new DbcEditor(this);

        ui->listWidget->addItem(fi.fileName());
        ui->tabWidget->addTab(editor,fi.fileName());
        editor->loadDbc(item);
    }
}
