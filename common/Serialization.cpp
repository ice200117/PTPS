/**
 *          @file:  Serialization.cpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月16日 16时29分25秒
 *       @version:  none
 *          @note:  
 */


#include    "Serialization.hpp"
#include  <QBuffer>
#include  <stdio.h>
#include "global_def.hpp"

QByteArray Serialization::serialize(QString nodeName, std::list<Resource> lr)
{
    QBuffer buf;
    InfoType in = SendResource;
    buf.open(QBuffer::ReadWrite);
    QDataStream out(&buf);
    out.setVersion(QDataStream::Qt_4_8);
    out << (qint32)in;
    out << nodeName;
    out << (qint32)lr.size();
    std::list<Resource>::iterator it = lr.begin();
    for(   ; it != lr.end() ; it++ )
    {
        //ql.push_back(*it);
        out << *it;
    }
    
    QByteArray ba = qCompress(buf.buffer());
    //QByteArray ba = buf.buffer();
    buf.close();
    return ba;
}

QByteArray Serialization::serialize(Task t, Resource re)
{
    QBuffer buf;
    InfoType in = SendTask;

    buf.open(QBuffer::ReadWrite);
    QDataStream out(&buf);
    out.setVersion(QDataStream::Qt_4_8);
    out << (qint32)in;
    out << t << re;

    QByteArray ba = qCompress(buf.buffer());
    //QByteArray ba = buf.buffer();
    buf.close();

    return ba;
}

QByteArray Serialization::serialize(InfoType ift)
{
    QBuffer buf;

    buf.open(QBuffer::ReadWrite);
    QDataStream out(&buf);
    out.setVersion(QDataStream::Qt_4_8);
    out << (qint32)ift;
    
    QByteArray ba = qCompress(buf.buffer());
    //QByteArray ba = buf.buffer();
    buf.close();
    return ba;

}

InfoType Serialization::deserialize(char *rb, int len)
{
    QByteArray ba;
    ba.setRawData(rb, len);
    ba = qUncompress(ba);
    QBuffer buf; 
    buf.setBuffer(&ba);
    buf.open(QBuffer::ReadWrite);
    QDataStream in;
    in.setVersion(QDataStream::Qt_4_8);
    in.setDevice(&buf);
    InfoType it;
    qint32 tmp;
    in >> tmp;
    it = (InfoType)tmp;
    switch ( it )
    {
        case SendResource :
            // 解析子节点资源的消息内容
            deserializeSendRes(in);
            break;
        case SendTask :
            // 解析Task的消息内容
            deserializeSendTask(in);
            break;
        case SendHeartBeat :
            break;
        default :
            printf("Msg Type is wrong!\n");
            break;
    }
    buf.close();
    return it;
}

void Serialization::deserializeSendRes( QDataStream &in)
{
    int size;
    in >> m_nodeName;
    in >> size;
    idebug("nodeName = %s, size = %d", m_nodeName.toStdString().c_str(), size);

    for( int i = 0 ; i<size ; i++ )
    {
        Resource re;
        in >> re;
        idebug("re's nodeName = %s, rank = %d", re.nodeName.toStdString().c_str(), re.rank);
        m_lr.push_back(re);
    }
}


void Serialization::deserializeSendTask(QDataStream &in)
{
    in >> m_t >> m_re;
}

