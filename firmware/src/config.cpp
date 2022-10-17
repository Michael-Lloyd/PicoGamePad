
#include "configmanager.h"
#include "configs/webconfig.h"
#include "addons/ws2812b.h"

void ConfigManager::setup(ConfigType config) {
	switch(config) {
		case CONFIG_TYPE_WEB:
			setupConfig(new WebConfig());
			break;
	}
	this->cType = config;
}

void ConfigManager::loop() {
	config->loop();
}

void ConfigManager::setupConfig(GPConfig * gpconfig) {
	gpconfig->setup();
	this->config = gpconfig;
}

void ConfigManager::setGamepadOptions(Gamepad* gamepad) {
	gamepad->save();
}

void ConfigManager::setLedOptions(LEDOptions ledOptions) {
	Storage::getInstance().setLEDOptions(ledOptions);

	// Configure LED
	for (std::vector<GPAddon*>::iterator it = Storage::getInstance().Addons.begin(); it != Storage::getInstance().Addons.end(); it++) {
		if ((*it)->name() == NeoPicoLEDName) {
			//NeoPicoLEDAddon * neopicoled = (NeoPicoLEDAddon*)(*it);
			//neopicoled->configureLEDs();
			break; 
		}
	} 
}

void ConfigManager::setBoardOptions(BoardOptions boardOptions) {
	Storage::getInstance().setBoardOptions(boardOptions);

	Gamepad * gamepad = Storage::getInstance().GetGamepad();
	gamepad->mapDpadUp->setPin(boardOptions.pinDpadUp);
	gamepad->mapDpadDown->setPin(boardOptions.pinDpadDown);
	gamepad->mapDpadLeft->setPin(boardOptions.pinDpadLeft);
	gamepad->mapDpadRight->setPin(boardOptions.pinDpadRight);
	//gamepad->mapButtonA->setPin(boardOptions.pinButtonA);


	GamepadStore.save();
}
