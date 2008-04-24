// Arithmetic_entropy_test.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Arithmetic_entropy_encoder.h"
#include "Arithmetic_entropy_decoder.h"
#include "Arithmetic_entropy_decoder_Software.h"
#include "Java_decoder.h"
#include "java_encoder.h"

#include <iostream>
#include <cstdlib>
using namespace std;
using namespace BDK;

#define TEST_LENGTH 30

unsigned char cx[TEST_LENGTH];
unsigned char d1[TEST_LENGTH];
unsigned char d2[TEST_LENGTH];
unsigned char d3[TEST_LENGTH];
unsigned char d4[TEST_LENGTH];

int java_cx[TEST_LENGTH];
int java_d1[TEST_LENGTH];

void test();
void test_daten_generate();
void compare();

int _tmain(int argc, _TCHAR* argv[])
{
	
	test_daten_generate();
	test();
	cout<<"Test beendet"<<endl;
	return 0;
}

void test()
{
	Arithmetic_entropy_encoder* encoder						= new Arithmetic_entropy_encoder();
	Arithmetic_entropy_decoder* decoder						= new Arithmetic_entropy_decoder();
	Arithmetic_entropy_decoder_Software* decoder_Software	= new Arithmetic_entropy_decoder_Software();
	Java_decoder *java_decoder								= new Java_decoder(encoder->j2000_length, (int*)encoder->j2000_index);
	java_encoder *java_encod;

	ByteBuffer *bytebuffer;
	int point;
	encoder->initenc(encoder->j2000_length, encoder->j2000_mps, encoder->j2000_index);
	encoder->start_encode(TEST_LENGTH, d1, cx);
	encoder->flush();

	java_decoder->codeSymbols((int*)java_d1, (int*)java_cx, TEST_LENGTH);

	bytebuffer = encoder->getByteBuffer();
	point	= bytebuffer->read_byte_pos;
	decoder->initdec(bytebuffer ,encoder->j2000_length, encoder->j2000_mps, encoder->j2000_index);
	for(int i = 0; i < TEST_LENGTH; i++){
		d2[i] = decoder->decoder(cx[i]);
	}

	bytebuffer->read_byte_pos	= point;
	bytebuffer->eobit			= false;
	bytebuffer->eobyte			= false;
	decoder_Software->initdec(bytebuffer ,encoder->j2000_length, encoder->j2000_mps, encoder->j2000_index);
	for(int i = 0; i < TEST_LENGTH; i++){
		d3[i] = decoder_Software->decoder(cx[i]);
	}

	bytebuffer->read_byte_pos	= point;
	bytebuffer->eobit			= false;
	bytebuffer->eobyte			= false;
	java_encod	= new java_encoder(bytebuffer,encoder->j2000_length, (unsigned int*)encoder->j2000_mps, (unsigned int*)encoder->j2000_index);
	for(int i = 0; i < TEST_LENGTH; i++){
		d4[i] = java_encod->decodeSymbol((unsigned int)cx[i]);
	}
	compare();
}

void test_daten_generate()
{
	srand(0);
	for(int i = 0; i < TEST_LENGTH; i++){
		cx[i]	= rand() % 19;
		d1[i]	= rand() % 2;	

		java_cx[i] = cx[i];
		java_d1[i] = d1[i];
	}
}

void compare()
{
	for(int i = 0; i < TEST_LENGTH; i++){
		cout<< (int)d1[i] <<" - "<< (int)d4[i]<<"("<< (int)d3[i]<<") = " << (int)(d1[i] - d4[i]) <<endl;
	}
}