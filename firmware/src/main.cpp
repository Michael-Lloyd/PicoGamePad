/*
 *  Author:     Michael Lloyd (micl.dev)
 *  Version:    _version
 *  Variant:    _variant
 *  Date:       _date
 *
 *      __   ___.--'_`. 
 *     ( _`.'. -   'o` ) 
 *     _\.'_'      _.-'  
 *     ( `. )    //`    
 *     \_`-'`---'\__,   
 *      \`        \`--    
 *
 */

#include "pico/multicore.h"

#include "PicoGamePad.h"
#include "PicoGamePadAlt.h"

void core1() {

	multicore_lockout_victim_init(); // block core 1

	// Create PicoGamePad w/ Additional Modules for Core 1
	PicoGamePadAlt * gamepadCore1 = new PicoGamePadAlt();
	gamepadCore1->setup();
	gamepadCore1->run();
}


int main() {
	// Create PicoGamePad Main Core (core0), Core1 is dependent on Core0
	PicoGamePad * gamepad = new PicoGamePad();
	gamepad->setup();

	// Create PicoGamePad Thread for Core1
	multicore_launch_core1(core1);

	// Start Core0 Loop
	gamepad->run();
	return 0;
}
