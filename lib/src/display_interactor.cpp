#include "display_interactor.h"

#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void startScreen() {
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
		Serial.println("SSD1306 allocation failed");
		for(;;);
	}
    
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("OPENREMOTE");
  display.display();
}

void displayText(char text[]) {
  display.clearDisplay();
  display.print(text);
  display.display();
}

void displayClear() {
  display.clearDisplay();
}