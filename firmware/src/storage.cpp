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

#include "storagemanager.h"

#include "BoardConfig.h"
#include <GamepadStorage.h>
#include "FlashPROM.h"
#include "hardware/watchdog.h"
#include "CRC32.h"
#include <sstream>

#include "addons/ws2812b.h"

#include "helper.h"

/* Board stuffs */
void Storage::initBoardOptions() {
	EEPROM.get(BOARD_STORAGE_INDEX, boardOptions);
	uint32_t lastCRC = boardOptions.checksum;
	boardOptions.checksum = CHECKSUM_MAGIC;
	if (lastCRC != CRC32::calculate(&boardOptions)) {
		setDefaultBoardOptions();
	}
}

BoardOptions Storage::getBoardOptions() {
	return boardOptions;
}

void Storage::setDefaultBoardOptions() {
	boardOptions.hasBoardOptions   = false;
	boardOptions.pinDpadUp         = PIN_DPAD_UP;
	boardOptions.pinDpadDown       = PIN_DPAD_DOWN;
	boardOptions.pinDpadLeft       = PIN_DPAD_LEFT;
	boardOptions.pinDpadRight      = PIN_DPAD_RIGHT;
	strncpy(boardOptions.boardVersion, PICOGAMEPAD_VERSION, strlen(PICOGAMEPAD_VERSION));
	setBoardOptions(boardOptions);
}

void Storage::setBoardOptions(BoardOptions options) {

	if (memcmp(&options, &boardOptions, sizeof(BoardOptions)) != 0) {
		options.checksum = CHECKSUM_MAGIC; // set checksum to magic number
		options.checksum = CRC32::calculate(&options);
		EEPROM.set(BOARD_STORAGE_INDEX, options);
		EEPROM.commit();
		memcpy(&boardOptions, &options, sizeof(BoardOptions));
	}
}

/* LED stuffs */
void Storage::initLEDOptions() {
	EEPROM.get(LED_STORAGE_INDEX, ledOptions);
	uint32_t lastCRC = ledOptions.checksum;
	ledOptions.checksum = CHECKSUM_MAGIC;
	if (lastCRC != CRC32::calculate(&ledOptions)) {
		setDefaultLEDOptions();
	}
}

LEDOptions Storage::getLEDOptions() {
	return ledOptions;
}

void Storage::setDefaultLEDOptions() {
	ledOptions.dataPin = BOARD_LEDS_PIN;
	ledOptions.ledFormat = LED_FORMAT;
	ledOptions.ledLayout = BUTTON_LAYOUT;
	ledOptions.ledsPerButton = LEDS_PER_PIXEL;
	ledOptions.brightnessMaximum = LED_BRIGHTNESS_MAXIMUM;
	ledOptions.brightnessSteps = LED_BRIGHTNESS_STEPS;
	ledOptions.indexUp = LEDS_DPAD_UP;
	ledOptions.indexDown = LEDS_DPAD_DOWN;
	ledOptions.indexLeft = LEDS_DPAD_LEFT;
	ledOptions.indexRight = LEDS_DPAD_RIGHT;
	setLEDOptions(ledOptions);
}

void Storage::setLEDOptions(LEDOptions options) {
	if (memcmp(&options, &ledOptions, sizeof(LEDOptions)) != 0) {
		options.checksum = CHECKSUM_MAGIC; // set checksum to magic number
		options.checksum = CRC32::calculate(&options);
		EEPROM.set(LED_STORAGE_INDEX, options);
		EEPROM.commit();
		memcpy(&ledOptions, &options, sizeof(LEDOptions));
	}
}

void Storage::ResetSettings() {
	EEPROM.reset();
	watchdog_reboot(0, SRAM_END, 2000);
}

void Storage::SetConfigMode(bool mode) { // hack for config mode
	CONFIG_MODE = mode;
}

bool Storage::GetConfigMode() {
	return CONFIG_MODE;
}

void Storage::SetGamepad(Gamepad * newpad) {
	gamepad = newpad;
}

Gamepad * Storage::GetGamepad() {
	return gamepad;
}

void Storage::SetProcessedGamepad(Gamepad * newpad) {
	processedGamepad = newpad;
}

Gamepad * Storage::GetProcessedGamepad() {
	return processedGamepad;
}

