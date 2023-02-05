#include <Keypad.h>
#include "keypad_interactor.h"
// This is currently not used, due to space constraints in the breadboard.
// Uncomment this section of the code to implement a button matrix.
//
// const int ROW_NUM = 3; // amount of rows
// const int COL_NUM = 3; // amount of columns

// char keys[ROW_NUM][COL_NUM] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // key values
// byte pin_rows[ROW_NUM] = {19, 18, 23}; // pins for row connection
// byte pin_cols[COL_NUM] = {5, 17, 15}; // pins for column connection
// Keypad keypad = Keypad(
//     makeKeymap(keys),
//     pin_rows,
//     pin_cols,
//     ROW_NUM,
//     COL_NUM
// );

// int captureButtonPress() {
//     char key = keypad.getKey();
// 	if (key){
// 		Serial.print("KEY: ");
// 		Serial.println(int(key));
// 		return int(key);
// 	}
// 	return 0;
// }
int remoteButtonState;
int lastRemoteButtonState;
bool isPressed = false;
const int REMOTE_BUTTON_PIN= 5;

void setupRemoteButton() {
	pinMode(REMOTE_BUTTON_PIN, INPUT_PULLDOWN);
	remoteButtonState = digitalRead(REMOTE_BUTTON_PIN);	
}

int captureSingleButtonPress() {
  lastRemoteButtonState = remoteButtonState;
  remoteButtonState = digitalRead(REMOTE_BUTTON_PIN);

  if (remoteButtonState == HIGH && lastRemoteButtonState == LOW) {
		Serial.println("Changed state");
    isPressed = !isPressed;
  }

	if (isPressed) {
		Serial.println("PRESSED");
		isPressed = false;
		return 1;
	}
	return 0;
}