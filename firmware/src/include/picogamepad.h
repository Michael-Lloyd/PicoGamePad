#ifndef PICOGAMEPAD_H_
#define PICOGAMEPAD_H_

#include <stdint.h>
#include <string>
#include "pico/stdlib.h"
#include "gamepad.h"

using namespace std;

const string BUTTON_LABEL_UP = "Up";
const string BUTTON_LABEL_DOWN = "Down";
const string BUTTON_LABEL_LEFT = "Left";
const string BUTTON_LABEL_RIGHT = "Right";

class GPModule {
public:
	virtual void setup() = 0;
	virtual void loop() = 0;
	virtual void process(Gamepad *gamepad) = 0;
	absolute_time_t nextRunTime;
	const uint32_t intervalMS = 10;
	inline bool isEnabled() { return enabled; }
protected:
	bool enabled = true;
};

#endif
