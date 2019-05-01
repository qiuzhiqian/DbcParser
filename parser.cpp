#include "parser.h"

#include <QFile>
#include <QRegExp>
#include <QDebug>

Parser::Parser()
{

}

bool Parser::doThing(const QString &file){
    QFile fileVal(file);
    if (!fileVal.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QList<VAL_TABLE> valTblList;
    QList<PERIOD> periodList;

    QStringList context;
    //VAL_TABLE_ ([0-9a-zA-Z_]+) (\d{0,8} "[\S ]+" )+;
    QRegExp rx_enum(tr("VAL_TABLE_ ([0-9a-zA-Z_]+) (\\d{0,8} \"[\\S ]+\" )+;"));
    //BO_ \d{1,4} \S+: \d{1} Vector__XXX
    QRegExp rx_frame(tr("BO_ (\\d{1,4}) (\\S+): (\\d{1}) Vector__XXX"));
    //SG_ \S+ : \d{1,2}\|\d{1,2}@[01]{1}\+ \([0-9.]+,[0-9.]+\) \[\d{1,8}\|\d{1,8}\] "\S{0,}" Vector__XXX
    //SG_ (\S+) : (\d{1,2})\|(\d{1,2})@([01]{1})\+ \(([0-9.\-]+),([0-9.\-]+)\) \[([0-9.\-]+)\|([0-9.\-]+)\] \"(\S{0,})\" Vector__XXX
    QRegExp rx_item(tr("SG_ (\\S+) : (\\d{1,2})\\|(\\d{1,2})@([01]{1})[\\+\\-] \\(([0-9.\\-eE\\+]+),([0-9.\\-eE\\+]+)\\) \\[([0-9.\\-eE\\+]+)\\|([0-9.\\-eE\\+]+)\\] \"(\\S{0,})\" Vector__XXX"));
    //BA_ "GenMsgCycleTime" BO_ 657 10;
    QRegExp rx_period(tr("BA_ \"GenMsgCycleTime\" BO_ (\\d+) (\\d+);"));
    while (!fileVal.atEnd()) {
        //context.append(fileVal.readLine());
        //process_line(line);

        QString line = fileVal.readLine();
        if(line.size()<=1){
            continue;
        }
        //int pos = rx_frame.indexIn(line);
        if (rx_frame.indexIn(line) > -1) {
            QStringList mathstr = rx_frame.capturedTexts();
            //qDebug()<<"cnt:"<<mathstr.size();
            //int len = mathstr.size();
            //QString output;
            //for(int i=1;i<len;i++){
            //    output+=mathstr.at(i)+" ";
            //}
            //qDebug()<<output;
            BO_ tempBo;
            tempBo.m_id = static_cast<quint16>(mathstr.at(1).toInt());
            tempBo.m_name = mathstr.at(2);
            tempBo.m_length = static_cast<quint8>(mathstr.at(3).toInt());

            while(!fileVal.atEnd()){
                QString line_item = fileVal.readLine();
                //qDebug()<<line_item;
                int pos = rx_item.indexIn(line_item);
                if (pos > -1) {
                    QStringList mathstr = rx_item.capturedTexts();
                    //qDebug()<<"cnt:"<<mathstr.size();
                    //int len = mathstr.size();
                    //QString output;
                    //for(int i=1;i<len;i++){
                    //    output+=mathstr.at(i)+" ";
                    //}
                    //qDebug()<<output;
                    SG_ tempSg;
                    tempSg.m_name = mathstr.at(1);
                    tempSg.m_startBit = static_cast<quint8>(mathstr.at(2).toInt());
                    tempSg.m_bitLen = static_cast<quint8>(mathstr.at(3).toInt());
                    tempSg.m_type = static_cast<quint8>(mathstr.at(4).toInt());
                    tempSg.m_factor = mathstr.at(5).toDouble();
                    tempSg.m_offset = mathstr.at(6).toDouble();
                    tempSg.m_min = mathstr.at(7).toDouble();
                    tempSg.m_max = mathstr.at(8).toDouble();
                    tempSg.m_uint = mathstr.at(9);
                    tempBo.m_sgList.append(tempSg);
                }
                else{
                    break;
                }
            }
            m_boList.append(tempBo);
        }
        else if(rx_enum.indexIn(line) > -1){
            QStringList mathstr = rx_enum.capturedTexts();
            //qDebug()<<"cnt:"<<mathstr.size();
            int len = mathstr.size();
            QString output;
            VAL_TABLE tempTbl;
            for(int i=1;i<len;i++){

                if(i>1){
                    int pos = 0;
                    QString str = mathstr.at(i);
                    QRegExp rx_param(tr("(\\d{0,8}) \"([\x0A-\x21\x23-\xff]+)\" "));
                    while ((pos = rx_param.indexIn(str, pos)) != -1) {
                          //qDebug() << rx_param.cap(1) << " " << rx_param.cap(2);
                        //output+=rx_param.cap(1) + " " + rx_param.cap(2);
                        VAL val;
                        val.val = static_cast<quint64>(rx_param.cap(1).toInt());
                        val.name=rx_param.cap(2);
                          tempTbl.m_valList.append(val);
                          pos += rx_param.matchedLength();
                      }
                }
                else{
                    //output+=mathstr.at(i)+" ";
                    tempTbl.m_name = mathstr.at(i);
                }
            }
            valTblList.append(tempTbl);
        }
        else if(rx_period.indexIn(line) > -1){
            //qDebug()<<"period: "<<rx_period.cap(1)<<" "<<rx_period.cap(2);
            PERIOD pd;
            pd.m_id = static_cast<quint16>(rx_period.cap(1).toInt());
            pd.m_period = static_cast<quint16>(rx_period.cap(2).toInt());
            periodList.append(pd);
        }
    }
    //QString context = fileVal.readAll();

    for(auto& item:m_boList){
        for(auto& var:item.m_sgList){
            int index_val = findValTblIndex(var.m_name,valTblList);
            if(index_val>=0){
                //qDebug()<<"match name:"<<var.m_name << " index:"<<index;
                for(auto enumvar:valTblList.at(index_val).m_valList){
                    var.m_valList.append(enumvar);
                }
            }
        }

        int index_period = findPeriodIndex(item.m_id,periodList);
        if(index_period>=0){
            item.m_period = periodList.at(index_period).m_period;
        }
    }

    return true;
}

int Parser::findValTblIndex(QString name,const QList<VAL_TABLE>& valtablist){
    int i=0;
    for(auto item:valtablist){
        if(item.m_name == name){
            return i;
        }
        i++;
    }
    return -1;
}

int Parser::findPeriodIndex(quint16 id, const QList<PERIOD> &pdList){
    int i=0;
    for(auto item:pdList){
        if(item.m_id == id){
            return i;
        }
        i++;
    }
    return -1;
}

QList<BO_>& Parser::getBOList(){
    return m_boList;
}

CPos Parser::posCalc(quint8 start, quint8 offset, quint8 format){
    //7,15,23,31,39,47,55,63
    CPos pos;
    int stabyte = start/8;
    int sta = stabyte*8;

    int tempOffset = start+offset-sta;

    int offByte = tempOffset/8;
    pos.bitIndex = tempOffset%8;

    if(format == 1){
        pos.byteIndex = stabyte+offByte;
    }
    else{
        pos.byteIndex = stabyte-offByte;
    }
    return pos;
}

CPos Parser::offsetToIndex(quint8 start, quint8 offset, quint8 format){
    CPos pos;
    int stabyte = start/8;
    int sta = stabyte*8+7;
    int len =sta- start + offset;

    int deltByte = len/8;
    pos.bitIndex = len%8;

    if(format == 1){
        pos.byteIndex = sta/8+deltByte;
    }
    else{
        pos.byteIndex = sta/8-deltByte;
    }
    return pos;
}

CPos Parser::indexToPos(int index){
    CPos pos;
    pos.byteIndex = index/8;
    pos.bitIndex = 7- (index%8);
}
