#define lib_import extern "C" __declspec(dllimport) 

lib_import void* __cdecl  create_Decoder_c(char* image_path, char* error_path);
lib_import void* __cdecl  delete_Decoder(void* in_this);
lib_import unsigned int __cdecl get_SIZ_Lsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_Rsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_Xsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_Ysiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_XOsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_YOsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_XTsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_YTsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_XTOsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_YTOsiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_Csiz(void* decoder);
lib_import unsigned int __cdecl get_SIZ_Ssiz(void* decoder, int componente);
lib_import unsigned int __cdecl get_SIZ_XRsiz(void* decoder, int componente);
lib_import unsigned int __cdecl get_SIZ_YRsiz(void* decoder, int componente);
lib_import unsigned int __cdecl fill_buffer(void* decoder, int tile, int component, unsigned char *buffer, unsigned int whidth, unsigned int height);