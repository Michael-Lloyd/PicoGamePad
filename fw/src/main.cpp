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

// ================================================================================================
// MAIN GLOBALS & CONTROLS
// ================================================================================================

// Yes, it does seem redundant, but these can allow for programmatic handling of 
// deprecated code. 
#ifndef _PICOPAD_ 
#define _PICOPAD_ 
#define _PICOPAD_VERSION_MAJOR 1
#define _PICOPAD_VERSION_MINOR 0
#define _PICOPAD_VERSION_PATCH 0 
#define _PICOPAD_VERSION_INT   100000000

// If for some reason I need to control returns between the main function or not. 
#ifndef _PICOPAD_CTRLCODES_
#define _PICOPAD_CTRLCODES_
#ifndef OVERRIDE_FAIL 
#define OVERRIDE_FAIL false
#endif 
#ifndef OVERRIDE_LOOP
#define OVERRIDE_LOOP false
#endif
#endif 

// * - *


#include "include/picoSystem.h" 

System picopad(GLOBAL_DEBOUNCE_WINDOW);

// ================================================================================================
// MAIN
// ================================================================================================

int main() {

	// Initialization of all settings within the System class occurs
	// here. Including storage handling.  
	picopad.setup();

	while(!OVERRIDE_FAIL) {

		switch(picopad.getMode()) { 
			case(MODE_PROG): // Open programming interfaces and standby 
				break; 
			case(MODE_DEBUG): // Further debugging information or selections (if necessary) 

				// The mode flag isn't parsed by the preprocessor under the class 
				// So, if you intend to debug the board, you need to assign the mask.
				// Benefit? Until defined, it will nuke objects stemming from debug calls.
				#if !defined(PICOPAD_DEBUG_MASK)
					#define PICOPAD_DEBUG_MASK false 
				#endif 
				PICOPAD_DEBUG_MASK && continue; 
				break; 
			case(MODE_CONFIGURE): // Similar to PROG, but does not overwrite program space 
				break; 
			case(MODE_PLAY): 
				picopad.flash.save(); 
				picopad.flash.load();
				while(!OVERRIDE_LOOP) { 
					picopad.update()
				}
				break; // :| 
			default:
				// Debug mode default 
				picopad.setMode(MODE_DEBUG); 
				break; 
		} 

	}

	return 0;
}

// * - *

#endif
