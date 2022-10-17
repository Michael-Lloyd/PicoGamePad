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
	Gamepad * gamepad = Storage::getInstance().GetGamepad();
	gamepad->setup();

	// Check for Config or Regular Input (w/ Button Combos)
	InputMode inputMode = gamepad->options.inputMode;
	gamepad->read();
	if (gamepad->pressedF1() && gamepad->pressedUp()) { // BOOTSEL - Go to UF2 Flasher
		reset_usb_boot(0, 0);
	} else if (gamepad->pressedS2()) { 					// START - Config Mode
		Storage::getInstance().SetConfigMode(true);
		inputMode = INPUT_MODE_CONFIG; // force config
        initialize_driver(inputMode);
		ConfigManager::getInstance().setup(CONFIG_TYPE_WEB);
	} else { 											// Gamepad Mode
		Storage::getInstance().SetConfigMode(false);
		if (gamepad->pressedB3())                       // HOLD B3 - D-INPUT
			inputMode = INPUT_MODE_HID;
		else if (gamepad->pressedB1())                  // HOLD B1 - SWITCH
			inputMode = INPUT_MODE_SWITCH;
		else if (gamepad->pressedB2())                  // HOLD B2 - X-INPUT
			inputMode = INPUT_MODE_XINPUT;
		if (inputMode != gamepad->options.inputMode ) { // Save changes
			gamepad->options.inputMode = inputMode;
			gamepad->save();
		}
		initialize_driver(inputMode);
	}

	// Setup Add-on Inputs
	setupInput(new AnalogInput());
	setupInput(new I2CAnalog1219Input());
	setupInput(new JSliderInput());
	setupInput(new ReverseInput());
	setupInput(new TurboInput());
	
}

void PicoGamePad::run() {
	Gamepad * gamepad = Storage::getInstance().GetGamepad();
	Gamepad * processedGamepad = Storage::getInstance().GetProcessedGamepad();
	bool configMode = Storage::getInstance().GetConfigMode();
	while (1) { // LOOP
		// Config Loop (Web-Config does not require gamepad)
		if (configMode == true ) {
			ConfigManager::getInstance().loop();
			continue;
		}

		if (nextRuntime > getMicro()) { // fix for unsigned
			sleep_us(50); // Give some time back to our CPU (lower power consumption)
			continue;
		}

		// Gamepad Features
		gamepad->read(); 	// gpio pin reads
	#if GAMEPAD_DEBOUNCE_MILLIS > 0
		gamepad->debounce();
	#endif
		gamepad->hotkey(); 	// check for MPGS hotkeys
		gamepad->process(); // process through MPGS

		// Loop through all input modifiers/features (Analog Sticks, Turbo Buttons, Macro Inputs, Touch Screens, etc.) 
		for (std::vector<GPAddon*>::iterator it = Storage::getInstance().Inputs.begin(); it != Storage::getInstance().Inputs.end(); it++) {
			(*it)->process();
		}

		// Copy Processed Gamepad
		memcpy(&processedGamepad->state, &gamepad->state, sizeof(GamepadState));

		// USB FEATURES : Send/Get USB Features (including Player LEDs on X-Input)
		send_report(gamepad->getReport(), gamepad->getReportSize());
		Storage::getInstance().ClearFeatureData();
		receive_report(Storage::getInstance().GetFeatureData());
		tud_task(); // TinyUSB Task update

		nextRuntime = getMicro() + GAMEPAD_POLL_MICRO;
	}
}

void PicoGamePad::setupInput(GPAddon* input) {
	if (input->available()) {
		input->setup();
		Storage::getInstance().Inputs.push_back(input);
	}
}
