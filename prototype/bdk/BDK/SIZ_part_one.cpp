// SIZ_part_one.cpp
//
// This header file defines the implementation of the class SIZ_part_one
//
// This file was generate from a Dia Diagram using the xslt script file dia-uml2cpp.xsl
// which is copyright(c) Dave Klotzbach <dklotzbach@foxvalley.net>
//
// The author asserts no additional copyrights on the derived product. Limitations
// on the uses of this file are the right and responsibility of authors of the source 
// diagram.
// 
// The dia-uml2cpp.xsl script is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
// more details.
//
// A copy of the GNU General Public License is available by writing to the 
// Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, 
// MA 02111-1307, USA.
//
// 
//
#include "SIZ_part_one.h"

#define OFFSET 2

BDK::SIZ_part_one::SIZ_part_one(unsigned char *ptr_char)
{
	unsigned short siz = 0;

	siz |= ptr_char[OFFSET + 0];
	siz <<= 8;
	siz |= ptr_char[OFFSET + 1];
	if(siz != SIZ){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "NO SIZ found" );
	}

	Lsiz = 0;
	Lsiz |= ptr_char[OFFSET + 2];
	Lsiz <<= 8;
	Lsiz |= ptr_char[OFFSET + 3];

	Rsiz = 0;
	Rsiz |= ptr_char[OFFSET + 4];
	Rsiz <<= 8;
	Rsiz |= ptr_char[OFFSET + 5];

	Xsiz = 0;
	Xsiz |= ptr_char[OFFSET + 6];
	Xsiz <<= 8;
	Xsiz |= ptr_char[OFFSET + 7];
	Xsiz <<= 8;
	Xsiz |= ptr_char[OFFSET + 8];
	Xsiz <<= 8;
	Xsiz |= ptr_char[OFFSET + 9];

	Ysiz = 0;
	Ysiz |= ptr_char[OFFSET + 10];
	Ysiz <<= 8;
	Ysiz |= ptr_char[OFFSET + 11];
	Ysiz <<= 8;
	Ysiz |= ptr_char[OFFSET + 12];
	Ysiz <<= 8;
	Ysiz |= ptr_char[OFFSET + 13];

	XOsiz = 0;
	XOsiz |= ptr_char[OFFSET + 14];
	XOsiz <<= 8;
	XOsiz |= ptr_char[OFFSET + 15];
	XOsiz <<= 8;
	XOsiz |= ptr_char[OFFSET + 16];
	XOsiz <<= 8;
	XOsiz |= ptr_char[OFFSET + 17];

	YOsiz = 0;
	YOsiz |= ptr_char[OFFSET + 18];
	YOsiz <<= 8;
	YOsiz |= ptr_char[OFFSET + 19];
	YOsiz <<= 8;
	YOsiz |= ptr_char[OFFSET + 20];
	YOsiz <<= 8;
	YOsiz |= ptr_char[OFFSET + 21];

	XTsiz = 0;
	XTsiz |= ptr_char[OFFSET + 22];
	XTsiz <<= 8;
	XTsiz |= ptr_char[OFFSET + 23];
	XTsiz <<= 8;
	XTsiz |= ptr_char[OFFSET + 24];
	XTsiz <<= 8;
	XTsiz |= ptr_char[OFFSET + 25];

	YTsiz = 0;
	YTsiz |= ptr_char[OFFSET + 26];
	YTsiz <<= 8;
	YTsiz |= ptr_char[OFFSET + 27];
	YTsiz <<= 8;
	YTsiz |= ptr_char[OFFSET + 28];
	YTsiz <<= 8;
	YTsiz |= ptr_char[OFFSET + 29];

	XTOsiz = 0;
	XTOsiz |= ptr_char[OFFSET + 30];
	XTOsiz <<= 8;
	XTOsiz |= ptr_char[OFFSET + 31];
	XTOsiz <<= 8;
	XTOsiz |= ptr_char[OFFSET + 32];
	XTOsiz <<= 8;
	XTOsiz |= ptr_char[OFFSET + 33];

	YTOsiz = 0;
	YTOsiz |= ptr_char[OFFSET + 34];
	YTOsiz <<= 8;
	YTOsiz |= ptr_char[OFFSET + 35];
	YTOsiz <<= 8;
	YTOsiz |= ptr_char[OFFSET + 36];
	YTOsiz <<= 8;
	YTOsiz |= ptr_char[OFFSET + 37];

	Csiz = 0;
	Csiz |= ptr_char[OFFSET + 38];
	Csiz <<= 8;
	Csiz |= ptr_char[OFFSET + 39];

}

void BDK::SIZ_part_one::set_SIZ_part_two(unsigned char *ptr_char)
{
	unsigned int i;
	for(i = 0; i < Csiz; i++){
		siz_part_two.push_back(new SIZ_part_two(ptr_char, i * 3));
		
	}
}

BDK::SIZ_part_one::~SIZ_part_one()
{
}
