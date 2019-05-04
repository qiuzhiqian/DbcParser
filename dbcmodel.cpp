#include "dbcmodel.h"
#include <QDebug>

DbcModel::DbcModel(QObject *parent):QAbstractTableModel(parent)
{
    m_hHeader << "Id" <<"Name"<<"Length"<<"Period";
}

DbcModel::DbcModel(QList<BO_>* list,QObject *parent):QAbstractTableModel(parent),m_boList(list)
{
    m_hHeader << "Id" <<"Name"<<"Length"<<"Period";
}

int DbcModel::rowCount(const QModelIndex &parent) const
{
    return m_boList->size();//5行
}

int DbcModel::columnCount(const QModelIndex &parent) const
{
    return 4;//5列
}

QVariant DbcModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())        //安全判断
    {
        return QVariant();
    }
    if(Qt::TextAlignmentRole == role)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else if(Qt::DisplayRole == role)            //这里这样写是为了过滤掉其他role(例如过滤掉checkBox)
    {
        switch(index.column()){
        //case 0:{
        //    return index.row();//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        //}
        case 0:{
            return m_boList->at(index.row()).m_id;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 1:{
            return m_boList->at(index.row()).m_name;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 2:{
            return m_boList->at(index.row()).m_length;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 3:{
            return m_boList->at(index.row()).m_period;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        }

    }
    return QVariant();
}

QVariant DbcModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole != role)
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)       //横向头
    {
        return m_hHeader.at(section);//横向头一次递增
    }
    else if(orientation == Qt::Vertical)    //纵向头
    {
        return section + 1;//纵向头依次递增
    }
    return QVariant();
}

bool DbcModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole && value.isValid() && m_boList!=nullptr){

        switch(index.column()){
        //case 0:{
        //    //int id = value.toInt();
        //    break;
        //}
        case 0:{
            int id = value.toInt();
            BO_& tempbo = const_cast<BO_&>(m_boList->at(index.row()));
            tempbo.m_id = static_cast<quint16>(id);
            break;
        }
        case 1:{
            QString name = value.toString();
            BO_& tempbo = const_cast<BO_&>(m_boList->at(index.row()));
            tempbo.m_name = name;
            break;
        }
        case 2:{
            int len = value.toInt();
            BO_& tempbo = const_cast<BO_&>(m_boList->at(index.row()));
            tempbo.m_length = static_cast<quint8>(len);
            break;
        }
        case 3:{
            int period = value.toInt();
            BO_& tempbo = const_cast<BO_&>(m_boList->at(index.row()));
            tempbo.m_period = static_cast<quint16>(period);
            break;
        }
        }
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags DbcModel::flags(const QModelIndex &index) const{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);
    flag |= Qt::ItemIsEditable;
    return flag;
}
