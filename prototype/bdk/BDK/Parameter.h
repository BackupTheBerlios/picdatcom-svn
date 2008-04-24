#ifndef __PARAMETER_H__
#define __PARAMETER_H__




#include <windows.h>

#define lib_export  __declspec(dllexport)
#define lib_import  __declspec(dllimport)

typedef enum{	layer_resolution_level_component_position = 0,
				resolution_level_layer_component_position = 1,
				resolution_level_position_component_layer = 2,
				position_component_resolution_level_layer = 3,
				component_position_resolution_level_layer = 4} BDK_Progression_order;

typedef enum{	reversible,
				irreversible}BDK_Multiple_component_transformation_type;

typedef enum{	main_header,
				tile_part_header}BDK_use_in;

typedef enum{	scalar_expounded,
				scalar_derived,
				no_quantization}BDK_Quantization_style;

#define SCALAR_EXPOUNDED		0x02
#define	SCALAR_DERIVED			0x01
#define NO_QUANTIZATION			0x00

#define	DEFAULTPRECINCTSIZEBIT	0x1
#define SOPBIT					0x2
#define EPHBIT					0x4
#define MULTIPLE_TRANSFORMATION	0x1
#define	CCOC_DEFAULT			0xFF

#define SOC 0xFF4F
#define SIZ 0xFF51
#define EOC	0xFFD9
#define COD	0xFF52
#define QCD 0xFF5C
#define COM 0xFF64
#define SOT	0xFF90
#define SOD 0xFF93

#define SELECTIVE_ARITHMETIC_CODING_BYPASS	0x01	
#define RESET_CONTEXT_PROBALITIES			0x02
#define TERMINATION_ON_EACH_CODING_PASS		0x04
#define VERTICALLY_CAUSAL_CONTEXT			0x08
#define PREDICTABEL_TERMINATION				0x10
#define SEGMENTION_SYMBOLS_USED				0x20

#define NINESEVENFILTER						0x00
#define FIVETHREEFILTER						0x01

#define	DEFAULT_PRECINCT_SIZE				15

unsigned short	bytetoshort(const unsigned char* in, int pos);
unsigned int	bytetouint(const unsigned char* in, int pos);
bool is_known_mark(int mark);
unsigned int BDK_ui_max(unsigned int, unsigned int );
unsigned int BDK_ui_min(unsigned int, unsigned int );
int BDK_i_max(int, int );
int BDK_i_min(int, int );

int BDK_i_ceiling( int , int);
int BDK_i_floor( int , int);


#endif