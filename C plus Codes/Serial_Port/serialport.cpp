
//#include "stdafx.h"
#include "serialport.h"

#define PORTLISTBUFFERSIZE 8		//�������8������
#define MAX_LENGTH 256
#define LPDATABUFFER 25
#define BUFFERSIZE 20

char serialContent[20] = "";

//SerialPort serialHandle;	//��

	//��ȡ������
	LONG SerialPort::getSerialPortNames() {
		LPCTSTR lpSubKey =L"HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
		HKEY hKey;
		CString portNameListTemp[PORTLISTBUFFERSIZE];
		long result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey);
		if (result == ERROR_SUCCESS) {
			long status;
			wchar_t serialPortValueName[MAX_LENGTH];
			DWORD serialPortValueNameSize;
			DWORD lpcbData;
			DWORD dwIndex = 0;
			unsigned char lpData[LPDATABUFFER];
			serialPortValueNameSize = sizeof(serialPortValueName);
			lpcbData = sizeof(lpData);
			do {
				status = RegEnumValue(hKey, dwIndex, serialPortValueName, &serialPortValueNameSize, NULL, NULL, lpData, &lpcbData);
				if (status == ERROR_SUCCESS) {
					for (int i = 1; i < lpcbData / 2; i++)
					{
						lpData[i] = lpData[i * 2];
					}
					portNameListTemp[dwIndex] = CString(lpData);
					dwIndex++;
				}

				serialPortValueNameSize = sizeof(serialPortValueName);
				lpcbData = sizeof(lpData);

			} while (!status);

			RegCloseKey(hKey);
			portCount = dwIndex;
			if (!portCount)
			{
				errorInfo = L"NO SERIAL PORT AVALIBLE";
				return 2;
			}
			this->serialPortNameList = nullptr;
			this->serialPortNameList = new CString[portCount];
			for (int temp = 0; temp<portCount; temp++)
			{
				this->serialPortNameList[temp] = portNameListTemp[temp];
			}
			return ERROR_SUCCESS;
		}
		else {
			errorInfo = L"READ SERIAL PORT FAILED";
			//TO DO FormatMessage();
		}
		return 1;
	}

	//��ȡ���ھ��
	BOOL SerialPort::getSerialPortResource(CString serialPortNumber) {
		CloseHandle(hCom);
		this->hCom = CreateFile(serialPortNumber,//COM��
			GENERIC_READ | GENERIC_WRITE, //�������д
			0, //��ռ��ʽ
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���
			0, //ͬ����ʽFILE_FLAG_OVERLAPPED
			NULL);
		if (this->hCom == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		return TRUE;
	}

	//���Ӵ���,����ͨ��
	void SerialPort::StartSerialPort(CString serialPortName, int baudRate, int parity, int stopBits, int byteSize) {
			 if (this->getSerialPortResource(serialPortName)) {

				SetupComm(hCom, 1024, 1024); //���뻺����������������Ĵ�С����1024 �ֽ�

				COMMTIMEOUTS TimeOuts;     //���ڳ�ʱ

				TimeOuts.ReadIntervalTimeout = 20;

				TimeOuts.ReadTotalTimeoutMultiplier = 0;
				TimeOuts.ReadTotalTimeoutConstant = 0;

				//�趨д��ʱ
				TimeOuts.WriteTotalTimeoutMultiplier = 0;
				TimeOuts.WriteTotalTimeoutConstant = 0;

				SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ
				GetCommState(hCom, &dcb);
				dcb.BaudRate = baudRate; //������Ϊ115200
				dcb.ByteSize = byteSize; //ÿ���ֽ���8λ
				dcb.Parity = parity; //����żУ��λ
				dcb.StopBits = stopBits; //һ��ֹͣλ
				SetCommState(hCom, &dcb);	
				errorInfo = L"open hcom succeed";
			}
			 else {
				 errorInfo = L"open hcom failed";
			 }
	}

	char* SerialPort::ReadSerialPort() {
		CString data;
		DWORD wCount;//��ȡ���ֽ���
		COMSTAT ComStat;
		DWORD dwErrorFlags;
		ClearCommError(hCom, &dwErrorFlags, &ComStat);
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
		if (ReadFile(hCom, &serialContent, sizeof(serialContent), &wCount, NULL))
		{
		//tempurature = (int)serialContent[9];
		//wet= (int)serialContent[8];
		//data.Format(_T("��ǰ  �¶ȣ�%d��  ʪ�ȣ�%d%%"), tempurature, wet);
		//cout << "fuck you1---"<<serialContent << endl;
		return serialContent;
	}
			else
			{
				char* error = "read serial port failed!";
				return error;
			}
	}
	//�򴮿�д������
	bool SerialPort::WriteSerialPort(char*& data) {
		DWORD wCount; //ʵ�ʶ�ȡ���ֽ���
		DWORD wToCount = 256; //Ҫ��ȡ���ֽ���
		COMSTAT ComStat;
		DWORD dwErrorFlags;
		ClearCommError(hCom, &dwErrorFlags, &ComStat);
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
		if (WriteFile(hCom, &data, strlen(data), &wCount, NULL))
			return true;
		return false;
	}

	SerialPort::SerialPort() {
		hCom = NULL;
		portCount = 0;
		serialPortNameList = NULL;
		this->blockFlags = true;
		endflags = false;
		tempurature = 0;
		wet = 0;
	}
	SerialPort::~SerialPort() {
		if (serialPortNameList) {
			delete[] serialPortNameList;
		}
		CloseHandle(hCom);
	}