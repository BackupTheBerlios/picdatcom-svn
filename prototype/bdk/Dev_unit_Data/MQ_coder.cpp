#include "MQ_coder.h"
#include "Data.h"


const int MQ_Encoder::qe[] = {0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
                  0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
                  0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
                  0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
                  0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
                  0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
                  0x0015, 0x0009, 0x0005, 0x0001, 0x5601};

const int MQ_Encoder::nMPS[] = { 1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
                     18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
                     35,36,37,38,39,40,41,42,43,44,45,45,46 };

const int MQ_Encoder::nLPS[] = { 1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
                     16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
                     32,33,34,35,36,37,38,39,40,41,42,43,46 };

const int MQ_Encoder::switchT[]={ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

MQ_Encoder::MQ_Encoder(void)
{
	int iWork1;

	for(iWork1 = 0; iWork1 < NUMBER_OF_CONTEXT; iWork1++){
		I[iWork1]	= 0;
		MPS[iWork1]	= 0;
	}

	I[UNIFORM]		= 46;
	I[RUNLENGTH]	= 3;
	I[0]			= 4;
	B = 0;
	initenc();
}

MQ_Encoder::~MQ_Encoder(void)
{
}


void MQ_Encoder::start(vector<struct context_label> &buffer)
{

	vector<struct context_label>::const_iterator pos;
	int CX;
	int D;
	int qetemp;
	int itemp;


	for(pos = buffer.begin(); pos < buffer.end(); pos++){
		CX  = pos->context;
		D	= pos->symbol;

		if(D == 0){
		// CODE0
			itemp	= I[CX];
			qetemp	= qe[itemp];
			if(MPS[CX] == 0){
			//CODEMPS
				A = A - qetemp;
				if((A & 0x8000) == 0){
					if(A < qetemp){
						A = qetemp;
					}else{
						C = C + qetemp;
					}
					I[CX] = nLPS[itemp];
					//RENORME
					do{
						A = A << 1;
						C = C << 1;
						CT = CT - 1;
						if(CT == 0){
						//BYTEOUT
							if(B == 0xFF){
								byte_buffer.push_back(B);
								B = C >> 20;
								C = C & 0xFFFF;
								CT = 7;
							}else{
								if(C < 0x8000000){
									byte_buffer.push_back(B);
									B = C >> 19;
									C = C & 0x7FFFF;
									CT = 8;							
								}else{
									B = B + 1;
									if(B == 0xFF){
										C = C & 0x7FFFFFF;
										byte_buffer.push_back(B);
										B = C >> 20;
										C = C & 0xFFFF;
										CT = 7;
									}else{
										byte_buffer.push_back(B);
										B = C >> 19;
										C = C & 0x7FFFF;
										CT = 8;
									}
								}
							}
						//BYTEOUT END
						}
					}while((A & 0x8000) == 0);
					//RENORME END		
				}else{
					C = C + qetemp;
				}
			//CODEMPS END
			}else{
			//CODELPS
				itemp	= I[CX];
				qetemp	= qe[itemp];
				A = A - qetemp;
				if(A < qetemp){
					C = C + qetemp;
				}else{
					A = qetemp;
				}
				
				if(switchT[itemp] == 1){
					MPS[CX] = 1 - MPS[CX];
				}
				
				I[CX] = nLPS[itemp];

				//RENORME
				do{
					A = A << 1;
					C = C << 1;
					CT = CT - 1;
					if(CT == 0){
					//BYTEOUT
						if(B == 0xFF){
							byte_buffer.push_back(B);
							B = C >> 20;
							C = C & 0xFFFF;
							CT = 7;
						}else{
							if(C < 0x8000000){
								byte_buffer.push_back(B);
								B = C >> 19;
								C = C & 0x7FFFF;
								CT = 8;							
							}else{
								B = B + 1;
								if(B == 0xFF){
									C = C & 0x7FFFFFF;
									byte_buffer.push_back(B);
									B = C >> 20;
									C = C & 0xFFFF;
									CT = 7;
								}else{
									byte_buffer.push_back(B);
									B = C >> 19;
									C = C & 0x7FFFF;
									CT = 8;
								}
							}
						}
					//BYTEOUT END
					}
				}while((A & 0x8000) == 0);
				//RENORME END
			}
			//CODELPS END
		}else{
		// CODE1
			itemp	= I[CX];
			qetemp	= qe[itemp];
			if(MPS[CX] == 1){
			//CODEMPS
				A = A - qetemp;
				if((A & 0x8000) == 0){
					if(A < qetemp){
						A = qetemp;
					}else{
						C = C + qetemp;
					}
					I[CX] = nLPS[itemp];
					//RENORME
					do{
						A = A << 1;
						C = C << 1;
						CT = CT - 1;
						if(CT == 0){
						//BYTEOUT
							if(B == 0xFF){
								byte_buffer.push_back(B);
								B = C >> 20;
								C = C & 0xFFFF;
								CT = 7;
							}else{
								if(C < 0x8000000){
									byte_buffer.push_back(B);
									B = C >> 19;
									C = C & 0x7FFFF;
									CT = 8;							
								}else{
									B = B + 1;
									if(B == 0xFF){
										C = C & 0x7FFFFFF;
										byte_buffer.push_back(B);
										B = C >> 20;
										C = C & 0xFFFF;
										CT = 7;
									}else{
										byte_buffer.push_back(B);
										B = C >> 19;
										C = C & 0x7FFFF;
										CT = 8;
									}
								}
							}
						//BYTEOUT END
						}
					}while((A & 0x8000) == 0);
					//RENORME END		
				}else{
					C = C + qetemp;
				}
			//CODEMPS END
			}else{
			//CODELPS
				itemp	= I[CX];
				qetemp	= qe[itemp];
				A = A - qetemp;
				if(A < qetemp){
					C = C + qetemp;
				}else{
					A = qetemp;
				}
				
				if(switchT[itemp] == 1){
					MPS[CX] = 1 - MPS[CX];
				}
				
				I[CX] = nLPS[itemp];

				//RENORME
				do{
					A = A << 1;
					C = C << 1;
					CT = CT - 1;
					if(CT == 0){
					//BYTEOUT
						if(B == 0xFF){
							byte_buffer.push_back(B);
							B = C >> 20;
							C = C & 0xFFFF;
							CT = 7;
						}else{
							if(C < 0x8000000){
								byte_buffer.push_back(B);
								B = C >> 19;
								C = C & 0x7FFFF;
								CT = 8;							
							}else{
								B = B + 1;
								if(B == 0xFF){
									C = C & 0x7FFFFFF;
									byte_buffer.push_back(B);
									B = C >> 20;
									C = C & 0xFFFF;
									CT = 7;
								}else{
									byte_buffer.push_back(B);
									B = C >> 19;
									C = C & 0x7FFFF;
									CT = 8;
								}
							}
						}
					//BYTEOUT END
					}
				}while((A & 0x8000) == 0);
				//RENORME END
			}
			//CODELPS END
		}
	}
}


void MQ_Encoder::initenc(){
	A	= 0x8000;
	C	= 0;
	CT	= 12;
	if(B = 0xFF){
		CT = 13;
	}
}

void MQ_Encoder::flush(){
	int TEMP;
	//SETBITS
	TEMP = C + A;
	C = C | 0xFFFF;
	if(C >= TEMP){
		C = C - 0x8000;
	}
	//SETBITS END

	C = C << CT;

	//BYTEOUT
		if(B == 0xFF){
			byte_buffer.push_back(B);
			B = C >> 20;
			C = C & 0xFFFF;
			CT = 7;
		}else{
			if(C < 0x8000000){
				byte_buffer.push_back(B);
				B = C >> 19;
				C = C & 0x7FFFF;
				CT = 8;							
			}else{
				B = B + 1;
				if(B == 0xFF){
					C = C & 0x7FFFFFF;
					byte_buffer.push_back(B);
					B = C >> 20;
					C = C & 0xFFFF;
					CT = 7;
				}else{
					byte_buffer.push_back(B);
					B = C >> 19;
					C = C & 0x7FFFF;
					CT = 8;
				}
			}
		}
	//BYTEOUT END

	C = C << CT;

	//BYTEOUT
		if(B == 0xFF){
			byte_buffer.push_back(B);
			B = C >> 20;
			C = C & 0xFFFF;
			CT = 7;
		}else{
			if(C < 0x8000000){
				byte_buffer.push_back(B);
				B = C >> 19;
				C = C & 0x7FFFF;
				CT = 8;							
			}else{
				B = B + 1;
				if(B == 0xFF){
					C = C & 0x7FFFFFF;
					byte_buffer.push_back(B);
					B = C >> 20;
					C = C & 0xFFFF;
					CT = 7;
				}else{
					byte_buffer.push_back(B);
					B = C >> 19;
					C = C & 0x7FFFF;
					CT = 8;
				}
			}
		}
	//BYTEOUT END

	if(B != 0xFF){
		byte_buffer.push_back(B);
	}
}
