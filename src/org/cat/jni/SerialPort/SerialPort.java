package org.cat.jni.SerialPort;

public class SerialPort {
	
	public native int[] getPorts();			//��ȡ���ں�
	
	public native void getHandle(int port);		//��þ��
	
	public native void startPort(int _BaudRation, int _parity,int _stopBits,int _byteSize);		//��������
	
	public native String readPort();		//��ȡһ������
	
	public native boolean sendDatatoP04();		//����һ���ź�
	
	//���ض�̬��
	static{
		System.loadLibrary("Serial_Port");
	}
}
