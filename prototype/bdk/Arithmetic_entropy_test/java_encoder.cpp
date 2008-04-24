#include "java_encoder.h"


	unsigned int java_encoder::qe[] = {
							0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
							0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
							0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
							0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
							0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
							0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
							0x0015, 0x0009, 0x0005, 0x0001, 0x5601 };

    
	unsigned int java_encoder::nMPS[] = {	
							1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
							18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
							35,36,37,38,39,40,41,42,43,44,45,45,46 };

	unsigned int java_encoder::nLPS[] = {	
							1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
							16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
							32,33,34,35,36,37,38,39,40,41,42,43,46 };

	unsigned int java_encoder::switchLM[] = {	
							1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

java_encoder::java_encoder(ByteBuffer *bytebuffer,  const int length, unsigned int* default_mps,  unsigned int* default_index)
{
	this->bytebuffer = bytebuffer;
	I		= new unsigned int[length];
	mPS		= new unsigned int[length];
	initStates = default_index;
	I_length = length;

	init();

	// Set the contexts
	resetCtxts();
}

void java_encoder::init()
{
     // Read first byte
       b = bytebuffer->get_next_byte();

        // Software conventions decoder
        c=(b^0xFF)<<16;
        byteIn();
        c=c<<7;
        cT=cT-7;
        a=0x8000;
}

void java_encoder::byteIn()
{
	if(b==0xFF){
		b=bytebuffer->get_next_byte(); // Convert EOFs (-1) to 0xFF

		if(b>0x8F){
			//markerFound=true;
			// software-convention decoder: c unchanged
			cT=8;
		}else{
			c += 0xFE00 - (b<<9);
			cT=7;
		}
	} else {
		b=bytebuffer->get_next_byte(); // Convert EOFs (-1) to 0xFF
		c += 0xFF00 - (b<<8);
		cT=8;
	}
}

java_encoder::~java_encoder(void)
{
}

void java_encoder::resetCtxts()
{
	for(int i = 0; i < I_length; i++){
		mPS[i]	= 0;
		I[i]	= initStates[i];
	}
}

unsigned char java_encoder::decodeSymbol(unsigned int context){
    int q			= 0;
    int la			= 0;
    int index		= 0;
    int decision	= 0;

    index = I[context];
    q = qe[index];
    
    // NOTE: (a < 0x8000) is equivalent to ((a & 0x8000)==0)
    // since 'a' is always less than or equal to 0xFFFF

    // NOTE: conditional exchange guarantees that A for MPS is
    // always greater than 0x4000 (i.e. 0.375)
    // => one renormalization shift is enough for MPS
    // => no need to do a renormalization while loop for MPS

    a -= q;
    if ((c>>16) < a) {
        if(a >= 0x8000){
            decision = mPS[context];
        }
        else {
            la = a;
            // -- MPS Exchange
            if(la >= q){
                decision = mPS[context];
                I[context] = nMPS[index];
                // -- Renormalize (MPS: no need for while loop)
                if(cT==0)
                    byteIn();
                la<<=1;
                c<<=1;
                cT--;
                // -- End renormalization
            }
            else{
                decision = 1-mPS[context];
                if(switchLM[index]==1)
                    mPS[context] = 1-mPS[context];
                I[context] = nLPS[index];
                // -- Renormalize
                do{
                    if(cT==0)
                        byteIn();
                    la<<=1;
                    c<<=1;
                    cT--;
                }while(la < 0x8000);
                // -- End renormalization
            }
            // -- End MPS Exchange
            a = la;
        }
    }
    else {
        la = a;
        c -= (la<<16);
        // -- LPS Exchange
        if(la < q){
            la = q;
            decision = mPS[context];
            I[context] = nMPS[index];
            // -- Renormalize (MPS: no need for while loop)
            if(cT==0)
                byteIn();
            la<<=1;
            c<<=1;
            cT--;
            // -- End renormalization
        }
        else {
            la = q;
            decision = 1-mPS[context];
            if(switchLM[index] == 1)
                mPS[context] = 1-mPS[context];
            I[context] = nLPS[index];
            // -- Renormalize
            do{
                if(cT==0)
                    byteIn();
                la<<=1;
                c<<=1;
                cT--;
            } while (la < 0x8000);
            // -- End renormalization
        }
        // -- End LPS Exchange

        a = la;
    }
    return decision;
}