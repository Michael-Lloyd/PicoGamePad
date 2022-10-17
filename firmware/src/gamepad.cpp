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


#include "gamepad.h"
#include "storage.h"

#include "FlashPROM.h"
#include "CRC32.h"

// MUST BE DEFINED for mpgs
uint32_t getMillis() {
	return to_ms_since_boot(get_absolute_time());
}

uint64_t getMicro() {
	return to_us_since_boot(get_absolute_time());
}

void Gamepad::setup() {

	load(); // MPG load call is here (?) 

	// Configure pin mapping
	BoardOptions boardOptions = Storage::getInstance().getBoardOptions();

	mapDpadUp    = new GamepadButtonMapping(boardOptions.pinDpadUp,    GAMEPAD_MASK_UP);
	mapDpadDown  = new GamepadButtonMapping(boardOptions.pinDpadDown,  GAMEPAD_MASK_DOWN);
	mapDpadLeft  = new GamepadButtonMapping(boardOptions.pinDpadLeft,  GAMEPAD_MASK_LEFT);
	mapDpadRight = new GamepadButtonMapping(boardOptions.pinDpadRight, GAMEPAD_MASK_RIGHT);
	//mapButtonA  = new GamepadButtonMapping(boardOptions.pinButtonA,  GAMEPAD_MASK_A);

	gamepadMappings = new GamepadButtonMapping *[GAMEPAD_DIGITAL_INPUT_COUNT] {
		mapDpadUp, mapDpadDown, mapDpadLeft, mapDpadRight
	};

	for (int i = 0; i < GAMEPAD_DIGITAL_INPUT_COUNT; i++) {
		gpio_init(gamepadMappings[i]->pin);             // Initialize pin
		gpio_set_dir(gamepadMappings[i]->pin, GPIO_IN); // Set as INPUT
		gpio_pull_up(gamepadMappings[i]->pin);          // Set as PULLUP
	}

	#ifdef PIN_SETTINGS
		gpio_init(PIN_SETTINGS);             // Initialize pin
		gpio_set_dir(PIN_SETTINGS, GPIO_IN); // Set as INPUT
		gpio_pull_up(PIN_SETTINGS);          // Set as PULLUP
	#endif
}

void Gamepad::process() {
	memcpy(&rawState, &state, sizeof(GamepadState));
	// MPG update 
	MPGS::process();
}

void Gamepad::read() {

	// Pullup
	uint32_t values = ~gpio_get_all();

	#ifdef PIN_SETTINGS
	state.aux = 0
		| ((values & (1 << PIN_SETTINGS)) ? (1 << 0) : 0)
	;
	#endif

	state.dpad = 0
		| ((values & mapDpadUp->pinMask)    ? mapDpadUp->buttonMask    : 0)
		| ((values & mapDpadDown->pinMask)  ? mapDpadDown->buttonMask  : 0)
		| ((values & mapDpadLeft->pinMask)  ? mapDpadLeft->buttonMask  : 0)
		| ((values & mapDpadRight->pinMask) ? mapDpadRight->buttonMask : 0)
	;

	state.buttons = 0;
		//| ((values & mapButtonA->pinMask)  ? mapButtonA->buttonMask  : 0)
		//;

}


void GamepadStorage::start() {
	EEPROM.start();
}

void GamepadStorage::save() {
	EEPROM.commit();
}

GamepadOptions GamepadStorage::getGamepadOptions() {
	GamepadOptions options;
	EEPROM.get(GAMEPAD_STORAGE_INDEX, options);

	uint32_t lastCRC = options.checksum;
	options.checksum = CHECKSUM_MAGIC;
	if (CRC32::calculate(&options) != lastCRC) {
		options.inputMode = InputMode::INPUT_MODE_XINPUT; // Default
		setGamepadOptions(options);
	}

	return options;
}

void GamepadStorage::setGamepadOptions(GamepadOptions options) {
	options.checksum = 0;
	options.checksum = CRC32::calculate(&options);
	EEPROM.set(GAMEPAD_STORAGE_INDEX, options);
}

