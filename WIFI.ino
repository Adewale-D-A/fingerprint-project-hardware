//CONNECT TO WIFI
// Function to connect to Wi-Fi
void connectToWiFi() {
  connectingToWifiDisplay();
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("Fingerprint", "123456789");  // password protected ap
  if (!res) {
    Serial.println("Failed to connect");
    ESP.restart();
    delay(1000);
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    deviceMode = getMode();
    while (deviceMode.toInt() < 1 || deviceMode.toInt() > 4) {
      deviceLockedDisplay();
      delay(5000);
      deviceMode = getMode();
    }

    if (deviceMode == "1") {
      registrationDisplay();
    } else if (deviceMode == "2") {
      verificationDisplay();
    } else if (deviceMode == "3") {
      deleteUserIdDisplay();
    } else if (deviceMode == "4") {
      deleteAllUsersDisplay();
    }
    delay(3000);
    // Serial.println("\nConnected to the WiFi network");
    // Serial.print("Local ESP32 IP: ");
    // Serial.println(WiFi.localIP());
  }
}
