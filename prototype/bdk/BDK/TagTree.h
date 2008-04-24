#pragma once

#include "Parameter.h"
#include "ByteBuffer.h"

namespace BDK
{

	typedef enum{FIRSTTAG = 1, LASTTAG = 2, FIRSTLASTTAG = 3,  SOMETAG = 4} Tagposition;

	class Tag
	{
	public:
		Tag*		next;
		Tag*		wayBack;
		int			value;
		int			valueknown;
		bool		final;
		Tagposition	tagposition;

		Tag(Tagposition tagposition);
		
	};

	class TagTree
	{
	private:
		int* size_U;
		int* size_V;
		int numlayer;

		Tag**** tagtree;  // [layer][u][v]

		int		getnumlayer(int size);
		Tag*	goUp(Tag* in);
	public:
		TagTree(int u, int v);
		~TagTree(void);

		void	setValue(int u, int v, int value);
		void	encodeValue(ByteBuffer* buffer, int max1, int u, int v);
		bool 	isfinal(int u, int v);
		bool	decodeValue(ByteBuffer* buffer, int max1, int u, int v);
		int		getValue(int u, int v);

		void	printTagTree();
		void	printTagTree1();
	};
};