/*
 * Copyright (C) 2008  Uwe Br�nen
 *      Contact Email:
 *
 * This file is part of PicDatCom.
 *
 * PicDatCom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PicDatCom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PicDatCom.  If not, see <http://www.gnu.org/licenses/>.
 * */

 #include "PDC_Java_Junction.h"
 #include "PDC_Decoder.h"
 #include "PDC_Parameter.h"
 #include "PDC_Picture.h"

 START_C

 /* Inaccessible static: dll_path */
/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    create_structur
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_PicDatCom_PicDatComImage_create_1structur
  (JNIEnv *env, jclass in_class, jstring in_path)
{
	const char *path		= NULL;
	jlong pointer			= 0;
	PDC_Decoder	*decoder	= NULL;

	path = (*env)->GetStringUTFChars(env, in_path, 0);
	if(path == NULL){
		return pointer;
	}

	decoder = new_PDC_Decoder_02(path);
	if(decoder == NULL){
		return pointer;
	}
	pointer = (jlong)(POINTER)decoder;

	return pointer;
}

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    delete_structur
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_PicDatCom_PicDatComImage_delete_1structur
  (JNIEnv *env, jclass in_class, jlong in_pointer)
{

	return in_pointer;
}

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_width
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PicDatCom_PicDatComImage_get_1width
  (JNIEnv *env, jclass in_class, jlong in_pointer)
{
	PDC_Decoder	*decoder	= NULL;
	jint width				= 0;
	PDC_Picture *picture	= NULL;

	if(in_pointer == 0){
		return width;
	}

	decoder = (PDC_Decoder	*)(POINTER)in_pointer;
	if(decoder == NULL){
		return width;
	}

	picture = decoder->picture;
	if(picture == NULL){
		return width;
	}

	width = (jint) PDC_Picture_get_width(decoder->exception, picture);
	if(decoder->exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return 0;
	}


	return width;
}

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_height
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PicDatCom_PicDatComImage_get_1height
  (JNIEnv *env, jclass in_class, jlong in_pointer)
{
	PDC_Decoder	*decoder	= NULL;
	jint height				= 0;
	PDC_Picture *picture	= NULL;

	if(in_pointer == 0){
		return height;
	}

	decoder = (PDC_Decoder	*)(POINTER)in_pointer;
	if(decoder == NULL){
		return height;
	}

	picture = decoder->picture;
	if(picture == NULL){
		return height;
	}

	height = (jint) PDC_Picture_get_height(decoder->exception, picture);
	if(decoder->exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return 0;
	}


	return height;
}

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_RGB
 * Signature: (J[F)[F
 */
JNIEXPORT jfloatArray JNICALL Java_PicDatCom_PicDatComImage_get_1RGB__J_3F
  (JNIEnv *env, jclass in_class, jlong in_pointer, jfloatArray floatarray)
{
	PDC_Decoder	*decoder = NULL;
	PDC_Picture *picture = NULL;
	jboolean	isCopy;
	float*		data;
	PDC_uint	size;

	decoder = (PDC_Decoder*)(POINTER)in_pointer;
	if(decoder == NULL){
		return NULL;
	}

	picture = decoder->picture;
	size = PDC_Picture_get_width(decoder->exception, picture);

	data = (*env)->GetFloatArrayElements(env, floatarray, &isCopy);

	PDC_Picture_get_RGB_float(decoder->exception, picture, data, size);

	(*env)->ReleaseFloatArrayElements(env, floatarray, data, 0);
	return floatarray;
}

/*
 * Class:     PicDatCom_PicDatComImage
 * Method:    get_RGB
 * Signature: (J[I)[I
 */
JNIEXPORT jintArray JNICALL Java_PicDatCom_PicDatComImage_get_1RGB__J_3I
  (JNIEnv *env, jclass in_class, jlong in_pointer, jintArray intarray)
{
	PDC_Decoder	*decoder = NULL;
	PDC_Picture *picture = NULL;
	jboolean	isCopy;
	int*		data;
	PDC_uint	size;

	decoder = (PDC_Decoder*)(POINTER)in_pointer;
	if(decoder == NULL){
		return NULL;
	}

	picture = decoder->picture;
	size = PDC_Picture_get_width(decoder->exception, picture);

	data = (*env)->GetIntArrayElements(env, intarray, &isCopy);

	PDC_Picture_get_RGB_int(decoder->exception, picture, (PDC_uint32 *)data, size);

	(*env)->ReleaseIntArrayElements(env, intarray, data, 0);
	return intarray;
}



STOP_C
