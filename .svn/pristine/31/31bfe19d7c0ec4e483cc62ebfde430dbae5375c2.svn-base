#pragma once
#include "InterfaceSingle4Slave_Global.h"
#include "../common/DispatcherInterface.h"

class INTERFACESINGLE4SLAVE_IMPEXP InterfaceSingle4Slave : public Slave2MasterInterface
{
	Q_OBJECT

//public:
//	static InterfaceSingle4Slave &getInstance(void)
//	{
//		return *s_instance;
//	}
protected:
	void run(){};

public slots:
	QString slotHandleResult2Master(Task, Resource);
	QString slotSendRes2Master(QString nodeName, std::list<Resource> lr);

signals:
	QString signalHandleResult2JobDispatcher(Task, Resource);
	QString signalSendRes2JobDispatcher(std::string, std::list<Resource>);

//private:
//	InterfaceSingle4Slave(void);//禁止构造函数
//	virtual ~InterfaceSingle4Slave(void);
//	InterfaceSingle4Slave(const InterfaceSingle4Slave &);//禁止拷贝构造函数
//	InterfaceSingle4Slave & operator=(const InterfaceSingle4Slave &);//禁止赋值拷贝函数
//
//	static QAtomicPointer<InterfaceSingle4Slave> s_instance;/*!<使用原子指针,默认初始化为0。*/
};