#include "TagTree.h"


BDK::Tag::Tag(Tagposition tagposition)
{
	this->tagposition	= tagposition;
	this->value			= 2147483647;
	this->valueknown	= 0;
	this->final			= false;
}


BDK::TagTree::TagTree(int u, int v)
{
	numlayer = BDK_i_max(getnumlayer(u), getnumlayer(v));
	int u1, v1;
	size_U = new int[numlayer];
	size_V = new int[numlayer];
	

	size_U[0] = u;
	size_V[0] = v;
	for(int i = 1; i < numlayer; i++){
		size_U[i] = BDK_i_ceiling(size_U[i - 1], 2);
		size_V[i] = BDK_i_ceiling(size_V[i - 1], 2);
	}

	tagtree = new Tag***[numlayer];
	numlayer--;
	for(int i = 0; i <= numlayer; i++){
		tagtree[i] = new Tag**[size_U[i]];

		for(int u = 0; u < size_U[i]; u++){
			tagtree[i][u] = new Tag*[size_V[i]];
			for(int v = 0; v < size_V[i]; v++){
				if(i == 0){
					if(i != numlayer){
						tagtree[i][u][v] = new Tag(FIRSTTAG);
					}else{
						tagtree[i][u][v] = new Tag(FIRSTLASTTAG);
					}
				}else if(i == numlayer){
					tagtree[i][u][v] = new Tag(LASTTAG);
				}else{
					tagtree[i][u][v] = new Tag(SOMETAG);
				}
			}
		}
	}

	for(int i = 0; i < numlayer; i++){
		for(int u = 0; u < size_U[i]; u++){
			for(int v = 0; v < size_V[i]; v++){
				u1 = BDK_i_floor(u,2);
				v1 = BDK_i_floor(v,2);
				tagtree[i][u][v]->next = tagtree[i+1][u1][v1];
			}
		}
	}
	numlayer++;
}
BDK::TagTree::~TagTree(void)
{
	for(int i = 0; i < numlayer; i++){		
		for(int u = 0; u < size_U[i]; u++){
			for(int v = 0; v < size_V[i]; v++){
				if(i == 0){
					delete tagtree[i][u][v];
				}else if(i == numlayer){
					delete  tagtree[i][u][v];
				}else{
					delete tagtree[i][u][v];
				}
			}
			delete[] tagtree[i][u];
		}
		delete[] tagtree[i];
	}
	delete[] tagtree;
}


int BDK::TagTree::getnumlayer(int size)
{
	int in = size;
	int count = 1;
	while(in > 1){
		in = BDK_i_ceiling(in, 2);
		count++;
	}

	return count;
}

void BDK::TagTree::setValue(int u, int v, int value)
{
	Tag* tag;

	if(u < 0 || v < 0){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}

	if(u >= size_U[0] || v >= size_V[0]){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	
	tag = tagtree[0][u][v];
	tag->value = value;

	while((tag->tagposition & LASTTAG) != LASTTAG){
		if(tag->value < tag->next->value){
			tag->next->value = tag->value;
			tag = tag->next;
		}else{
			break;
		}
	}
}

void BDK::TagTree::encodeValue(ByteBuffer* buffer, int max1, int u, int v)
{
	Tag* tag;
	int max = max1 + 1;
	if(u < 0 || v < 0){
		//throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	if(u >= size_U[0] || v >= size_V[0]){
		//throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	tag = tagtree[0][u][v];
	tag = goUp(tag);
	
	if((tag->tagposition & LASTTAG) != LASTTAG){
		if(tag->valueknown < tag->next->value){
			tag->valueknown = tag->next->value;
		}
	}
	
	while(!(tag->final && (tag->tagposition & FIRSTTAG) == FIRSTTAG))
	{
		while(tag->valueknown < tag->value && tag->valueknown < max)
		{
			buffer->add_bit(0);
			tag->valueknown++;
		}
		if(max > tag->value){
			buffer->add_bit(1);
			tag->final = true;
			if((tag->tagposition & FIRSTTAG) != FIRSTTAG){
				tag->wayBack->valueknown = tag->value;
				tag = tag->wayBack;
			}
		}else{
			break;
		}
	}
}


BDK::Tag* BDK::TagTree::goUp(BDK::Tag* in)
{
	Tag* back = in;
	while((back->tagposition & LASTTAG) != LASTTAG && back->next->final != true)
	{	
		back->next->wayBack = back;
		back = back->next;
	}
	return back;
}


bool BDK::TagTree::decodeValue(ByteBuffer* buffer, int max1, int u, int v)
{
	Tag* tag;
	Tag* tag_1;
	unsigned char bit;
	int max = max1 + 1;

	if(u < 0 || v < 0){
		//throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	if(u >= size_U[0] || v >= size_V[0]){
		//throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	tag_1 = tag = tagtree[0][u][v];
	tag = goUp(tag);

	if((tag->tagposition & LASTTAG) != LASTTAG){
		if(tag->valueknown < tag->next->value){
			tag->valueknown = tag->next->value;
		}
	}

	while(!(tag->final && (tag->tagposition & FIRSTTAG) == FIRSTTAG))
	{
		if(tag->valueknown < max){
			bit = buffer->get_next_bit(true);
			if(bit == 0){
				tag->valueknown++;
			}else{
				tag->value	= tag->valueknown;
				tag->final	= true;
				if((tag->tagposition & FIRSTTAG)  != FIRSTTAG){
					tag->wayBack->valueknown = tag->value;
					tag			= tag->wayBack;
				}
			}
		}else{
			break;
		}
	}

	return tag_1->final;
}


int	BDK::TagTree::getValue(int u, int v)
{
	int back = 0;
	
	Tag* tag;
		
	if(u < 0 || v < 0){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	if(u >= size_U[0] || v >= size_V[0]){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	tag = tagtree[0][u][v];

	back = tag->value;

	return back;
}



bool BDK::TagTree::isfinal(int u, int v)
{
	bool back = false;
	
	Tag* tag;
		
	if(u < 0 || v < 0){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	if(u >= size_U[0] || v >= size_V[0]){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Out of range "); 
	}
	tag = tagtree[0][u][v];

	back = tag->final;
	return back;

}


void BDK::TagTree::printTagTree()
{
	int u1,v1;
	Tag* tag;
	for(int l = 0; l < numlayer; l++)
	{
		u1 = size_U[l];
		v1 = size_V[l];
		for(int y = 0; y < v1; y++){
			for(int x = 0; x < u1; x++){
				tag =  tagtree[l][x][y];
				printf(" %d ", tag->value);
			}
			printf("\n");
		}
		printf("\n");
	}

}

void BDK::TagTree::printTagTree1()
{
	int u1,v1;
	Tag* tag;
	for(int l = 0; l < numlayer; l++)
	{
		u1 = size_U[l];
		v1 = size_V[l];
		for(int y = 0; y < v1; y++){
			for(int x = 0; x < u1; x++){
				tag =  tagtree[l][x][y];
				printf(" %d ", tag->valueknown);
			}
			printf("\n");
		}
		printf("\n");
	}

}
