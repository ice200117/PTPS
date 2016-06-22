#include "InterfaceSingle4Slave.h"
#include    "../common/global_def.hpp"

//QAtomicPointer<InterfaceSingle4Slave> InterfaceSingle4Slave::s_instance = new InterfaceSingle4Slave;
//
//InterfaceSingle4Slave::InterfaceSingle4Slave(void)
//{
//}
//
//InterfaceSingle4Slave::~InterfaceSingle4Slave(void)
//{
//}

QString InterfaceSingle4Slave::slotHandleResult2Master( Task t, Resource r)
{
	return emit signalHandleResult2JobDispatcher(t, r);
}

QString InterfaceSingle4Slave::slotSendRes2Master(QString nodeName, std::list<Resource> lr)
{
	return emit signalSendRes2JobDispatcher(nodeName.toStdString(), lr);
}
