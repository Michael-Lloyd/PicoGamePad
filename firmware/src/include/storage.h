#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdint.h>
#include "NeoPico.hpp"
#include "enums.h"

#define GAMEPAD_STORAGE_INDEX      0 // 1024 bytes for gamepad options
#define BOARD_STORAGE_INDEX     1024 //  512 bytes for hardware options
#define LED_STORAGE_INDEX       1536 //  512 bytes for LED configuration

struct BoardOptions {
	bool hasBoardOptions;
	uint8_t pinDpadUp;
	uint8_t pinDpadDown;
	uint8_t pinDpadLeft;
	uint8_t pinDpadRight;
	ButtonLayout buttonLayout;
	uint32_t checksum;
};

struct LEDOptions {
	bool useUserDefinedLEDs;
	int dataPin;
	LEDFormat ledFormat;
	ButtonLayout ledLayout;
	uint8_t ledsPerButton;
	uint8_t brightnessMaximum;
	uint8_t brightnessSteps;
	int indexUp;
	int indexDown;
	int indexLeft;
	int indexRight;
};

BoardOptions getBoardOptions();
void setBoardOptions(BoardOptions options);

LEDOptions getLEDOptions();
void setLEDOptions(LEDOptions options);

#endif
