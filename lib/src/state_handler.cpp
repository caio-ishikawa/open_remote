#include "state_handler.h"
#include "display_interactor.h"
#include "keypad_interactor.h"
#include <IRremote.h>
#include <Arduino.h>
#include <string>
#include <array>
#include <map>
#include <vector>

int buttonState;
int lastButtonState;
bool isRemoteMode = true;
byte IR_EMITTER_PIN = 4;
// std::array<uint32_t, 67> irCode = {9050, 4450, 600, 500, 600, 550, 600, 1600, 600, 550, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1600, 650, 1600, 600, 1650, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1650, 600, 1650, 600, 1600, 650, 500, 600, 1650, 600, 1600, 600, 1650, 600, 1650, 600};
std::map<std::string, std::vector<uint32_t>> buttonMappings;

void setupInitialState() {
  startScreen();

  //global state button setup
  pinMode(GLOBAL_BUTTON_PIN, INPUT_PULLUP);
  buttonState = digitalRead(GLOBAL_BUTTON_PIN);

  //remote button setup
  setupRemoteButton();

  //receiver setup
  IrReceiver.begin(18, ENABLE_LED_FEEDBACK);

  delay(2000);
}

void handleGlobalState() {
  lastButtonState = buttonState;
  buttonState = digitalRead(GLOBAL_BUTTON_PIN);

  if (buttonState == HIGH && lastButtonState == LOW) {
    isRemoteMode = !isRemoteMode;
  }

  if (isRemoteMode) {
    startRemoteMode();
  } else {
    startPairingMode();
  }
}


void startPairingMode() {
  if (!IrReceiver.decode()) {
    Serial.println("Waiting for IR");
    return;
  }

  IrReceiver.printIRResultRawFormatted(&Serial);
  uint32_t rawIrCode[67];
  std::vector<uint32_t> irCode;

  //todo: figure out why pushing uint32_t directly to vector results in only 10s
  for (int i = 1; i < IrReceiver.decodedIRData.rawDataPtr->rawlen; i++) {
    auto tCurrentTicks = IrReceiver.decodedIRData.rawDataPtr->rawbuf[i];
		rawIrCode[i] = (uint32_t) tCurrentTicks * MICROS_PER_TICK, DEC;
		irCode.push_back(rawIrCode[i]);
  }

  int pressedKey = captureSingleButtonPress();
	if (pressedKey == 0) {
		Serial.println("waiting for key");
		return;
	}

	for (uint32_t i: irCode) {
		Serial.print(i);
		Serial.print(", ");
	}

	std::string pressedStr = std::to_string(pressedKey);
	buttonMappings[pressedStr] = irCode;

	IrReceiver.resume();
}

void startRemoteMode() {
	pinMode(IR_EMITTER_PIN, OUTPUT);
	digitalWrite(IR_EMITTER_PIN, LOW);
	ledcSetup(PWM_CHANNEL, 38000, 8);
	ledcAttachPin(IR_EMITTER_PIN, PWM_CHANNEL);

  int keyPress = captureSingleButtonPress();
  if (keyPress == 0) {
    Serial.println("Waiting for keypress");
  }
	Serial.println("\n");
	Serial.println(keyPress);
	std::string pressedStr = std::to_string(keyPress);
	std::vector<uint32_t> irCode = buttonMappings[pressedStr];

	// Loops over irCode data and triggers PWM pin with a delay corresponding to
	// the current value of irCode array
	for (auto i = irCode.begin(); i != irCode.end(); ++i) {
		int index = std::distance(irCode.begin(), i);
		Serial.println(irCode[index]);
		if (index % 2 == 0) {
			ledcWrite(PWM_CHANNEL, 125);
			delayMicroseconds(irCode[index]);
		} else {
			ledcWrite(PWM_CHANNEL, 0);
			delayMicroseconds(irCode[index]);
		}
	}

	ledcWrite(PWM_CHANNEL, 0);
}

