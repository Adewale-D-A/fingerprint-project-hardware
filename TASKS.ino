// Function to handle button press interrupt
void buttonInterrupt() {
  // Read the state of the button
  int buttonState = digitalRead(BUTTON_PIN);
  // Check if the button state has changed
  if (buttonState == LOW) {
    isButtonPressed = true;
  }
}



// Function to display enrollment page
void displayRegistrationPage() {
  registrationHeaderDisplay();
  greenLED();

  isButtonPressed = false;
  Serial.println("Ready to enroll a fingerprint!");  //TODO: Print information to screen
  instantMessageDisplay("Ready to enroll");
  receivedId = getID();
  id = receivedId.toInt();  //readnumber();
  if (id == 0) {
    return;
  }
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        greenLED();
        instantMessageDisplay("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println("No finger detected");

        yellowLED();
        instantMessageDisplay("No finger");
        instantMessageLine2Display("detected");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        redLED();
        instantMessageDisplay("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        redLED();
        instantMessageDisplay("Communication error");
        break;
      default:
        Serial.println("Unknown error");
        redLED();
        instantMessageDisplay("Unknown error");
        break;
    }
  }

  //CAPTURE IMAGE ONCE LOOP
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      greenLED();
      instantMessageDisplay("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
    case FINGERPRINT_PACKETRECIEVEERR:
    case FINGERPRINT_FEATUREFAIL:
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      redLED();
      instantMessageDisplay("Could not find");
      instantMessageLine2Display("fingerprint features");
      return;
    default:
      Serial.println("Unknown error");
      redLED();
      instantMessageDisplay("Unknown error");
      return;
  }

  Serial.println("Remove finger");  //TODO: Print information to screen
  instantMessageDisplay("Remove finger");
  yellowLED();
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();  //makes the variable 'p' equals to a zero
  }

  p = -1;
  Serial.println("Place same finger again");  //TODO: Print information to screen
  yellowLED();
  instantMessageDisplay("Place same");
  instantMessageLine2Display("finger again");

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        greenLED();
        instantMessageDisplay("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        // instantMessageDisplay("Image taken");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        redLED();
        instantMessageDisplay("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        redLED();
        instantMessageDisplay("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        redLED();
        instantMessageDisplay("Unknown error");
        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      instantMessageDisplay("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
    case FINGERPRINT_PACKETRECIEVEERR:
    case FINGERPRINT_FEATUREFAIL:
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      instantMessageDisplay("Could not find");
      instantMessageLine2Display("fingerprint features");
      return;
    default:
      Serial.println("Unknown error");
      instantMessageDisplay("Unknown error");
      return;
  }

  Serial.print("Creating model for #");
  Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    greenLED();
    instantMessageDisplay("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    redLED();
    instantMessageDisplay("Communication error");
    return;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match, please restart user's registration");  //TODO: Print information to screen

    redLED();
    instantMessageDisplay("Fingerprints did");
    instantMessageLine2Display("not match, please");
    instantMessageLine3Display("restart registration");
    delay(2000);
    return;
  } else {
    Serial.println("Unknown error");
    redLED();
    instantMessageDisplay("Unknown error");
    return;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    regId = String(id);
    registeredIdPostResponse = postRegisteredId(regId);  //can either be a 1 or 0
    Serial.println("\nUser with ID");
    greenLED();
    instantMessageDisplay("User with ID");
    instantMessageLine2Display(regId);
    instantMessageLine3Display("Stored!");
    Serial.println(id);
    Serial.println("Stored!");  //TODO: Print ID to screen, then wait for a button click to register another user
    delay(2000);
    while (!isButtonPressed) {
      Serial.println("Click button to register another user");  //TODO: Print ID to screen

      yellowLED();
      instantMessageDisplay("Click button to");
      instantMessageLine2Display("register another ");
      instantMessageLine3Display("user");
      buttonInterrupt();
    }
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    redLED();
    instantMessageDisplay("Communication error");
    return;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    redLED();
    instantMessageDisplay("Could not store");
    instantMessageLine2Display("in that location");
    return;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    redLED();
    instantMessageDisplay("Error writing");
    instantMessageLine2Display("to flash");
    return;
  } else {
    Serial.println("Unknown error");
    redLED();
    instantMessageDisplay("Unknown error");
    return;
  }

  //delay(500); // Add a delay to avoid continuous enrollment attempts
}


// Function to display attendance marking page
void displayVerificationPage() {
  verificationHeaderDisplay();
  greenLED();

  isButtonPressed = false;
  uint8_t p = finger.getImage();

  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      greenLED();
      instantMessageDisplay("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      instantMessageDisplay("No finger");
      yellowLED();
      instantMessageLine2Display("detected");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      redLED();
      instantMessageDisplay("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      redLED();
      instantMessageDisplay("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      redLED();
      instantMessageDisplay("Unknown error");
      break;
  }

  if (p == FINGERPRINT_OK) {
    p = finger.image2Tz();

    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        greenLED();
        instantMessageDisplay("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        redLED();
        instantMessageDisplay("Image too messy");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        redLED();
        instantMessageDisplay("Communication error");
        break;
      case FINGERPRINT_FEATUREFAIL:
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        redLED();
        instantMessageDisplay("Could not find");
        instantMessageLine2Display("fingerprint features");
        break;
      default:
        Serial.println("Unknown error");
        redLED();
        instantMessageDisplay("Unknown error");
        break;
    }

    if (p == FINGERPRINT_OK) {
      p = finger.fingerSearch();

      if (p == FINGERPRINT_OK) {
        greenLED();

        fingerprintVerifiedId = String(finger.fingerID);
        matricNumber = postVerifiedId(fingerprintVerifiedId);

        instantMessageDisplay(matricNumber);
        instantMessageLine2Display("Verified!");
        // instantMessageLine3Display(String(finger.confidence));

        Serial.println("\nDone verifying user, wait 5 seconds to verify another user");
        delay(2000);
        while (!isButtonPressed) {
          Serial.println("Click button to register another user");  //TODO: Print ID to screen
          instantMessageLine3Display("Click to verify");
          instantMessageLine4Display("another user ");
          yellowLED();
          buttonInterrupt();
        }
      } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        instantMessageDisplay("Communication error");
        redLED();
      } else if (p == FINGERPRINT_NOTFOUND) {
        instantMessageDisplay("Fingerprints did");
        instantMessageLine2Display("not match");
        redLED();
        delay(2000);
      } else {
        Serial.println("Unknown error");
        redLED();
        instantMessageDisplay("Unknown error");
      }
    }
  }
}