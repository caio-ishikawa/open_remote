#ifndef STATE_HANDLER_HPP
#define STATE_HANDLER_HPP

const int PWM_CHANNEL = 0;
const int GLOBAL_BUTTON_PIN = 15;

void setupInitialState();
void startPairingMode(); 
void startRemoteMode();
void handleGlobalState();

#endif