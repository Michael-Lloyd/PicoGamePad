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

// PicoGamePad includes
#include "PicoGamePad.h"
#include "helpers.h"
#include "config.h" 
#include "storage.h"

// Pico includes
#include "pico/bootrom.h"

// TinyUSB
#include "usb_driver.h"
#include "tusb.h"

#define GAMEPAD_DEBOUNCE_MILLIS 5 // make this a class object

PicoGamePad::PicoGamePad() : nextRuntime(0) {
	Storage::getInstance().SetGamepad(
			new Gamepad(GAMEPAD_DEBOUNCE_MILLIS)
			);
	Storage::getInstance().SetProcessedGamepad(
			new Gamepad(GAMEPAD_DEBOUNCE_MILLIS)
			);
}

PicoGamePad::~PicoGamePad() {
}

void PicoGamePad::setup() {	

    // Setup Gamepad and Gamepad Storage
   // Gamepad * gamepad = Storage::getInstance().GetGamepad();
   // gamepad->setup();

   // // Check for Config or Regular Input (w/ Button Combos)
   // InputMode inputMode = gamepad->options.inputMode;
   // gamepad->read();

   // if (gamepad->pressedStart() && gamepad->pressedUp()) { // BOOTSEL - Go to UF2 Flasher
   // 	reset_usb_boot(0, 0);
   // } else { 											// Gamepad Mode
   // 	Storage::getInstance().SetConfigMode(false);
   // 	if (gamepad->pressedStart())                       
   // 		inputMode = INPUT_MODE_HID;
   // 	else if (gamepad->pressedSelect())                  
   // 		inputMode = INPUT_MODE_XINPUT;
   // 	if (inputMode != gamepad->options.inputMode ) { // Save changes
   // 		gamepad->options.inputMode = inputMode;
   // 		gamepad->save();
   // 	}
   // 	initialize_driver(inputMode);
   // }

}

void PicoGamePad::run() {

	//Gamepad * gamepad = Storage::getInstance().GetGamepad();
	//Gamepad * processedGamepad = Storage::getInstance().GetProcessedGamepad();
	//bool configMode = Storage::getInstance().GetConfigMode();

	//while (1) { // LOOP
	//	// Config Loop (Web-Config does not require gamepad)
	//	if (configMode == true ) {
	//		ConfigManager::getInstance().loop();
	//		continue;
	//	}

	//	if (nextRuntime > getMicro()) {
	//		sleep_us(50); 
	//		continue;
	//	}

	//	// Gamepad Features
	//	gamepad->read(); 	
	//	#if GAMEPAD_DEBOUNCE_MILLIS > 0
	//	gamepad->debounce();
	//	#endif
	//	

	//	// MPG Hotkey poll 
	//	gamepad->hotkey(); 	
	//	gamepad->process(); 

	//	// Copy Processed Gamepad
	//	memcpy(&processedGamepad->state, &gamepad->state, sizeof(GamepadState));

	//	// USB FEATURES : Send/Get USB Features (including Player LEDs on X-Input)
	//	send_report(gamepad->getReport(), gamepad->getReportSize());
	//	Storage::getInstance().ClearFeatureData();
	//	receive_report(Storage::getInstance().GetFeatureData());
	//	tud_task(); // TinyUSB Task update

	//	nextRuntime = getMicro() + GAMEPAD_POLL_MICRO;
	//}
}

void PicoGamePad::setupInput(GPAddon* input) {

   // if (input->available()) {
   // 	input->setup();
   // 	Storage::getInstance().Inputs.push_back(input);
   // }

}
