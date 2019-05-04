#include "sgmodel.h"

SgModel::SgModel(QObject *parent):QAbstractTableModel(parent)
{
    m_hHeader << "Name" <<"Start"<<"Length"<<"Format"<<"Factor"<<"Offset"<<"Min"<<"Max"<<"Unit";
}

SgModel::SgModel(QList<SG_>* list,QObject *parent):QAbstractTableModel(parent),m_sgList(list)
{
    m_hHeader << "Name" <<"Start"<<"Length"<<"Format"<<"Factor"<<"Offset"<<"Min"<<"Max"<<"Unit";
}

int SgModel::rowCount(const QModelIndex &parent) const
{
    return m_sgList->size();//5行
}

int SgModel::columnCount(const QModelIndex &parent) const
{
    return 9;//5列
}

QVariant SgModel::data(const QModelIndex &index, int role) const
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
        case 0:{
            return m_sgList->at(index.row()).m_name;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 1:{
            return m_sgList->at(index.row()).m_startBit;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 2:{
            return m_sgList->at(index.row()).m_bitLen;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 3:{
            return m_sgList->at(index.row()).m_type;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 4:{
            return m_sgList->at(index.row()).m_factor;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 5:{
            return m_sgList->at(index.row()).m_offset;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 6:{
            return m_sgList->at(index.row()).m_min;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 7:{
            return m_sgList->at(index.row()).m_max;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 8:{
            return m_sgList->at(index.row()).m_unit;//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        }

    }
    return QVariant();
}

QVariant SgModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool SgModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole && value.isValid() && m_sgList!=nullptr){

        switch(index.column()){
        case 0:{
            //int id = value.toInt();
            QString name = value.toString();
            SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
            tempsg.m_name = name;
            break;
        }
        case 1:{
            int start = value.toInt();
            SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
            tempsg.m_startBit = static_cast<quint8>(start);
            break;
        }
        case 2:{
            int bitlen = value.toInt();
            SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
            tempsg.m_bitLen = static_cast<quint8>(bitlen);
            break;
        }
        case 3:{
            int type = value.toInt();
            SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
            tempsg.m_type = static_cast<quint8>(type);
            break;
        }
        case 4:{
            bool isOk =false;
            double factor = value.toDouble(&isOk);
            if(isOk){
                SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
                tempsg.m_factor = factor;
            }
            else{
                return false;
            }
            break;
        }
        case 5:{
            bool isOk =false;
            double offset = value.toDouble(&isOk);
            if(isOk){
                SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
                tempsg.m_offset = offset;
            }
            else{
                return false;
            }
            break;
        }
        case 6:{
            bool isOk =false;
            double min = value.toDouble(&isOk);
            if(isOk){
                SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
                tempsg.m_min = min;
            }
            else{
                return false;
            }
            break;
        }
        case 7:{
            bool isOk =false;
            double max = value.toDouble(&isOk);
            if(isOk){
                SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
                tempsg.m_max = max;
            }
            else{
                return false;
            }
            break;
        }
        case 8:{
            QString unit = value.toString();
            SG_& tempsg = const_cast<SG_&>(m_sgList->at(index.row()));
            tempsg.m_unit = unit;
            break;
        }
        }
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags SgModel::flags(const QModelIndex &index) const{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);
    flag |= Qt::ItemIsEditable;
    return flag;
}
