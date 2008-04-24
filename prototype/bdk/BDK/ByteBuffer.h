

#ifndef __BYTEBUFFER_H__
#define __BYTEBUFFER_H__

#include "Default_Exceptionhandler.h"

namespace BDK
{
	class ByteBuffer
	{
	public:
		static unsigned int DEFAULT_INIT_SIZE;
		unsigned char*	buffer;
		unsigned int	write_byte_pos;
		unsigned int	write_bit_pos;
		unsigned int	read_byte_pos;
		unsigned int	read_bit_pos;
		unsigned int	buffer_size;
		bool			eobyte;
		bool			eobit;

		ByteBuffer();
		ByteBuffer(unsigned char* in, int length);
		ByteBuffer(ByteBuffer *bytebuffer, unsigned int  length);
		~ByteBuffer();

		void			add_bit(unsigned char in);
		void			add_byte(unsigned char in);
		void			add_byte(unsigned int in);
		void			add_bytes(ByteBuffer *bytebuffer, unsigned int length);
		unsigned char	get_next_bit( bool bitstuffing);
		unsigned char	get_next_byte();
		void			go_next_byte_without_padding();
		unsigned int	readbit(int anzahl, unsigned int in, bool bitstuffing);

		int				compare_byte(ByteBuffer *);

	private:
		void count_write_bit_up();
		void count_write_bit_up(int i);
		void realloc_buffer();
		void realloc_buffer(unsigned int minimum);
		void realloc_buffer_if_necessary(int size);
	};

}
#endif

