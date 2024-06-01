
void greenLED() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 128, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
    //delay(500);
  }
}

void redLED() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
    //delay(500);
  }
}


void yellowLED() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
    //delay(500);
  }
}
