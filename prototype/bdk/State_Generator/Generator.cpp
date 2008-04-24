#include "Generator.h"


Generator::Generator(void)
{
	int sumH;
	int sumV;
	int sumD;
	int sumHV;
	int iWork1;

	DMASK = 325;
	VMASK = 130;
	HMASK =  40;

	for(iWork1 = 0; iWork1 < 512; iWork1++){
		sumH = sumHx(iWork1);
		sumV = sumVx(iWork1);
		sumD = sumDx(iWork1);
		
		if(sumH == 2){
			significant_context_LL[iWork1] = 8;
		}else if(sumH == 1 && sumV >= 1){
			significant_context_LL[iWork1] = 7;
		}else if(sumH == 1 && sumV == 0 && sumD >= 1){
			significant_context_LL[iWork1] = 6;
		}else if(sumH == 1 && sumV == 0 && sumD == 0){
			significant_context_LL[iWork1] = 5;
		}else if(sumH == 0 && sumV == 2){
			significant_context_LL[iWork1] = 4;
		}else if(sumH == 0 && sumV == 1){
			significant_context_LL[iWork1] = 3;
		}else if(sumH == 0 && sumV == 0 && sumD >= 2){
			significant_context_LL[iWork1] = 2;
		}else if(sumH == 0 && sumV == 0 && sumD == 1){
			significant_context_LL[iWork1] = 1;
		}else if(sumH == 0 && sumV == 0 && sumD == 0){
			significant_context_LL[iWork1] = 0;
		}
	}

	for(iWork1 = 0; iWork1 < 512; iWork1++){
		sumH = sumHx(iWork1);
		sumV = sumVx(iWork1);
		sumD = sumDx(iWork1);
		
		if(sumV == 2){
			significant_context_HL[iWork1] = 8;
		}else if(sumH >= 1 && sumV == 1){
			significant_context_HL[iWork1] = 7;
		}else if(sumH == 0 && sumV == 1 && sumD >= 1){
			significant_context_HL[iWork1] = 6;
		}else if(sumH == 0 && sumV == 1 && sumD == 0){
			significant_context_HL[iWork1] = 5;
		}else if(sumH == 2 && sumV == 0){
			significant_context_HL[iWork1] = 4;
		}else if(sumH == 1 && sumV == 0){
			significant_context_HL[iWork1] = 3;
		}else if(sumH == 0 && sumV == 0 && sumD >= 2){
			significant_context_HL[iWork1] = 2;
		}else if(sumH == 0 && sumV == 0 && sumD == 1){
			significant_context_HL[iWork1] = 1;
		}else if(sumH == 0 && sumV == 0 && sumD == 0){
			significant_context_HL[iWork1] = 0;
		}
	}

	for(iWork1 = 0; iWork1 < 512; iWork1++){
		sumH  = sumHx(iWork1);
		sumV  = sumVx(iWork1);
		sumHV = sumH + sumV;
		sumD  = sumDx(iWork1);
		
		if(sumD >= 3){
			significant_context_HH[iWork1] = 8;
		}else if(sumHV >= 1 && sumD == 2){
			significant_context_HH[iWork1] = 7;
		}else if(sumHV == 0 && sumD == 2){
			significant_context_HH[iWork1] = 6;
		}else if(sumHV >= 2 && sumD == 1){
			significant_context_HH[iWork1] = 5;
		}else if(sumHV == 1 && sumD == 1){
			significant_context_HH[iWork1] = 4;
		}else if(sumHV == 0 && sumD == 1){
			significant_context_HH[iWork1] = 3;
		}else if(sumHV >= 2 && sumD == 0){
			significant_context_HH[iWork1] = 2;
		}else if(sumHV == 1 && sumD == 0){
			significant_context_HH[iWork1] = 1;
		}else if(sumHV == 0 && sumD == 0){
			significant_context_HH[iWork1] = 0;
		}
	}

	/*
	 * Table for sign coding
	 */
	bool V0_sig;
	bool V0_sin;
	bool V1_sig;
	bool V1_sin;
	bool H0_sig;
	bool H0_sin;
	bool H1_sig;
	bool H1_sin;
	for(iWork1 = 0; iWork1 < 256; iWork1++){

		V0_sig = getV0sig(iWork1);
		V0_sin = getV0sin(iWork1);
		V1_sig = getV1sig(iWork1);
		V1_sin = getV1sin(iWork1);
		H0_sig = getH0sig(iWork1);
		H0_sin = getH0sin(iWork1);
		H1_sig = getH1sig(iWork1);
		H1_sin = getH1sin(iWork1);

		if(V0_sig && !V0_sin && V1_sig && !V1_sin){
			V_contribution[iWork1] = 1;
		}else if(V0_sig && V0_sin && V1_sig && !V1_sin){
			V_contribution[iWork1] = 0;
		}else if(!V0_sig && V1_sig && !V1_sin){
			V_contribution[iWork1] = 1;
		}else if(V0_sig && !V0_sin && V1_sig && V1_sin){
			V_contribution[iWork1] = 0;
		}else if(V0_sig && V0_sin && V1_sig && V1_sin){
			V_contribution[iWork1] = -1;
		}else if(!V0_sig && V1_sig && V1_sin){
			V_contribution[iWork1] = -1;
		}else if(V0_sig && !V0_sin && !V1_sig ){
			V_contribution[iWork1] = 1;
		}else if(V0_sig && V0_sin && !V1_sig ){
			V_contribution[iWork1] = -1;
		}else if(!V0_sig&& !V1_sig ){
			V_contribution[iWork1] = 0;
		}

		if(H0_sig && !H0_sin && H1_sig && !H1_sin){
			H_contribution[iWork1] = 1;
		}else if(H0_sig && H0_sin && H1_sig && !H1_sin){
			H_contribution[iWork1] = 0;
		}else if(!H0_sig && H1_sig && !H1_sin){
			H_contribution[iWork1] = 1;
		}else if(H0_sig && !H0_sin && H1_sig && H1_sin){
			H_contribution[iWork1] = 0;
		}else if(H0_sig && H0_sin && H1_sig && H1_sin){
			H_contribution[iWork1] = -1;
		}else if(!H0_sig && H1_sig && H1_sin){
			H_contribution[iWork1] = -1;
		}else if(H0_sig && !H0_sin && !H1_sig ){
			H_contribution[iWork1] = 1;
		}else if(H0_sig && H0_sin && !H1_sig ){
			H_contribution[iWork1] = -1;
		}else if(!H0_sig&& !H1_sig ){
			H_contribution[iWork1] = 0;
		}
	}

	for(iWork1 = 0; iWork1 < 256; iWork1++){
		
		if(H_contribution[iWork1] == 1 && V_contribution[iWork1] == 1){
			sign_context[iWork1]	= 13;
			sign_XORbit[iWork1]		= 0;
		}else if(H_contribution[iWork1] == 1 && V_contribution[iWork1] == 0){
			sign_context[iWork1]	= 12;
			sign_XORbit[iWork1]		= 0;
		}else if(H_contribution[iWork1] == 1 && V_contribution[iWork1] == -1){
			sign_context[iWork1]	= 11;
			sign_XORbit[iWork1]		= 0;
		}else if(H_contribution[iWork1] == 0 && V_contribution[iWork1] == 1){
			sign_context[iWork1]	= 10;
			sign_XORbit[iWork1]		= 0;
		}else if(H_contribution[iWork1] == 0 && V_contribution[iWork1] == 0){
			sign_context[iWork1]	= 9;
			sign_XORbit[iWork1]		= 0;
		}else if(H_contribution[iWork1] == 0 && V_contribution[iWork1] == -1){
			sign_context[iWork1]	= 10;
			sign_XORbit[iWork1]		= 1;
		}else if(H_contribution[iWork1] == -1 && V_contribution[iWork1] == 1){
			sign_context[iWork1]	= 11;
			sign_XORbit[iWork1]		= 1;
		}else if(H_contribution[iWork1] == -1 && V_contribution[iWork1] == 0){
			sign_context[iWork1]	= 12;
			sign_XORbit[iWork1]		= 1;
		}else if(H_contribution[iWork1] == -1 && V_contribution[iWork1] == -1){
			sign_context[iWork1]	= 13;
			sign_XORbit[iWork1]		= 1;
		}
	}

}

Generator::~Generator(void)
{
}

void Generator::write(ofstream *in)
{
	int iWork1;

	(*in)<<"	const int significant_context_LL[] = {";
	for(iWork1 = 0; iWork1 < 512; iWork1++){
		if(iWork1 % 30 == 0){
			(*in)<<endl<<"		";
		}
		(*in) << significant_context_LL[iWork1];
		if(iWork1 != 511){
			(*in)<<",";
		}

	}
	(*in)<<endl<<"	};"<<endl;

	(*in)<<endl<<endl;
	(*in)<<"	const int significant_context_HL[] = {";
	for(iWork1 = 0; iWork1 < 512; iWork1++){
		if(iWork1 % 30 == 0){
			(*in)<<endl<<"		";
		}
		(*in) << significant_context_HL[iWork1];
		if(iWork1 != 511){
			(*in)<<",";
		}

	}
	(*in)<<endl<<"	};"<<endl;


	(*in)<<endl<<endl;
	(*in)<<"	const int significant_context_HH[] = {";
	for(iWork1 = 0; iWork1 < 512; iWork1++){
		if(iWork1 % 30 == 0){
			(*in)<<endl<<"		";
		}
		(*in) << significant_context_HH[iWork1];
		if(iWork1 != 511){
			(*in)<<",";
		}

	}
	(*in)<<endl<<"	};"<<endl;

	(*in)<<endl<<endl;
	(*in)<<"	const int sign_context[] = {";
	for(iWork1 = 0; iWork1 < 256; iWork1++){
		if(iWork1 % 30 == 0){
			(*in)<<endl<<"		";
		}
		(*in) << sign_context[iWork1];
		if(iWork1 != 255){
			(*in)<<",";
		}

	}
	(*in)<<endl<<"	};"<<endl;

	(*in)<<endl<<endl;
	(*in)<<"	const int sign_XORbit[] = {";
	for(iWork1 = 0; iWork1 < 256; iWork1++){
		if(iWork1 % 30 == 0){
			(*in)<<endl<<"		";
		}
		(*in) << sign_XORbit[iWork1];
		if(iWork1 != 255){
			(*in)<<",";
		}

	}
	(*in)<<endl<<"	};"<<endl;

}

int Generator::sumDx(int in)
{
	int input = in & DMASK;
	return count_last_nine_bits(input);

}

int Generator::sumHx(int in)
{
	int input = in & HMASK;
	return count_last_nine_bits(input);
}

int Generator::sumVx(int in)
{
	int input = in & VMASK;
	return count_last_nine_bits(input);
}

int Generator::count_last_four_bits(int in)
{
	int input = in & 15;

	switch(input)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:	
		return 2;
	case 4:
		return 1;
	case 5:
		return 2;
	case 6:
		return 2;
	case 7:
		return 3;
	case 8:
		return 1;
	case 9:
		return 2;
	case 10:
		return 2;
	case 11:	
		return 3;
	case 12:
		return 2;
	case 13:
		return 3;
	case 14:
		return 3;
	case 15:
		return 4;
	default:
		return 3333;
	}

}


int Generator::count_last_nine_bits(int in)
{
	int iWork1;
	int count = 0;
	for(iWork1 = 0; iWork1 < 9; iWork1++){
		count += ((in>>iWork1) & 1);
	}

	return count;
}


bool Generator::getV0sin(int in)
{
	if((in & 0x80) != 0){
		return true;
	}else{
		return false;
	}
}


bool Generator::getV0sig(int in)
{
	if((in & 0x40) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getV1sin(int in)
{
	if((in & 0x20) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getV1sig(int in)
{
	if((in & 0x10) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getH0sin(int in)
{
	if((in & 0x8) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getH0sig(int in)
{
	if((in & 0x4) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getH1sin(int in)
{
	if((in & 0x2) != 0){
		return true;
	}else{
		return false;
	}
}

bool Generator::getH1sig(int in)
{
	if((in & 0x1) != 0){
		return true;
	}else{
		return false;
	}
}