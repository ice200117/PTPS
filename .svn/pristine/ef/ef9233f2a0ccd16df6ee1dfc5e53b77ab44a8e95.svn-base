/**
 *          @file:  Serialization.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月16日 16时16分02秒
 *       @version:  none
 *          @note:  
 */
#ifndef  SERIALIZATION_HPP
#define  SERIALIZATION_HPP

#include  <QByteArray>
#include  <QString>
#include    "Task.hpp"
#include    "DispatcherInterface.h"
#include "common_global.h"

class COMMON_EXPORT Serialization
{
    public:
        Serialization(){};
        ~Serialization(){};

    
        QByteArray serialize(QString nodeName, std::list<Resource> lr);
        QByteArray serialize(Task t, Resource re);
        QByteArray serialize(InfoType ift);

        InfoType deserialize(char *rb, int len);

        QString nodeName(){ return m_nodeName; }
        std::list<Resource> lr() { return m_lr; }
        Task& t(){ return m_t; };
        Resource& re() { return m_re; };

    private:

        void deserializeSendRes( QDataStream &in);
        void deserializeSendTask(QDataStream &in);

        QString m_nodeName;
        std::list<Resource> m_lr;

        Task m_t;
        Resource m_re;

};
#endif   /* ----- #ifndef SERIALIZATION_HPP  ----- */

