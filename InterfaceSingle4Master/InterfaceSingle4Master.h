#pragma once
#include "InterfaceSingle4Master_Global.h"
#include "../common/DispatcherInterface.h"

class INTERFACESINGLE4MASTER_IMPEXP InterfaceSingle4Master : public Master2SlaveInterface
{
	Q_OBJECT

//public:
//	static InterfaceSingle4Master &getInstance(void)
//	{
//		return *s_instance;
//	}
protected:
	void run(){};

public slots:
	QString slotDispatcherTask2Slave(Task, Resource);

signals:
	QString signalDispatcherTask2TaskController(Task, Resource);

//private:
//	InterfaceSingle4Master(void);//��ֹ���캯��
//	virtual ~InterfaceSingle4Master(void);
//	InterfaceSingle4Master(const InterfaceSingle4Master &);//��ֹ�������캯��
//	InterfaceSingle4Master & operator=(const InterfaceSingle4Master &);//��ֹ��ֵ��������
//
//	static QAtomicPointer<InterfaceSingle4Master> s_instance;/*!<ʹ��ԭ��ָ��,Ĭ�ϳ�ʼ��Ϊ0��*/
};