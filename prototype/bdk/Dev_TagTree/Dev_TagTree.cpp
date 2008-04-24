// Dev_TagTree.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "TagTree.h"
#include "ByteBuffer.h"
#include <time.h>
#include <stdlib.h>
using namespace BDK;


void printmatrix(int in[7][7], int u, int v);
bool testTagTree(int size_u, int size_v, int maxvalue);

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char in[8] = { 1,0,1 ,4,6,6,3,0};
	unsigned char out[8];

	int testsize_u, testsize_v;

	ByteBuffer* puf		= new ByteBuffer();
	ByteBuffer* puf2	= new ByteBuffer(); 
	for(int i = 0; i < 3; i++){
		puf->add_bit(in[i]);
	}
	for(int i = 3; i < 8; i++){
		puf->add_byte(in[i]);
	}	

	for(int i = 0; i < 3; i++){
		out[i] = puf->get_next_bit();
	}
	for(int i = 3; i < 8; i++){
		out[i] =puf->get_next_byte();
	}	
/*
	for(int i = 0; i < 8; i++){
		printf("in = %d out = %d dif = %d\n", in[i], out[i], in[i] - out[i]);
	}
*/
	int example1[7][7] = {	{ 3, 4, 5, 6, 8, 4, 9},
							{ 0, 2, 3, 4, 7, 2, 8},
							{ 2, 3, 4, 7, 1, 4, 1},
							{ 9, 9, 9, 9, 9, 9, 9},
							{ 0, 2, 3, 4, 7, 2, 8},
							{ 2, 3, 4, 7, 1, 4, 1},
							{ 9, 9, 9, 9, 9, 9, 9}};

	int example2[7][7];

	int u1 = 7;
	int v1 = 7;
	TagTree* tagtree1 = new TagTree(u1, v1);
	TagTree* tagtree2 = new TagTree(u1, v1);

	for(int v = 0; v < v1; v++){
		for(int u = 0; u < u1; u++){
			tagtree1->setValue(u,v, example1[u][v]);
		}
	}

	tagtree1->printTagTree();

	for(int layer = 0; layer < 10; layer++){
		for(int v = 0; v < v1; v++){
			for(int u = 0; u < u1; u++){
				tagtree1->encodeValue(puf2,layer,u,v);	
			}
		}
	}

	

	for(int layer = 0; layer < 10; layer++){
		for(int v = 0; v < v1; v++){
			for(int u = 0; u < u1; u++){
				tagtree2->decodeValue(puf2,layer,u,v);	

				if(tagtree1->isfinal(u,v)){
					example2[u][v] = tagtree2->getValue(u, v);
				}
			}
		}
	}
	tagtree2->printTagTree();

	printf("bytest = %d \n", puf2->write_byte_pos);
	printmatrix(example1, 7, 7);
	printmatrix(example2, 7, 7);


	testsize_u = testsize_v = 88;
	for(int t = 1; t < testsize_u; t++){
		for(int r = 1; r < testsize_u; r++){

			if(testTagTree(r, t, 10)){
				printf("Test war erfolgreich \n");
			}else{
				printf("Test war nicht erfolgreich");
				t = r = testsize_u;
			}
		}
	}
	return 0;
}


void printmatrix(int in[7][7], int u, int v)
{

	for(int y = 0; y < v; y++){
		for(int x = 0; x < u; x++){
			printf(" %d ",in[x][y]);
		}
		printf("\n");
	}
	printf("\n");

}

bool equal(int* in1, int* in2, int size)
{
	bool back = true;

	for(int i = 0; i < size; i++){
		if(in1[i] != in2[i]){
			back = false;
			break;
		}
	}
	return back;
}

bool testTagTree(int size_u, int size_v, int maxvalue)
{
	TagTree* tagtree1	= new TagTree(size_u, size_v);
	TagTree* tagtree2	= new TagTree(size_u, size_v);
	ByteBuffer* puf		= new ByteBuffer();
	int totalsize		= size_u * size_v;
	
	bool back;
	time_t sek;
	time(&sek);
	srand((unsigned)sek);

	int* testwerte = (int*)malloc(sizeof(int) * totalsize);
	int* ergebniswerte =  (int*)malloc(sizeof(int) * totalsize);
	for(int i = 0; i < totalsize; i++){
		testwerte[i] = rand() % maxvalue;
	}

	for(int v = 0; v < size_v; v++){
		for(int u = 0; u < size_u; u++){
			tagtree1->setValue(u,v, testwerte[v * size_u + u]);
		}
	}

	for(int layer = 0; layer < maxvalue; layer++){
		for(int v = 0; v < size_v; v++){
			for(int u = 0; u < size_u; u++){
				tagtree1->encodeValue(puf,layer,u,v);	
			}
		}
	}

	for(int layer = 0; layer < maxvalue; layer++){
		for(int v = 0; v < size_v; v++){
			for(int u = 0; u < size_u; u++){
				tagtree2->decodeValue(puf,layer,u,v);	

				if(tagtree1->isfinal(u,v)){
					ergebniswerte[v * size_u + u] = tagtree2->getValue(u, v);
				}
			}
		}
	}

	back = equal(testwerte, ergebniswerte, totalsize);

	delete puf;
	delete tagtree1;
	delete tagtree2;
	free(testwerte);
	free(ergebniswerte);

	return back;
}
