#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Generator
{
private:
	/*
	 * | D0 | V0 | D1 | H0 | X | H1 | D2 | V1 | D3 |
	 */
	int DMASK;
	int VMASK;
	int HMASK;

	int significant_context_LL[512];
	int significant_context_HL[512];
	int significant_context_HH[512];
	int sumDx(int);
	int sumHx(int);
	int sumVx(int);
	int count_last_four_bits(int);
	int count_last_nine_bits(int);

	/*
	 * | V0sin | V0sig | V1sin | V1sig | H0sin | H0sig | H1sin | H1sig |    
	 */

	int V_contribution[256];
	int H_contribution[256];
	int sign_context[256];
	int sign_XORbit[256];

	bool getV0sin(int);
	bool getV0sig(int);
	bool getV1sin(int);
	bool getV1sig(int);
	bool getH0sin(int);
	bool getH0sig(int);
	bool getH1sin(int);
	bool getH1sig(int);


public:
	Generator(void);
	~Generator(void);
	void write(ofstream *);
};
