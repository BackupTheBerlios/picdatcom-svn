#include "Java_decoder.h"



	unsigned int Java_decoder::qe[] = {
							0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
							0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
							0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
							0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
							0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
							0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
							0x0015, 0x0009, 0x0005, 0x0001, 0x5601 };

    
	unsigned int Java_decoder::nMPS[] = {	
							1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
							18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
							35,36,37,38,39,40,41,42,43,44,45,45,46 };

	unsigned int Java_decoder::nLPS[] = {	
							1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
							16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
							32,33,34,35,36,37,38,39,40,41,42,43,46 };

	unsigned int Java_decoder::switchLM[] = {	
							1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


Java_decoder::Java_decoder(int nrOfContexts, int *init)
{
	        // Default initialization of the statistics bins is MPS=0 and
        // I=0
		bytebuffer = new ByteBuffer();
		delFF = false;
		I_length = nrOfContexts;
        I		= new int[nrOfContexts];
        mPS		= new int[nrOfContexts];
        initStates = init;

		nrOfWrittenBytes = -1;

        a=0x8000;
        c=0;
        if(b==0xFF) {
            cT=13;
        } else {
            cT=12;
        }

        resetCtxts();        

        // End of INITENC ---
        b=0;
}

void Java_decoder::resetCtxts()
{
	for(int i = 0; i < I_length; i++){
		mPS[i]	= 0;
		I[i]	= initStates[i];
	}
	
}


   void Java_decoder::codeSymbols(int* bits, int* cX, int n) {
        int q;
        int li; // local cache of I[context]
        int la;
        int nc;
        int ctxt; // context of current symbol
        int i; // counter

        // NOTE: here we could use symbol aggregation to speed things up.
        // It remains to be studied.
	
        la = a; // cache A register in local variable
        for(i=0; i<n; i++) {
            // NOTE: (a<0x8000) is equivalent to ((a&0x8000)==0)
            // since 'a' is always less than or equal to 0xFFFF

            // NOTE: conditional exchange guarantees that A for MPS is
            // always greater than 0x4000 (i.e. 0.375)
            // => one renormalization shift is enough for MPS
            // => no need to do a renormalization while loop for MPS

            ctxt = cX[i];
            li = I[ctxt];
            q = qe[li]; // Retrieve current LPS prob.
            
            if(bits[i]==mPS[ctxt]) { // -- Code MPS

                la -= q; // Interval division associated with MPS coding
                
                if(la>=0x8000) { // Interval big enough
                    c += q;
                } else { // Interval too short
                    if(la<q) {// Probabilities are inverted
                        la = q;
                    } else {
                        c += q;
                    }
                
                    I[ctxt]=nMPS[li];

                    // -- Renormalization (MPS: no need for while loop)
                    la <<= 1; // a is doubled
                    c <<= 1; // c is doubled
                    cT--;
                    if(cT==0) {
                        byteOut();
                    }
                    // -- End of renormalization
                }
            } else { // -- Code LPS
                la -= q; // Interval division according to LPS coding

                if(la<q) {
                    c += q;
                } else {
                    la = q;
                }
                if(switchLM[li]!=0) {
                    mPS[ctxt]=1-mPS[ctxt];
                }
                I[ctxt]=nLPS[li];
            
                // -- Renormalization

                // sligthly better than normal loop
                nc = 0;
                do {
                    la <<= 1;
                    nc++; // count number of necessary shifts
                } while (la<0x8000);
                if (cT>nc) {
                    c <<= nc;
                    cT -= nc;
                } else {
                    do {
                        c <<= cT;
                        nc -= cT;
                        // cT = 0; // not necessary
                        byteOut();
                    } while (cT<=nc);
                    c <<= nc;
                    cT -= nc;
                }
            
                // -- End of renormalization
            }
        }
        a = la; // save cached A register
    }

void Java_decoder::byteOut() {
        if(nrOfWrittenBytes>=0) {
            if(b==0xFF) {
                // Delay 0xFF byte
                delFF = true;
                b = c >> 20;
                c &= 0xFFFFF;
                cT = 7;
            } else if(c<0x8000000) {
                // Write delayed 0xFF bytes
                if (delFF) {
					bytebuffer->add_byte((unsigned char)0xFF);
                    delFF = false;
                    nrOfWrittenBytes++;
                }
                bytebuffer->add_byte(b);
                nrOfWrittenBytes++;
                b = c >> 19;
                c &= 0x7FFFF;
                cT=8;
            } else {
                b++;
                if(b==0xFF) {
                    // Delay 0xFF byte
                    delFF = true;
                    c &= 0x7FFFFFF;
                    b = c>>20;
                    c &= 0xFFFFF;
                    cT = 7;
                } else {
                    // Write delayed 0xFF bytes
                    if (delFF) {
                        bytebuffer->add_byte((unsigned char)0xFF);
                        delFF = false;
                        nrOfWrittenBytes++;
                    }
                    bytebuffer->add_byte(b);
                    nrOfWrittenBytes++;
                    b = ((c>>19)&0xFF);
                    c &= 0x7FFFF;
                    cT=8;
                }
            }
        } else {
            // NOTE: carry bit can never be set if the byte buffer was empty
            b = (c>>19);
            c &= 0x7FFFF;
            cT = 8;
            nrOfWrittenBytes++;
        }
    }
Java_decoder::~Java_decoder(void)
{
}
