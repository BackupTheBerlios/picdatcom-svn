/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class PicDatCom_PicDatComImage */

#ifndef _Included_PicDatCom_PicDatComImage
#define _Included_PicDatCom_PicDatComImage
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    create_structur
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_PicDatCom_PicDatComImage_create_1structur__Ljava_lang_String_2
  (JNIEnv *, jclass, jstring);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    create_structur
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_PicDatCom_PicDatComImage_create_1structur___3B
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    delete_structur
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_PicDatCom_PicDatComImage_delete_1structur
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_width
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PicDatCom_PicDatComImage_get_1width
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_height
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PicDatCom_PicDatComImage_get_1height
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_RGB
 * Signature: (J[F)[F
 */
JNIEXPORT jfloatArray JNICALL Java_PicDatCom_PicDatComImage_get_1RGB__J_3F
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_RGB
 * Signature: (J[I)[I
 */
JNIEXPORT jintArray JNICALL Java_PicDatCom_PicDatComImage_get_1RGB__J_3I
  (JNIEnv *, jclass, jlong, jintArray);

#ifdef __cplusplus
}
#endif
#endif