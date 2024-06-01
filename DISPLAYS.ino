// U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/5, /* data=*/6, /* CS=*/4, /* reset=*/16);  //TODO

//DISPLAY MODE FUNCTIONS
// Function to display connecting to WIFI mode
void connectingToWifiDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("WIFI CONNECTING...");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00f7");

  u8g2.drawXBMP(46, 20, 35, 43, u8g2_Wifi_start_bits);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}

// Function to display registration mode
void registrationDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("REGISTRATION");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u0073");

  u8g2.drawXBMP(44, 20, 40, 40, epd_bitmap_file);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}
// Function to display registration mode
void registrationHeaderDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("REGISTRATION");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u0073");
  u8g2.sendBuffer();
}

// Function to display verification mode
void verificationDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("VERIFICATION");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00e5");

  u8g2.drawXBMP(38, 20, 52, 40, epd_bitmap_id__1_);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}

// Function to display registration mode
void verificationHeaderDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("VERIFICATION");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00e5");
  u8g2.sendBuffer();
}
// Function to display delete user by id mode
void deleteUserIdDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("DELETE USER");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00e5");

  u8g2.drawXBMP(44, 20, 40, 40, epd_bitmap_delete_user__1_);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}

// Function to display delete all users mode
void deleteAllUsersDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("DELETE ALL USERS");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00e4");

  u8g2.drawXBMP(45, 20, 37, 40, epd_bitmap_delete_all);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}

// Function to display delete all users mode
void deviceLockedDisplay() {
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);  //https://github.com/olikraus/u8g2/wiki/fntlistallplain#40-pixel-height
  u8g2.setCursor(10, 8);                     //0-128,0-64,
  u8g2.print("DEVICE IS LOCKED");
  u8g2.setCursor(0, 16);  //0-128,0-64,
  u8g2.print("auto retry in 5s...");

  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);  //https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_all_1x
  u8g2.setCursor(0, 8);
  u8g2.print("\u00c1");

  u8g2.drawXBMP(30, 20, 69, 40, epd_bitmap_lock);  //https://javl.github.io/image2cpp/
  u8g2.sendBuffer();
}

// Function to display registration mode
void instantMessageDisplay(String message) {
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);
  u8g2.setDrawColor(0); /* color 1 for the box */
  u8g2.drawBox(0, 10, 128, 54);
  u8g2.setCursor(0, 20);  //0-128,0-64,
  u8g2.print(message);
  u8g2.sendBuffer();
}


// Function to display registration mode
void instantMessageLine2Display(String message) {
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);
  u8g2.setDrawColor(0); /* color 1 for the box */
  u8g2.drawBox(0, 35, 128, 29);
  u8g2.setCursor(0, 30);  //0-128,0-64,
  u8g2.print(message);
  u8g2.sendBuffer();
}

// Function to display registration mode
void instantMessageLine3Display(String message) {
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);
  u8g2.setDrawColor(0); /* color 1 for the box */
  u8g2.drawBox(0, 45, 128, 19);
  u8g2.setCursor(0, 40);  //0-128,0-64,
  u8g2.print(message);
  u8g2.sendBuffer();
}

// Function to display registration mode
void instantMessageLine4Display(String message) {
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_victoriabold8_8r);
  u8g2.setDrawColor(0); /* color 1 for the box */
  u8g2.drawBox(0, 55, 128, 9);
  u8g2.setCursor(0, 50);  //0-128,0-64,
  u8g2.print(message);
  u8g2.sendBuffer();
}
