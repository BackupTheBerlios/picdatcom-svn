#include "ByteBuffer.h"

unsigned int BDK::ByteBuffer::DEFAULT_INIT_SIZE = 1024;

BDK::ByteBuffer::ByteBuffer()
{
	buffer_size		= DEFAULT_INIT_SIZE;
	buffer			= new unsigned char[DEFAULT_INIT_SIZE];
	write_byte_pos	= 0;
	write_bit_pos	= 0;
	read_byte_pos	= 0;
	read_bit_pos	= 0;
	eobit			= false;
	eobyte			= false;
}


BDK::ByteBuffer::ByteBuffer(unsigned char* in, int length)
{
	buffer_size		= DEFAULT_INIT_SIZE + length;
	buffer			= new unsigned char[buffer_size];
	write_byte_pos	= 0;
	write_bit_pos	= 0;
	read_byte_pos	= 0;
	read_bit_pos	= 0;
	eobit			= false;
	eobyte			= false;

	for(int i = 0; i < length; i++){
		buffer[i] = in[i];
	}
	write_byte_pos = length;
}

void BDK::ByteBuffer::add_bit(unsigned char in)
{
	int shift = 7 - write_bit_pos;

	unsigned char bit = 1 << shift;

	if(in == 0){
		bit ^= 0xFF;
		buffer[write_byte_pos] &= bit;
	}else{
		buffer[write_byte_pos] |= bit;
	}

	
	count_write_bit_up();
}

void BDK::ByteBuffer::count_write_bit_up()
{
	write_bit_pos++;
	if(write_bit_pos > 7){
		write_bit_pos = 0;
		write_byte_pos += 1;
		if(write_byte_pos >= buffer_size){
			realloc_buffer();
		}
	}
}

void BDK::ByteBuffer::count_write_bit_up(int i)
{
	unsigned int byts_plus = i/8;
	unsigned int bits_plus = i%8;
	
	unsigned int new_write_bit_pos	= write_bit_pos + bits_plus;
	unsigned int new_write_byte_pos	= write_byte_pos + byts_plus;

	if(new_write_bit_pos > 7){
		new_write_bit_pos	= 7 - new_write_bit_pos;
		new_write_byte_pos	+= 1;
	}
}

void BDK::ByteBuffer::realloc_buffer()
{
	realloc_buffer(0);
}

void BDK::ByteBuffer::realloc_buffer(unsigned int minimum)
{
	unsigned int newlength = buffer_size + DEFAULT_INIT_SIZE;
	if(DEFAULT_INIT_SIZE < minimum)
	{
		newlength = buffer_size + minimum;
	}

	unsigned char* temp_buffer = new unsigned char[newlength];
	if(temp_buffer == NULL){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"No memory");
	}
	for(unsigned int i = 0; i < buffer_size; i += 1){
		temp_buffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer		= temp_buffer;
	buffer_size = newlength;
}

void BDK::ByteBuffer::realloc_buffer_if_necessary(int size)
{
	unsigned int new_write_byte_pos = size + write_byte_pos;
	unsigned int mini;
	if(new_write_byte_pos >= buffer_size){
		mini = new_write_byte_pos + 1 - buffer_size;
		realloc_buffer(mini);
	}
}

void BDK::ByteBuffer::add_byte(unsigned char in)
{
	int leftshift, rightshift;
	unsigned char uc_help;

	if(write_bit_pos == 0){
		buffer[write_byte_pos] = in;
		write_byte_pos += 1;
		if(write_byte_pos >= buffer_size){
			realloc_buffer();
		}
	}else{
		rightshift	= write_bit_pos;
		leftshift	= 8 - write_bit_pos;
		buffer[write_byte_pos] &= (0xFF << leftshift);
		uc_help = in >> rightshift;
		buffer[write_byte_pos] |=uc_help;
		write_byte_pos += 1;
		if(write_byte_pos >= buffer_size){
			realloc_buffer();
		}
		buffer[write_byte_pos] = in << leftshift;

	}
}

void BDK::ByteBuffer::add_byte(unsigned int in1)
{
	unsigned char  in = (in1 & 0xFF);
	int leftshift, rightshift;
	unsigned char uc_help;

	if(write_bit_pos == 0){
		buffer[write_byte_pos] = in;
		write_byte_pos += 1;
		if(write_byte_pos >= buffer_size){
			realloc_buffer();
		}
	}else{
		rightshift	= write_bit_pos;
		leftshift	= 8 - write_bit_pos;
		buffer[write_byte_pos] &= (0xFF << leftshift);
		uc_help = in >> rightshift;
		buffer[write_byte_pos] |=uc_help;
		write_byte_pos += 1;
		if(write_byte_pos >= buffer_size){
			realloc_buffer();
		}
		buffer[write_byte_pos] = in << leftshift;

	}
}

unsigned char BDK::ByteBuffer::get_next_bit( bool bitstuffing)
{
	unsigned char back = 0;
	if(eobit == false){
		if(write_byte_pos > read_byte_pos)
		{
			back = buffer[read_byte_pos];
			back >>= (7 - read_bit_pos);
			back &= 1;
			read_bit_pos += 1;
			if(read_bit_pos > 7){
				if(buffer[read_byte_pos] == 255 && bitstuffing){
					read_bit_pos = 1;
					read_byte_pos += 1;
				}else{
					read_bit_pos = 0;
					read_byte_pos += 1;
				}
			}
		}else if(write_byte_pos == read_byte_pos){
			if(write_bit_pos > read_bit_pos){
				back = buffer[read_byte_pos];
				back >>= (7 - read_bit_pos);
				back &= 1;
			}else{
				eobit	= true;
				eobyte	= true;
			}
			read_bit_pos += 1;
			if(read_bit_pos > 7){
				read_bit_pos = 0;
				read_byte_pos += 1;
			}		
		}else{
			eobit	= true;
			eobyte	= true;
		}
	}
	return back;
}

/*
unsigned char BDK::ByteBuffer::get_next_bit()
{
	unsigned char back = 0;
	if(eobit == false){
		if(write_byte_pos > read_byte_pos)
		{
			back = buffer[read_byte_pos];
			back >>=  read_bit_pos;
			back &= 1;
			read_bit_pos += 1;
			if(read_bit_pos > 7){
				read_bit_pos = 0;
				read_byte_pos += 1;
			}
		}else if(write_byte_pos == read_byte_pos){
			if(write_bit_pos > read_bit_pos){
				back = buffer[read_byte_pos];
				back >>= read_bit_pos;
				back &= 1;
			}else{
				eobit	= true;
				eobyte	= true;
			}
			read_bit_pos += 1;
			if(read_bit_pos > 7){
				read_bit_pos = 0;
				read_byte_pos += 1;
			}		
		}else{
			eobit	= true;
			eobyte	= true;
		}
	}
	return back;
}
*/


unsigned char BDK::ByteBuffer::get_next_byte()
{
	unsigned char back = 0xFF;
	if(eobit == false && eobyte == false){
		if(write_byte_pos > read_byte_pos)
		{	
			if(read_bit_pos == 0){
				back = buffer[read_byte_pos];
				read_byte_pos += 1;
			}else{
				if((write_byte_pos > (read_byte_pos + 1)) || (write_bit_pos > read_bit_pos)){
					back = buffer[read_byte_pos];
					back <<= read_bit_pos;
					read_byte_pos += 1;
					back |= (buffer[read_byte_pos] >> (8 - read_bit_pos));
				}else{
					eobyte	= true;
				}
			}
		}else{
			eobyte	= true;
		}
	}
	return back;
}

BDK::ByteBuffer::~ByteBuffer()
{
	delete[] buffer; 
}


void BDK::ByteBuffer::go_next_byte_without_padding()
{
	if(read_bit_pos != 0){
		if(eobit == false && eobyte == false){
			if(write_byte_pos > read_byte_pos){
				read_bit_pos	= 0;	
				read_byte_pos	+= 1;
			}else{
				eobyte	= true;				
			}
			if(write_byte_pos <= read_byte_pos){
				eobyte	= true;	
				eobit	= true;
			}
		}
	}
}

unsigned int BDK::ByteBuffer::readbit(int anzahl, unsigned int in, bool bitstuffing)
{
	unsigned char bit;
	
	for(int i = 0; i < anzahl; i++){
		bit = get_next_bit(bitstuffing);	
		in <<= 1;
		if(bit != 0){
			in |= 1;	
		}
	}
	return in;
}


BDK::ByteBuffer::ByteBuffer(ByteBuffer *bytebuffer, unsigned int length)
{
	buffer_size		= length + 1;
	buffer			= new unsigned char[buffer_size];
	write_byte_pos	= 0;
	write_bit_pos	= 0;
	read_byte_pos	= 0;
	read_bit_pos	= 0;
	eobit			= false;
	eobyte			= false;
	unsigned int	end = write_byte_pos + length;

	for(; write_byte_pos < end && bytebuffer->eobyte	== false;){
		buffer[write_byte_pos] = bytebuffer->buffer[bytebuffer->read_byte_pos];

		write_byte_pos++;
		bytebuffer->read_byte_pos++;
		if(bytebuffer->read_byte_pos >= bytebuffer->write_byte_pos){
			bytebuffer->eobyte	= true;
		}
	}

	if(write_byte_pos < end){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Can´t create buffer." );
	}
}


void BDK::ByteBuffer::add_bytes(ByteBuffer *bytebuffer, unsigned int length)
{
	unsigned int	end = write_byte_pos + length;

	if((write_byte_pos + length) >= buffer_size){
		realloc_buffer(length + 1);
	}

	for(; write_byte_pos < end && bytebuffer->eobyte	== false;){
		buffer[write_byte_pos] = bytebuffer->buffer[bytebuffer->read_byte_pos];

		write_byte_pos++;
		bytebuffer->read_byte_pos++;
		if(bytebuffer->read_byte_pos >= bytebuffer->write_byte_pos){
			bytebuffer->eobyte	= true;
		}
	}

	if(write_byte_pos < end){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Can´t create buffer." );
	}
}

int BDK::ByteBuffer::compare_byte(ByteBuffer *buffert)
{
	int back = 1;
	unsigned int i = 0;
	if(buffert->write_byte_pos == write_byte_pos){
		back = 0;
		for(i = 0; i < buffert->write_byte_pos; i++){
			back += (int)buffert->buffer[i] - (int)buffer[i];
		}
	}else{
		back = -1;
	}
	return back;
}
