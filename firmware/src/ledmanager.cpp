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



#include "PicoGamePad.h"
#include "themes.h"

#include "enums.h"
#include "helper.h"

static std::vector<uint8_t> EMPTY_VECTOR;

uint32_t rgbPLEDValues[4];

bool LEDManager::available() {
	LEDOptions ledOptions = Storage::getInstance().getLEDOptions();
	return ledOptions.dataPin != -1;
}

void LEDManager::setup() {
	// Set Default LED Options
	LEDOptions ledOptions = Storage::getInstance().getLEDOptions();
	if (!ledOptions.useUserDefinedLEDs) {
		Storage::getInstance().setDefaultLEDOptions();
	}

	deviceled = nullptr; // set deviceled to null

	deviceled = new deviceled(-1, 0);
	configureLEDs();

	nextRunTime = make_timeout_time_ms(0); // Reset timeout
}

void LEDManager::process() {

	LEDOptions ledOptions = Storage::getInstance().getLEDOptions();
	if (ledOptions.dataPin < 0 || !time_reached(this->nextRunTime))
		return;

	Gamepad * gamepad = Storage::getInstance().GetProcessedGamepad();
	uint8_t * featureData = Storage::getInstance().GetFeatureData();


	if ( action != HOTKEY_LEDS_NONE ) {
		as.HandleEvent(action);
	}

	uint32_t buttonState = gamepad->state.dpad << 16 | gamepad->state.buttons;

	if (pressed.size() > 0)
		as.HandlePressed(pressed);
	else
		as.ClearPressed();

	as.Animate();
	as.ApplyBrightness(frame);


	deviceled->Show();

	this->nextRunTime = make_timeout_time_ms(LEDManager::intervalMS);

}

uint8_t LEDManager::setupButtonPositions() {

	LEDOptions ledOptions = Storage::getInstance().getLEDOptions();
	buttonPositions.clear();
	buttonPositions.emplace(BUTTON_LABEL_UP, ledOptions.indexUp);
	buttonPositions.emplace(BUTTON_LABEL_DOWN, ledOptions.indexDown);
	buttonPositions.emplace(BUTTON_LABEL_LEFT, ledOptions.indexLeft);
	buttonPositions.emplace(BUTTON_LABEL_RIGHT, ledOptions.indexRight);

	uint8_t buttonCount = 0;
	for (auto const buttonPosition : buttonPositions) {
		if (buttonPosition.second != -1)
			buttonCount++;
	}

	return buttonCount;
}

void LEDManager::configureLEDs() {

	LEDOptions ledOptions = Storage::getInstance().getLEDOptions();
	uint8_t buttonCount = setupButtonPositions();
	vector<vector<Pixel>> pixels = createLEDLayout(ledOptions.ledLayout, ledOptions.ledsPerButton, buttonCount);
	ledCount = matrix.getLedCount();

	// Remove the old deviceled (config can call this)
	delete deviceled;
	deviceled = new deviceled(ledOptions.dataPin, ledCount, ledOptions.ledFormat);
	deviceled->Off();

	as.ConfigureBrightness(ledOptions.brightnessMaximum, ledOptions.brightnessSteps);
	addStaticThemes(ledOptions);
}


