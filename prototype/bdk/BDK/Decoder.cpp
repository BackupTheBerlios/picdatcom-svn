// Decoder.cpp
//
// This header file defines the implementation of the class Decoder
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
#include "Decoder.h"



ofstream* error_stream;

BDK::Decoder::~Decoder()
{
}

//  Operation: Decoder
//
//  Description:
//   
//  Parameters:
//

BDK::Decoder::Decoder(ifstream *ptr_ifstream)
{
	unsigned short soc = 0;
	this->ptr_ifstream = ptr_ifstream;
	unsigned short MARK;
	int length = 200000, new_read_nr;
	streamsize read_nr;
	unsigned char *ptr_soc = new unsigned char[length];
	unsigned char *ptr_qcd_input;
	unsigned int tile;
	unsigned int codestream_length = 0;
	//unsigned long stream_pos;

	COD_read = false;
	QCD_need_to_create = false;

	decoder_state state = decoder_main;

	read_nr = 42;
	(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
	if((*this->ptr_ifstream).eof() == true){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
	}
	

	soc |= ptr_soc[0];
	soc <<= 8;
	soc |= ptr_soc[1];

	if(soc != SOC){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "No *.jpc file " );
	}

	ptr_SIZ_part_one = new SIZ_part_one(ptr_soc);
	read_nr = ptr_SIZ_part_one->Csiz * 3;
	if(read_nr > length){
		ptr_soc = (unsigned char*)realloc(ptr_soc, read_nr);
		length	= read_nr; 
	}
	(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
	if((*this->ptr_ifstream).eof() == true){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
	}
	ptr_SIZ_part_one->set_SIZ_part_two(ptr_soc);

	createStructure();

	read_nr = 2;
	(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
	if((*this->ptr_ifstream).eof() == true){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
	}
	MARK = ptr_soc[0];
	MARK <<= 8;
	MARK |= ptr_soc[1];	
	do{
		switch(MARK){
			case COD:
				read_nr = 2;
				(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
				}
				new_read_nr = ptr_soc[0];
				new_read_nr <<= 8;
				new_read_nr |= ptr_soc[1];	
				if(new_read_nr > length){
					ptr_soc = (unsigned char*)realloc(ptr_soc, new_read_nr);
					length	= new_read_nr;
				}
				read_nr = new_read_nr - 2;
				(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
				}
				if(state == decoder_main){
					set_COD(new Coding_style_default_COD(ptr_soc, read_nr + 2, main_header));
					
				}else if(state == decoder_tile){
					tiles[tile]->set_COD(new Coding_style_default_COD(ptr_soc, read_nr + 2, main_header));
					codestream_length -= (tiles[tile]->ptr_COD->Lcox + 2);
					tiles[tile]->COD_read	= true;		
				}
				break;
			case QCD:
				read_nr = 2;
				(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__,"Unexpected EOF");
				}
				new_read_nr = bytetoshort( ptr_soc, 0);
				read_nr = new_read_nr - 2;
				ptr_qcd_input = (unsigned char*) new unsigned char[read_nr];
				if(ptr_qcd_input == NULL){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "NO MEMORY");
				}
				(*this->ptr_ifstream).read((char*)ptr_qcd_input, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected EOF");
				}
				if(state == decoder_main){
					if(COD_read == true){
						set_QCD( new Quantization_default_QCD(ptr_qcd_input, read_nr + 2, ptr_COD));
					}else{
						throw new Default_Exceptionhandler(__FILE__, __LINE__, "Not yet implement");
					}
				}else if(state == decoder_tile){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Not yet implement");
				}

				break;
			case COM:
				read_nr = 2;
				(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__,"Unexpected EOF");
				}
				new_read_nr = bytetoshort( ptr_soc, 0);
				read_nr = new_read_nr - 2;
				if(read_nr > length){
					ptr_soc = (unsigned char*)realloc(ptr_soc, new_read_nr);
					length	= read_nr;
				}
				(*this->ptr_ifstream).read((char*)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected EOF");
				}
				ptr_COM = new Comment(new_read_nr, ptr_soc);
				break;
			case SOT:
				read_nr = 2;
				(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__,"Unexpected EOF");
				}
				new_read_nr = bytetoshort( ptr_soc, 0);
				read_nr = new_read_nr - 2;
				if(read_nr > length){
					ptr_soc = (unsigned char*)realloc(ptr_soc, new_read_nr);
					length	= read_nr;
				}
				(*this->ptr_ifstream).read((char*)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected EOF");
				}				
				tile = Start_of_tile_part_SOT::get_Isot(ptr_soc);
				if(tiles.size() <= tile){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Wrong Isot");
				}
				tiles[tile]->set_Tilepart(read_nr + 2 , ptr_soc);
				codestream_length = Start_of_tile_part_SOT::get_Psot(ptr_soc);
				codestream_length -= 12;
				state = decoder_tile;
				break;
			case SOD:
				read_nr = codestream_length - 2;
				if(read_nr > length){
					ptr_soc = (unsigned char*)realloc(ptr_soc, read_nr);
					length	= read_nr;
				}
				
				(*this->ptr_ifstream).read((char*)ptr_soc, read_nr);
				if((*this->ptr_ifstream).eof() == true){
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected EOF");
				}				
				if(state == decoder_tile){
					ByteBuffer *bytebuffer = new ByteBuffer(ptr_soc, read_nr);
					tiles[tile]->set_Codestream(read_nr, ptr_soc, bytebuffer);
					codestream_length = 0;
					state = decoder_main;
				}else{
					throw new Default_Exceptionhandler(__FILE__, __LINE__, "SOD without SOT");
				}
				break;
		}


		read_nr = 2;
		(*this->ptr_ifstream).read((char *)ptr_soc, read_nr);
		if(((*this->ptr_ifstream).eof() == true) && (this->ptr_ifstream->gcount() != read_nr)){
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unexpected EOF" );
		}

		MARK = ptr_soc[0];
		MARK <<= 8;
		MARK |= ptr_soc[1];	


		if(!is_known_mark(MARK)){
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unknown Mark", MARK );
		}
	}while((*this->ptr_ifstream).eof() != true && MARK != EOC);
	
	inverse_quantization_irreversible();
	start_Filter97_decoder();

	delete[] ptr_soc;
}


void BDK::Decoder::createStructure()
{
	double d_help;
	unsigned int nr_tiles;
	unsigned int ui_help;

	d_help = (double)(this->ptr_SIZ_part_one->Xsiz - this->ptr_SIZ_part_one->XTOsiz)/ (double) this->ptr_SIZ_part_one->XTsiz;
	this->numXtiles = (unsigned int) ceil(d_help);
	d_help = (double)(this->ptr_SIZ_part_one->Ysiz - this->ptr_SIZ_part_one->YTOsiz)/ (double) this->ptr_SIZ_part_one->YTsiz;
	this->numYtiles = (unsigned int) ceil(d_help);
	
	nr_tiles = this->numXtiles * this->numYtiles;

	for(ui_help = 0; ui_help < nr_tiles; ui_help++){
		tiles.push_back(new Tile(this, ui_help));
	}


}


void BDK::Decoder::set_COD(Coding_style_default_COD* ptr_COD)
{
	size_t num_tiles	= this->tiles.size();
	this->ptr_COD		= ptr_COD;
	COD_read			= true;

	for(size_t i = 0; i < num_tiles; i++){
		this->tiles[i]->set_COD(ptr_COD);
	}
}


void BDK::Decoder::set_QCD(Quantization_default_QCD* ptr_QCD)
{
	size_t num_tiles	= this->tiles.size();
	this->ptr_QCD = ptr_QCD;
	for(size_t i = 0; i < num_tiles; i++){
		this->tiles[i]->set_QCD(ptr_QCD);
	}
}

void BDK::Decoder::inverse_quantization_irreversible()
{
	size_t num_tiles	= this->tiles.size();
	for(size_t i = 0; i < num_tiles; i++){
		this->tiles[i]->inverse_quantization_irreversible();
	}
}

void BDK::Decoder::start_Filter97_decoder()
{
	size_t num_tiles	= this->tiles.size();
	for(size_t i = 0; i < num_tiles; i++){
		this->tiles[i]->start_Filter97_decoder();
	}
}

void BDK::Decoder::fill_RGBbuffer(unsigned char* buffer)
{
	clearRGBBuffer(buffer);
	size_t num_tiles	= this->tiles.size();
	for(size_t i = 0; i < num_tiles; i++){
		this->tiles[i]->fill_RGBbuffer( buffer);
	}
}


void BDK::Decoder::clearRGBBuffer(unsigned char* buffer)
{
	unsigned int size = (ptr_SIZ_part_one->Xsiz - ptr_SIZ_part_one->XOsiz) * (ptr_SIZ_part_one->Ysiz - ptr_SIZ_part_one->YOsiz);
	unsigned int run = (size * 3) % 4;
	unsigned int* work_buffer = (unsigned int*)(&buffer[run]);
	
	for(unsigned int i = 0; i < run; i+=1){
		buffer[i] = 0x80;
	}

	run = (size * 3) / 4;
	for(unsigned int i = 0; i < run; i+=1){
		work_buffer[i] = 0x80808080;
	}
}

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

lib_export void*  __cdecl create_Decoder_c(char* image_path, char* error_path)
{
	BDK::Decoder* decoder = NULL;

	if(error_path != NULL){
		error_stream = new ofstream(error_path);
		if(error_stream->fail()){
			error_stream->~basic_ofstream();
			error_stream = NULL;
		}
	}else{
		error_stream = NULL;
	}

	ifstream *ptr_ifstream;
	ptr_ifstream = new ifstream(image_path,ios::binary);

	if(ptr_ifstream->fail()){
		if(error_stream != NULL){
			(*error_stream)<<"Datei konnte nicht geöffnet werden";
		}
	}else{
		try{
			decoder = new BDK::Decoder(ptr_ifstream);
		}catch(BDK::Default_Exceptionhandler *e){
			if(error_stream != NULL){
				(*error_stream)<< e->toString().c_str()<<endl;
			}
		}
	}
	return (void*)decoder;
}


lib_export void*  __cdecl delete_Decoder(void* in_this)
{
	BDK::Decoder* decoder = (BDK::Decoder*) in_this;
	decoder->~Decoder();

	if(error_stream != NULL){
		error_stream->close();
	}
	
	return NULL;
}

lib_export unsigned int __cdecl get_SIZ_Lsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->Lsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_Rsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->Rsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_Xsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->Xsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_Ysiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->Ysiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_XOsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->XOsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_YOsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->YOsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_XTsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->XTsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_YTsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->YTsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_XTOsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->XTOsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_YTOsiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->YTOsiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_Csiz(void* decoder)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		back = fm_decoder->ptr_SIZ_part_one->Csiz;
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_Ssiz(void* decoder, int componente)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		if(componente >= 0 && componente < fm_decoder->ptr_SIZ_part_one->Csiz){
			back = fm_decoder->ptr_SIZ_part_one->siz_part_two[componente]->Ssiz;
		}
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_XRsiz(void* decoder, int componente)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		if(componente >= 0 && componente < fm_decoder->ptr_SIZ_part_one->Csiz){
			back = fm_decoder->ptr_SIZ_part_one->siz_part_two[componente]->XRsiz;
		}
	}
	return back;
}

lib_export unsigned int __cdecl get_SIZ_YRsiz(void* decoder, int componente)
{
	unsigned int back = 0;
	BDK::Decoder* fm_decoder = (BDK::Decoder*) decoder;
	if(fm_decoder != NULL){
		if(componente >= 0 && componente < fm_decoder->ptr_SIZ_part_one->Csiz){
			back = fm_decoder->ptr_SIZ_part_one->siz_part_two[componente]->YRsiz;
		}
	}
	return back;
}

/*
lib_export unsigned int __cdecl fill_buffer(void *decoder, int tile, int component, unsigned char *buffer, unsigned int width, unsigned int height)
{
	int back = 0;
	BDK::Decoder	*fm_decoder = (BDK::Decoder*)decoder;
	BDK::Tile		*fm_tile;
	BDK::Component	*fm_component;
	BDK::Data		*fm_data;
	if(tile < (int)fm_decoder->tiles.size()){
		fm_tile = fm_decoder->tiles[tile];
		if(component < (int)fm_tile->components.size()){
			fm_component = fm_tile->components[component];
			if(fm_component->data != NULL){
				fm_data = fm_component->data;
				fm_data->fill_buffer(buffer, width, height);
			}else{
				back = 1;
			}
		}else{
			back = 1;
		}
	}else{
		back = 1;
	}
	return back;
}
*/

lib_export unsigned int __cdecl fill_buffer(void *decoder, int tile, int component, unsigned char *buffer, unsigned int width, unsigned int height)
{
	int back = 0;
	BDK::Decoder	*fm_decoder = (BDK::Decoder*)decoder;

	fm_decoder->fill_RGBbuffer(buffer);

	return back;
}

#ifdef __cplusplus
}
#endif