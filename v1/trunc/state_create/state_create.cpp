// state_create.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

/*
 * H0 H1 V0 V1 D0 D1 D2 D3
 * 87654321
 */


#define	SET_SIGN_CONTEXT_A1 0x0200
#define	SET_SIGN_CONTEXT_A2 0x4080 
#define	SET_SIGN_CONTEXT_A3 0x0100


#define	SET_SIGN_CONTEXT_B1 0x02000
#define	SET_SIGN_CONTEXT_B2 0x40800 
#define	SET_SIGN_CONTEXT_B3 0x01000


#define	SET_SIGN_CONTEXT_C1 0x020000
#define	SET_SIGN_CONTEXT_C2 0x408000 
#define	SET_SIGN_CONTEXT_C3 0x010000


#define	SET_SIGN_CONTEXT_D1 0x0200000
#define	SET_SIGN_CONTEXT_D2 0x4080000 
#define	SET_SIGN_CONTEXT_D3 0x0100000


#define SET_CONTEXT_1 0x028001
#define	SET_CONTEXT_2 0x800040
#define SET_CONTEXT_3 0x012004

#define D3 0x01
#define D2 0x02
#define D1 0x04
#define D0 0x08
#define V1 0x10
#define V0 0x20
#define H1 0x40
#define H0 0x80

#define SIGNV0 0x01
#define SIGNV1 0x02
#define SIGNH0 0x04
#define SIGNH1 0x08

int states[3][256];
int sign_states[256];
int XORbit[256];
void genratestate();
void genratesignstate();

int offset = 2;

int _tmain(int argc, _TCHAR* argv[])
{
	int t, g, z;
	FILE *file;

	file = fopen("states.txt", "w");

	genratestate();
	genratesignstate();
	
	fprintf(file,"	PDC_uint8 BDK_context_states[3][256] = {{	");
	for( t = 0; t < 256; ){
		for( g = 0; g < 16; g++){
			fprintf(file," %2d",states[0][t] + offset);
			if(t != 255){
				fprintf(file,",");
			}else{
				fprintf(file,"	},\n									{	");
			}
			t++;
		}
		fprintf(file,"\n												");
	}

	for( t = 0; t < 256; ){
		for( g = 0; g < 16; g++){
			fprintf(file," %2d",states[1][t]  + offset);
			if(t != 255){
				fprintf(file,",");
			}else{
				fprintf(file,"	},\n									{	");
			}
			t++;
		}
		fprintf(file,"\n												");
	}


	for( t = 0; t < 256; ){
		for( g = 0; g < 16; g++){
			fprintf(file," %2d",states[1][t]  + offset);
			if(t != 255){
				fprintf(file,",");
			}else{
				fprintf(file,"	}};\n");
			}
			t++;
		}
		fprintf(file,"\n												");
	}

	fprintf(file,"\n");
	fprintf(file,"	PDC_uint8 XORbit[256] = {	");
	for( t = 0; t < 256; ){
		for( g = 0; g < 16; g++){
			fprintf(file," 0x%02X",XORbit[t]);
			if(t != 255){
				fprintf(file,",");
			}else{
				fprintf(file,"	};\n");
			}
			t++;
		}
		fprintf(file,"\n								");
	}
	

	fprintf(file,"\n");
	fprintf(file,"	PDC_uint8 PDC_context_signstates[256] = {	");
	for( t = 0; t < 256; ){
		for( g = 0; g < 16; g++){
			fprintf(file," %2d",sign_states[t]  + offset);
			if(t != 255){
				fprintf(file,",");
			}else{
				fprintf(file,"	};\n");
			}
			t++;
		}
		fprintf(file,"\n												");
	}
	fclose(file);

	return 0;
}

int sum_D(unsigned char in)
{
	int back = 0;

	if((in & D0) == D0){
		back += 1;
	}

	if((in & D1) == D1){
		back += 1;
	}

	if((in & D2) == D2){
		back += 1;
	}

	if((in & D3) == D3){
		back += 1;
	}
	return back;
}

int sum_H(unsigned char in)
{
	int back = 0;

	if((in & H0) == H0){
		back += 1;
	}

	if((in & H1) == H1){
		back += 1;
	}
	return back;
}

int sum_V(unsigned char in)
{
	int back = 0;

	if((in & V0) == V0){
		back += 1;
	}

	if((in & V1) == V1){
		back += 1;
	}
	return back;
}

int state_LL(int V, int H, int D)
{
	int context = 88;

	if(H == 2){
		context = 8;
	}else if( H == 1 && V >= 1){
		context = 7;
	}else if( H == 1 && V == 0 && D >= 1){
		context = 6;
	}else if( H == 1 && V == 0 && D == 0){
		context = 5;
	}else if( H == 0 && V == 2){
		context = 4;
	}else if( H == 0 && V == 1){
		context = 3;
	}else if( H == 0 && V == 0 && D >= 2){
		context = 2;
	}else if( H == 0 && V == 0 && D == 1){
		context = 1;
	}else if( H == 0 && V == 0 && D == 0){
		context = 0;
	}

	if(context == 88){
		printf("Fehler \n");
	}

	return context;
}

int state_HL(int V, int H, int D)
{
	int context  = 88;

	if(V == 2){
		context = 8;
	}else if( H >= 1 && V == 1){
		context = 7;
	}else if( H == 0 && V == 1 && D >= 1){
		context = 6;
	}else if( H == 0 && V == 1 && D == 0){
		context = 5;
	}else if( H == 2 && V == 0){
		context = 4;
	}else if( H == 1 && V == 0){
		context = 3;
	}else if( H == 0 && V == 0 && D >= 2){
		context = 2;
	}else if( H == 0 && V == 0 && D == 1){
		context = 1;
	}else if( H == 0 && V == 0 && D == 0){
		context = 0;
	}

	if(context == 88){
		printf("Fehler \n");
	}

	return context;
}

int state_HH(int V, int H, int D)
{
	int context = 88;

	int HV = H + V;

	if(D >= 3){
		context = 8;
	}else if( HV >= 1 && D == 2){
		context = 7;
	}else if( HV == 0 && D == 2){
		context = 6;
	}else if( HV >= 2 && D == 1){
		context = 5;
	}else if( HV == 1 && D == 1){
		context = 4;
	}else if( HV == 0 && D == 1){
		context = 3;
	}else if( HV >= 2 && D == 0){
		context = 2;
	}else if( HV == 1 && D == 0){
		context = 1;
	}else if( HV == 0 && D == 0){
		context = 0;
	}

	if(context == 88){
		printf("Fehler \n");
	}

	return context;
}

void genratestate()
{
	int V, H, D;
	for(int i = 0; i < 256; i++){
		V = sum_V((unsigned char)i);
		D = sum_D((unsigned char)i);
		H = sum_H((unsigned char)i);

		states[0][i] = state_LL(V,H,D);
		states[1][i] = state_HL(V,H,D);
		states[2][i] = state_HH(V,H,D);
	}
}

int contribution(unsigned int signi0, unsigned int sign0, unsigned int signi1, unsigned int sign1)
{
	int contri = 88;
	/*
	if(signi0 != 0 && sign0 != 0 && signi1 != 0 && sign1 != 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 == 0 && signi1 != 0 && sign1 != 0){
		contri = 0;
	}else if(signi0 == 0 && signi1 != 0 && sign1 != 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 != 0 && signi1 != 0 && sign1 == 0){
		contri = 0;
	}else if(signi0 != 0 && sign0 == 0 && signi1 != 0 && sign1 == 0){
		contri = -1;
	}else if(signi0 == 0 && signi1 != 0 && sign1 == 0){
		contri = -1;
	}else if(signi0 != 0 && sign0 != 0 && signi1 == 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 == 0 && signi1 == 0){
		contri = -1;
	}else if(signi0 == 0 && signi1 == 0){
		contri = 0;
	}
	*/

	if(signi0 != 0 && sign0 == 0 && signi1 != 0 && sign1 == 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 != 0 && signi1 != 0 && sign1 == 0){
		contri = 0;
	}else if(signi0 == 0 && signi1 != 0 && sign1 == 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 == 0 && signi1 != 0 && sign1 != 0){
		contri = 0;
	}else if(signi0 != 0 && sign0 != 0 && signi1 != 0 && sign1 != 0){
		contri = -1;
	}else if(signi0 == 0 && signi1 != 0 && sign1 != 0){
		contri = -1;
	}else if(signi0 != 0 && sign0 == 0 && signi1 == 0){
		contri = 1;
	}else if(signi0 != 0 && sign0 != 0 && signi1 == 0){
		contri = -1;
	}else if(signi0 == 0 && signi1 == 0){
		contri = 0;
	}
	if(contri == 88){
		printf("Fehler \n");
	}

	return contri;
}

int sign_state(int H_contri, int V_contri)
{
	int state = 88;

	if(H_contri == 1 && V_contri == 1){
		state = 13;
	}else if(H_contri == 1 && V_contri == 0){
		state = 12;
	}else if(H_contri == 1 && V_contri == -1){
		state = 11;
	}else if(H_contri == 0 && V_contri == 1){
		state = 10;
	}else if(H_contri == 0 && V_contri == 0){
		state = 9;
	}else if(H_contri == 0 && V_contri == -1){
		state = 10;
	}else if(H_contri == -1 && V_contri == 1){
		state = 11;
	}else if(H_contri == -1 && V_contri == 0){
		state = 12;
	}else if(H_contri == -1 && V_contri == -1){
		state = 13;
	}

	if(state == 88){
		printf("Fehler \n");
	}

	return state;
}

int xorbit_state(int H_contri, int V_contri)
{
	int xorbit = 88;

	if(H_contri == 1 && V_contri == 1){
		xorbit = 0;
	}else if(H_contri == 1 && V_contri == 0){
		xorbit = 0;
	}else if(H_contri == 1 && V_contri == -1){
		xorbit = 0;
	}else if(H_contri == 0 && V_contri == 1){
		xorbit = 0;
	}else if(H_contri == 0 && V_contri == 0){
		xorbit = 0;
	}else if(H_contri == 0 && V_contri == -1){
		xorbit = 255;
	}else if(H_contri == -1 && V_contri == 1){
		xorbit = 255;
	}else if(H_contri == -1 && V_contri == 0){
		xorbit = 255;
	}else if(H_contri == -1 && V_contri == -1){
		xorbit = 255;
	}

	if(xorbit == 88){
		printf("Fehler \n");
	}

	return xorbit;
}

void genratesignstate()
{
	int V_contri, H_contri, i;

	for( i = 0; i < 256; i++){
		H_contri = contribution( i & H0, i & SIGNH0, i & H1, i & SIGNH1);
		V_contri = contribution( i & V0, i & SIGNV0, i & V1, i & SIGNV1);

		sign_states[i]	= sign_state(H_contri, V_contri);
		XORbit[i]		= xorbit_state(H_contri, V_contri);
	}
}