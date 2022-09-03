/*
 *  Author:     Michael Lloyd (micl.dev)
 *  Version:    1.0.0
 *  Variant:    A
 *  Date:       21/09/22
 *
 *      __   ___.--'_`. 
 *     ( _`.'. -   'o` ) 
 *     _\.'_'      _.-'  
 *     ( `. )    //`    
 *     \_`-'`---'\\__,   
 *      \\`        \`--    
 *
 */

#ifndef _STORAGE_H
#define _STORAGE_H 

#define PICOPAD_STORAGE_INDEX		0
#define BOARD_STORAGE_INDEX			1024

using pinOpt = uint8_t; 
using pinNum = uint16_t; 

typedef enum { 
	PICOPAD_V3_TYPE_A,
	PICOPAD_V3_TYPE_B,
	PICOPAD_V4_TYPE_A,
	CUSTOM_BOARD_LAYOUT
} BoardLayout; 

typedef struct _opts { 

	bool		hasOptions;

	// Pin assignments are not configured as magic numbers!
	// These are defined during the setup routine. 
	pinOpt		pinBtnUp;
	pinOpt		pinBtnDown;
	pinOpt		pinBtnLeft;
	pinOpt		pinBtnRight; 
	pinOpt		pinBtnB;
	pinOpt		pinBtnA;
	pinOpt		pinBtnSelect;
	pinOpt		pinBtnStart;

	ButtonLayout buttonLayout;   

	pinNum		i2cSDA;
	pinNum		i2cSCL;
	int 		i2cBlk;  // FIXME: uint or int?
	uint32_t	i2cSpeed;

	// FIXME: 
	// I'm probably not going to do CRC 
	uint32_t	chksum; 

} BoardOptions;  

// FIXME: A class might be nicer than the global. 
BoardOptions getBoardOptions; 
void setBoardOptions(BoardOptions opts);


#endif 
