// Bit_modeling.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "Bit_modeling.h"
#include "Data.h"
using namespace BDK;

int ofset = 2;

int _tmain(int argc, _TCHAR* argv[])
{
	fstream *cout1 = new fstream("C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2005\\Projects\\BDK_V1\\Bit_modeling\\states.txt",  fstream::out);
	if(cout1->fail()){
		cout<<"Error, during the file was opened";
	}

	create_static_stat(cout1);
	create_static_stat_sign(cout1);
	cout1->close();

	Data *myData = new Data(10,12, 3, 8, 4, 9);
	myData->set_subband(0);
	Data *myData2 = new Data(10,12, 3, 8, 4, 9);
	myData2->set_subband(0);
	myData->random_fill();
	myData->setmaximumValue();
	myData->setnumb_bitplane();
	myData->showData();

	myData->initBuffer();
	myData->start_encode_Coefficient_bit_modeling();

	myData2->initBuffer(myData->d_buffer);
	myData2->set_numb_bitplane(myData->get_numb_bitplane());
	myData2->zero_fill();
	myData2->start_decode_Coefficient_bit_modeling();
	myData2->showData();

	myData->compare(myData2);

	return 0;
}

bool get_D0(unsigned char in)
{
	unsigned char test = in & (1<<7);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_D1(unsigned char in)
{
	unsigned char test = in & (1<<6);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_D2(unsigned char in)
{
	unsigned char test = in & (1<<5);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_D3(unsigned char in)
{
	unsigned char test = in & (1<<4);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_V0(unsigned char in)
{
	unsigned char test = in & (1<<1);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_V1(unsigned char in)
{
	unsigned char test = in & (1<<0);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_H0(unsigned char in)
{
	unsigned char test = in & (1<<3);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

bool get_H1(unsigned char in)
{
	unsigned char test = in & (1<<2);
	bool back = true;

	if(test == 0){
		back = false;
	}
	return back;

}

int sum_H(unsigned char in)
{
	int back = 0;

	if(get_H1( in)){
		back += 1;
	}

	if(get_H0( in)){
		back += 1;
	}
	return back;
}


int sum_V(unsigned char in)
{
	int back = 0;

	if(get_V1( in)){
		back += 1;
	}

	if(get_V0( in)){
		back += 1;
	}
	return back;
}
int sum_D(unsigned char in)
{
	int back = 0;

	if(get_D0( in)){
		back += 1;
	}

	if(get_D1( in)){
		back += 1;
	}

	if(get_D2( in)){
		back += 1;
	}

	if(get_D3( in)){
		back += 1;
	}
	return back;
}


void create_static_stat(fstream *cout1 )
{
	unsigned char  context_significane[3][256];
	unsigned char in;
	int i = 0;
	int d;
	

	for(i = 0; i < 256; i++ ){
		in = (unsigned char)i; 
		if(sum_H(in) == 2){
			context_significane[0][i] = 8 + ofset;
		}else if(sum_H(in) == 1 && sum_V(in) >= 1){
			context_significane[0][i] = 7 + ofset;
		}else if(sum_H(in) == 1 && sum_V(in) == 0 && sum_D(in) >= 1){
			context_significane[0][i] = 6 + ofset;
		}else if(sum_H(in) == 1 && sum_V(in) == 0 && sum_D(in) == 0){
			context_significane[0][i] = 5 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 2 ){
			context_significane[0][i] = 4 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 1 ){
			context_significane[0][i] = 3 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) >= 2){
			context_significane[0][i] = 2 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) == 1){
			context_significane[0][i] = 1 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) == 0){
			context_significane[0][i] = 0 + ofset;
		}else{
			cout<< "Fehler bei der Erstellun "<<endl;
		}
	}

	for(i = 0; i < 256; i++ ){
		in = (unsigned char)i; 
		if(sum_V(in) == 2){
			context_significane[1][i] = 8 + ofset;
		}else if(sum_H(in) >= 1 && sum_V(in) == 1){
			context_significane[1][i] = 7 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 1 && sum_D(in) >= 1){
			context_significane[1][i] = 6 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 1 && sum_D(in) == 0){
			context_significane[1][i] = 5 + ofset;
		}else if(sum_H(in) == 2 && sum_V(in) == 0 ){
			context_significane[1][i] = 4 + ofset;
		}else if(sum_H(in) == 1 && sum_V(in) == 0 ){
			context_significane[1][i] = 3 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) >= 2){
			context_significane[1][i] = 2 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) == 1){
			context_significane[1][i] = 1 + ofset;
		}else if(sum_H(in) == 0 && sum_V(in) == 0 && sum_D(in) == 0){
			context_significane[1][i] = 0 + ofset;
		}else{
			cout<< "Fehler bei der Erstellun "<<endl;
		}
	}

	for(i = 0; i < 256; i++ ){
		in = (unsigned char)i; 
		if(sum_D(in) >= 3){
			context_significane[2][i] = 8 + ofset;
		}else if((sum_H(in) + sum_V(in)) >= 1 && sum_D(in) == 2){
			context_significane[2][i] = 7 + ofset;
		}else if((sum_H(in) + sum_V(in)) == 0 && sum_D(in) == 2){
			context_significane[2][i] = 6 + ofset;
		}else if((sum_H(in) + sum_V(in)) >= 2 && sum_D(in) == 1){
			context_significane[2][i] = 5 + ofset;
		}else if((sum_H(in) + sum_V(in)) == 1 && sum_D(in) == 1 ){
			context_significane[2][i] = 4 + ofset;
		}else if((sum_H(in) + sum_V(in)) == 0 && sum_D(in) == 1){
			context_significane[2][i] = 3 + ofset;
		}else if((sum_H(in) + sum_V(in)) >= 2 && sum_D(in) == 0){
			context_significane[2][i] = 2 + ofset;
		}else if((sum_H(in) + sum_V(in)) == 1 && sum_D(in) == 0){
			context_significane[2][i] = 1 + ofset;
		}else if((sum_H(in) + sum_V(in)) == 0 && sum_D(in) == 0){
			context_significane[2][i] = 0 + ofset;
		}else{
			cout<< "Fehler bei der Erstellun "<<endl;
		}
	}

	*cout1<<"{";
	for(d = 0; d < 3; d++){
		*cout1<<"{	"<<endl<<"	";
		for(i = 0; i < 256; i++){
			cout1->width(2);
			*cout1<<(int)context_significane[d][i]<<", ";
			if(i != 0 && ((i+1) % 16 )== 0){
				*cout1<<endl<<"	";
			}

		}
		*cout1<<endl<<"},"<<endl;
	}
	*cout1<<"};"<<endl<<endl;

}

void create_static_stat_sign(fstream *cout1 )
{
	unsigned char sign_context_label[256];
	unsigned char sign_XORBit[256];
	int h_contribution;
	int v_contribution;
	int i;

	for(i = 0; i < 256; i++){
		h_contribution = get_sign_contibution(i>>2);
		v_contribution = get_sign_contibution(i);
		if(h_contribution == 1 && v_contribution == 1){
			sign_context_label[i]	= 13 + ofset;
			sign_XORBit[i]			= 0;
		}else if(h_contribution == 1 && v_contribution == 0){
			sign_context_label[i]	= 12 + ofset;
			sign_XORBit[i]			= 0;
		}else if(h_contribution == 1 && v_contribution == -1){
			sign_context_label[i]	= 11 + ofset;
			sign_XORBit[i]			= 0;
		}else if(h_contribution == 0 && v_contribution == 1){
			sign_context_label[i]	= 10 + ofset;
			sign_XORBit[i]			= 0;
		}else if(h_contribution == 0 && v_contribution == 0){
			sign_context_label[i]	= 9 + ofset;
			sign_XORBit[i]			= 0;
		}else if(h_contribution == 0 && v_contribution == -1){
			sign_context_label[i]	= 10 + ofset;
			sign_XORBit[i]			= 1;
		}else if(h_contribution == -1 && v_contribution == 1){
			sign_context_label[i]	= 11 + ofset;
			sign_XORBit[i]			= 1;
		}else if(h_contribution == -1 && v_contribution == 0){
			sign_context_label[i]	= 12 + ofset;
			sign_XORBit[i]			= 1;
		}else if(h_contribution == -1 && v_contribution == -1){
			sign_context_label[i]	= 13 + ofset;
			sign_XORBit[i]			= 1;
		}else{
			cout<<"Something going wrong create_static_stat_sign()"<<endl;
		}

	}

	*cout1<<"{	"<<endl<<"	";
	for(i = 0; i < 256; i++){
		cout1->width(2);
		*cout1<<(int)sign_context_label[i]<<", ";
		if(i != 0 && ((i+1) % 16 )== 0){
			*cout1<<endl<<"	";
		}

	}
	*cout1<<endl<<"};"<<endl<<endl;

	*cout1<<"{	"<<endl<<"	";
	for(i = 0; i < 256; i++){
		cout1->width(2);
		*cout1<<(int)sign_XORBit[i]<<", ";
		if(i != 0 && ((i+1) % 16 )== 0){
			*cout1<<endl<<"	";
		}

	}
	*cout1<<endl<<"};"<<endl;
}

int get_sign_context(unsigned char in)
{
	int back = 0;
	int h_contribution = get_sign_contibution(in>>2);
	int v_contribution = get_sign_contibution(in);


	return back;

}

int get_sign_contibution(unsigned char in)
{
	int back = 0;
	bool signif0	= get_signif0(in);
	bool sign0		= get_sign0(in);
	bool signif1	= get_signif1(in);
	bool sign1		= get_sign1(in);

	if(			signif0 && !sign0 &&	signif1 && !sign1){
		back = 1;
	}else if(	signif0 && sign0 &&		signif1 && !sign1){
		back = 0;
	}else if(	!signif0 &&				signif1 && !sign1){
		back = 1;
	}else if(	signif0 && !sign0 &&	signif1 && sign1){
		back = 0;
	}else if(	signif0 && sign0 &&		signif1 && sign1){
		back = -1;
	}else if(	!signif0 && 			signif1 && sign1){
		back = -1;
	}else if(	signif0 && !sign0 &&	!signif1 ){
		back = 1;
	}else if(	signif0 && sign0 &&		!signif1 ){
		back = -1;
	}else if(	!signif0 &&				!signif1 ){
		back = 0;
	}else{
		cout<<"Something going wrong"<<endl;
	}

	return back;
}

bool get_signif0(unsigned char in)
{
	bool back = false;
	if((in & (1<<1)) != 0){
		back = true;
	}
	return back;

}

/*
	true	= negative
	false	= positive
*/
bool get_sign0(unsigned char in)
{
	bool back = false;
	if((in & (1<<5)) != 0){
		back = true;
	}
	return back;

}
bool get_signif1(unsigned char in)
{
	bool back = false;
	if((in & (1<<0)) != 0){
		back = true;
	}
	return back;

}

/*
	true	= negative
	false	= positive
*/
bool get_sign1(unsigned char in)
{
	bool back = false;
	if((in & (1<<4)) != 0){
		back = true;
	}
	return back;
}