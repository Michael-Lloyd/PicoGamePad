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

#ifndef _PICO_SYSTEM_
#define _PICO_SYSTEM_ 

#define GLOBAL_DEBOUNCE_WINDOW 15 // in s/10^3

enum _sys_mode = { 
		MODE_PROG,
		MODE_DEBUG,
		MODE_CONFIGURE,
		MODE_PLAY,
}; 

typedef _sys_mode runMode; 


class System { 
	
	public:
		inline System(uint16_t t); 
		void setup(); 
		void update(); 
}; 

#endif 
