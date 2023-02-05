#ifndef DISPLAY_INTERACTOR_H
#define DISPLAY_INTERACTOR_H

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 
#define OLED_RESET    -1

void startScreen();
void displayText(char text[]); 
void displayClear();

#endif