/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_cat_jni_SerialPort_SerialPort */

#ifndef _Included_org_cat_jni_SerialPort_SerialPort
#define _Included_org_cat_jni_SerialPort_SerialPort
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_cat_jni_SerialPort_SerialPort
 * Method:    getPorts
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_org_cat_jni_SerialPort_SerialPort_getPorts
  (JNIEnv *, jobject);

/*
 * Class:     org_cat_jni_SerialPort_SerialPort
 * Method:    getHandle
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_cat_jni_SerialPort_SerialPort_getHandle
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_cat_jni_SerialPort_SerialPort
 * Method:    startPort
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_org_cat_jni_SerialPort_SerialPort_startPort
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     org_cat_jni_SerialPort_SerialPort
 * Method:    readPort
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_cat_jni_SerialPort_SerialPort_readPort
  (JNIEnv *, jobject);

/*
 * Class:     org_cat_jni_SerialPort_SerialPort
 * Method:    sendDatatoP04
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_cat_jni_SerialPort_SerialPort_sendDatatoP04
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
