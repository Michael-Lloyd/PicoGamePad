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


#include "PicoGamePadAlt.h"
#include "gamepad.h"
#include "storage.h" // Managers
#include "addons/ws2812b.h"

#include <iterator>

PicoGamePadAlt::PicoGamePadAlt() {
}

PicoGamePadAlt::~PicoGamePadAlt() {
}

void PicoGamePadAlt::setup() {
	//setupAddon(new LEDAddon());
}

void PicoGamePadAlt::run() {
	while (1) {
		for (std::vector<GPAddon*>::iterator it = Storage::getInstance().Addons.begin(); it != Storage::getInstance().Addons.end(); it++) {
			(*it)->process();
		}
	}
}

void PicoGamePadAlt::setupAddon(GPAddon* addon) {
	if (addon->available()) {
		addon->setup();
		Storage::getInstance().Addons.push_back(addon);
	}
}
