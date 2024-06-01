#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <math.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include "IMAGES.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

// Define pin constants
#define RXD1 18
#define TXD1 17

// Define pin for the button
#define BUTTON_PIN 8

#define PSU_PIN 9
#define NEOPIXEL_PIN 48
#define NUMPIXELS 1
#define BRIGHTNESS 50

// WiFiClient wifiClient;
HTTPClient httpClient;

//Your Domain name with URL path or IP address with path
String baseUrl = "https://fingerprint-project.azurewebsites.net";
String routeBaseUrl = "/hardware";
String postRegisteredIdApi = baseUrl + routeBaseUrl + "/registered-id";                   //inform the server the ID that was registered on fingerprint device
String getSuggestedIdApi = baseUrl + routeBaseUrl + "/suggested-id";                      //get server to suggest ID to use in registering a user
String postVerifiedIdApi = baseUrl + routeBaseUrl + "/verify-user";                       //inform server on the ID that was just verified
String getDeletePermissionApi = baseUrl + routeBaseUrl + "/should_i_delete_all_records";  //get a response from the server either a 1 or 0 to know if to delete all records
String postRecordDeletionApi = baseUrl + routeBaseUrl + "/have_i_deleted_all_records";    //inform server that records have been clear on the hardware device
String getDeletableIdApi = baseUrl + routeBaseUrl + "/id-to-delete";                      //get ID that should be deleted from the server
String postDeletedIdToServerApi = baseUrl + routeBaseUrl + "/remove-id-from-server";      //inform server to remove deleted hardware from server's users database
String getModeIdApi = baseUrl + routeBaseUrl + "/mode";                                   //get server to suggest ID to use in registering a user


String serverResponse;         //general string server response
String receivedId;             //suggested ID variable
String regId;                  //registered ID variable
String fingerprintVerifiedId;  //verified ID variable
String matricNumber;           //retrived verified user's matric number
String systemPurgeReply;       //response from server to either purge/delete all stored hardware data or NOT - either a "1" or "0" reply
String systemPurgeStatus;      //Once hardware data has been cleared, value is update to carry that state - either a "1" or "0" reply
String serverPurgedStatus;     //get server purge/delete status - either a "1" or "0"
String deletableIdResponse;    //get id from server that should be deleted
String removeIdFromServer;     //removable ID from server

unsigned int id;
String clearFingerprintData = "0";    //variable to set server data purge response
String deletFingerprintIdData = "0";  //variable to exit while delete loop
int registeredIdPostResponse;         //on server registering an ID, return a 1 or 0 if registration is successful
bool wifiConnected = false;           //check status of WIFI connection
String deviceMode = "8";
volatile bool isButtonPressed = false;  // button state


// Define fingerprint sensor and display objects
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/5, /* data=*/6, /* CS=*/4, /* reset=*/16);


void setup() {
  // put your setup code here, to run once:
  // Initialize serial communication
  Serial.begin(57600);
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);  //fingerprint monitor


  // Initialize peripherals
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PSU_PIN, OUTPUT);
  digitalWrite(PSU_PIN, LOW);

  // Initialize display
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  // Attach buttonInterrupt() function to the interrupt vector for the button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, CHANGE);
  // Initialize fingerprint sensor
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Did not find fingerprint sensor :(");
    while (true) { delay(1); }
  }
  finger.getParameters();
  finger.getTemplateCount();


  connectToWiFi();
}

void loop() {
  if (deviceMode == "1") {
    // Function to display enrollment page
    displayRegistrationPage();
  } else if (deviceMode == "2") {
    displayVerificationPage();
  } else if (deviceMode == "3") {
    deleteUserIdDisplay();
  } else if (deviceMode == "4") {
    deleteAllUsersDisplay();
  }
}
