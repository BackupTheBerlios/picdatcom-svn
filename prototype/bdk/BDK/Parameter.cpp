#include "Parameter.h"


unsigned short bytetoshort(const unsigned char* in, int pos)
{
	unsigned short back = in[pos];
	back <<= 8;
	back |= in[pos + 1];

	return back;
}

unsigned int bytetouint(const unsigned char* in, int pos)
{
	unsigned int back = in[pos];
	back <<= 8;
	back |= in[pos + 1];
	back <<= 8;
	back |= in[pos + 2];
	back <<= 8;
	back |= in[pos + 3];

	return back;
}

bool is_known_mark(int mark){
	if(mark == COD){
		return true;
	}
	if(mark == QCD){
		return true;
	}
	if(mark == COM){
		return true;
	}
	if(mark == SOT){
		return true;
	}
	if(mark == SOD){
		return true;
	}
	if(mark == EOC){
		return true;
	}

	return false;


}

unsigned int BDK_ui_max(unsigned int a, unsigned int b)
{
	unsigned int max;

	if(a < b){
		max = b;
	}else{
		max = a;
	}
	return max;
}

unsigned int BDK_ui_min(unsigned int a, unsigned int b)
{
	unsigned int min;

	if(a > b){
		min = b;
	}else{
		min = a;
	}
	return min;
}

int BDK_i_max(int a, int b)
{
	int max = a;

	if(max < b){
		max = b;
	}

	return max;
}

int BDK_i_min(int a, int b)
{
	int min = a;

	if(min > b){
		min = b;
	}
	return min;
}

int BDK_i_ceiling(int a, int b)
{
	int i = a/b;
	if(a%b != 0){
		i += 1;
	}
	return i;	
}

int BDK_i_floor( int a, int b)
{
	int i = a/b;

	return i;
}