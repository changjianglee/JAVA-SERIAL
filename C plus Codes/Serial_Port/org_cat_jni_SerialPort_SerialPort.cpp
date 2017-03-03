# include <iostream>

# include "org_cat_jni_SerialPort_SerialPort.h"

# include "serialport.h"

using namespace std;

//��������
jstring stoJstring(JNIEnv* env, const char* pat);
int portNums;		//��¼���ں���,������������

/*
*����:		serialport
*����:		ȫ�ֱ���
*����:		�����ڲ�����
*/
SerialPort sp;


/**************************************************************************************************/

/*
* Class:     org_cat_jni_SerialPort_SerialPort
* Method:    getPorts
* Signature: ()[I
*/
JNIEXPORT jintArray JNICALL Java_org_cat_jni_SerialPort_SerialPort_getPorts
(JNIEnv * env, jobject obj)
{
	sp.getSerialPortNames();		//���Ȼ�ȡ���ں�

	int i = 0;

	int index;    //�����Ҵ��ں�������������
	int size = sp.portCount;	//���ڸ���

	CString portName;		//��¼������
	CString s = "M";		//���ֵ�ַ

	jintArray n = env->NewIntArray(size);	//��¼���ں���������

	jint *h = env->GetIntArrayElements(n, NULL);	//ָ��

	CString *portNames = sp.serialPortNameList;		//ָ��

	while (size--)
	{
		portName = sp.serialPortNameList[i];
		index = portName.Find(s);
		h[i] = _ttoi(portName.Right(index - 1));
		i++;
	}
	env->ReleaseIntArrayElements(n, h, 0);	//�ͷ���Դ
	return n;
}

/*
* Class:     org_cat_jni_SerialPort_SerialPort
* Method:    getHandle
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_org_cat_jni_SerialPort_SerialPort_getHandle
(JNIEnv * env, jobject obj, jint _jint)
{
	//cout << "no do" << endl;
	//CString spNum;
	int num = _jint + 48;
	char spNum[5] = { 'C','O','M',(char)num };
	portNums = _jint;		//��������,�Ժ�ʹ��
	BOOL isSuccess = sp.getSerialPortResource(spNum);

	if (isSuccess)	cout << "�ɹ���ȡ������Դ" << endl;
	else
	{
		cout << "��ȡ������Դʧ��" << endl;
	}
}

/*
* Class:     org_cat_jni_SerialPort_SerialPort
* Method:    startPort
* Signature: (IIII)V
*/
JNIEXPORT void JNICALL Java_org_cat_jni_SerialPort_SerialPort_startPort
(JNIEnv *, jobject, jint bdrx, jint _parity, jint _stopBits, jint _byteSize)
{
	int baudRatio = bdrx;
	int parit = _parity;
	int stops = _stopBits;
	int bytes = _byteSize;
	cout << "port identify:" << bdrx << "," << parit<<"," << stops<<"," << bytes << endl;
	//cout << "no do" << endl;
	char spNum[5] = { 'C','O','M',(char)(portNums + 48) };
	//cout << "���ں�"<<spNum << endl;
	sp.StartSerialPort(spNum, bdrx, _parity, _stopBits, _byteSize);

	wcout << sp.errorInfo.GetString() << endl;
}

/*
* Class:     org_cat_jni_SerialPort_SerialPort
* Method:    readPort
* Signature: ()Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL Java_org_cat_jni_SerialPort_SerialPort_readPort
(JNIEnv * env, jobject job)
{
	char *info;
	info = sp.ReadSerialPort();
	//wcout << info.GetString() << endl;
	//size_t len = wcslen(info) + 1;
	//size_t converted = 0;
	////char *host_;
	//host_ = (char*)malloc(len * sizeof(char));
	//wcstombs_s(&converted, host_, len, info, _TRUNCATE);
	//cout << "no do" << endl;
	//int m = portNums+48;
	//char ms;
	//ms = (char)m;
	//char z[5] = {'C','O','M',ms};
	//char *x = z;
	//cout << host_[1] << endl;

	//cout << "fuc you 2" << info << endl;

	jstring y = stoJstring(env, info);
	//cout << y [0]<< endl;
	return y;
}

/*
* Class:     org_cat_jni_SerialPort_SerialPort
* Method:    sendDatatoP04
* Signature: ()Z
*/
JNIEXPORT jboolean JNICALL Java_org_cat_jni_SerialPort_SerialPort_sendDatatoP04
(JNIEnv * env, jobject obj)
{
	cout << "fucking  you" << endl;
	jboolean r = 1;
	char *data = "1";
	if (sp.WriteSerialPort(data)) 
	{
		cout << "fucking succeed" << endl;
		return r;
	}
	cout << "fucking faild" << endl;
	return !r;
	
}

//�ٶȵ���
jstring stoJstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}