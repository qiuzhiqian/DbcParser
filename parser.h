#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include "dbctable.h"

class VAL{
public:
    QString name;
    quint64 val;
};

class PERIOD{
public:
    quint16 m_id;
    quint16 m_period;
};

class VAL_TABLE{
public:
    QString m_name;
    QList<VAL> m_valList;
};

class SG_ {
public:
    QString m_name;
    quint8 m_startBit;
    quint8 m_bitLen;
    quint8 m_type;
    double m_factor;
    double m_offset;
    double m_min;
    double m_max;
    QString m_uint;
    QList<VAL> m_valList;
};

class BO_ {
public:
    QString m_name;
    quint16 m_id;
    quint8 m_length;
    quint16 m_period;
    QList<SG_> m_sgList;
};

class Parser:public QObject
{
    Q_OBJECT
public:
    Parser();
    bool doThing(const QString& file);
    QList<BO_>& getBOList();
private:
    QString m_version;
    QList<BO_> m_boList;
    int findValTblIndex(QString name,const QList<VAL_TABLE>& valList);
    int findPeriodIndex(quint16 id,const QList<PERIOD>& pdList);
};

#endif // PARSER_H
