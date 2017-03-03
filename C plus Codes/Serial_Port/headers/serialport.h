#include <Windows.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include <sstream>
#include <time.h>
#include "atlstr.h"

using namespace std;

#define DWINQUEUE 1024
#define DWOUTQUEUE 1024
#define READINTERVALTIMEOUT 1000
#define READTOTALTIEMOUTMULTIPLIER  500
#define READTOTALTIMEOUTCONSTANT 500
#define WRITETOTALTIMEOUTMULTIPLIER 500
#define WRITETOTALTIMEOUTCONSTANT 1000
#define TIMER 5000
//#define TIMEOUT

class SerialPort {

public:
	LONG getSerialPortNames();	//������д���
	BOOL getSerialPortResource(CString serialPortNumber);	//��þ��
	void StartSerialPort(CString serialPortName, int baudRate, int parity, int stopBits, int byteSize);		//���Ӵ���,����ͨ��
	char* ReadSerialPort();		//�Ӵ��ڶ�ȡ��Ϣ

	bool WriteSerialPort(char*& data);	//�������ݸ�����

	SerialPort();	//���캯��
	~SerialPort();		//��������

	HANDLE hCom;	//���
	CString *serialPortNameList;	//���ں��б�
	DCB dcb;		//���ڲ������ò���
	int portCount;		//��������
	CString errorInfo;	//������Ϣ
	BOOL serialStates;		//����״̬
	BOOL blockFlags;	
	bool endflags;	//������־
	CString str;	
	int tempurature	;	//�¶�
	int wet ;	//ʪ��
};