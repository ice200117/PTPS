#include "InterfaceSingle4Master.h"

//QAtomicPointer<InterfaceSingle4Master> InterfaceSingle4Master::s_instance = new InterfaceSingle4Master;
//
//InterfaceSingle4Master::InterfaceSingle4Master(void)
//{
//}
//
//InterfaceSingle4Master::~InterfaceSingle4Master(void)
//{
//}

QString InterfaceSingle4Master::slotDispatcherTask2Slave( Task pt, Resource re)
{
    return emit signalDispatcherTask2TaskController(pt, re);
}
