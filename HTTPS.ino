

//retrieve suggested ID for registration from the server
String getMode() {
  httpClient.begin(getModeIdApi);
  int httpResponseCode = httpClient.GET();
  String mode_id = "";
  if (httpResponseCode > 0 && httpResponseCode < 400) {
    serverResponse = httpClient.getString();
    JSONVar myObject = JSON.parse(serverResponse);
    if (JSON.typeof(myObject) == "undefined") {
      return "10";
    }
    JSONVar dataValue = myObject["data"];
    JSONVar modeId = dataValue["mode_id"];
    mode_id = JSON.stringify(modeId);
  } else {
    Serial.print("\nHTTP GET Error code: ");
    Serial.println(httpResponseCode);
    return "10";
  }

  httpClient.end();
  return mode_id;
}


//retrieve suggested ID for registration from the server
String getID() {
  httpClient.begin(getSuggestedIdApi);
  int httpResponseCode = httpClient.GET();

  String idSuggested = "";
  if (httpResponseCode > 0 && httpResponseCode < 400) {
    Serial.print("HTTP GET Response code: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.println("\nGET Response:");
    Serial.println(serverResponse);

    JSONVar myObject = JSON.parse(serverResponse);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing response failed!");
      return "N/A";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar suggestedId = dataValue["suggested_id"];
    idSuggested = JSON.stringify(suggestedId);
  } else {
    Serial.print("\nHTTP GET Error code: ");
    Serial.println(httpResponseCode);
    return "N/A";
  }

  httpClient.end();
  return idSuggested;
}

//inform server of the registered ID
int postRegisteredId(String registerdId) {
  httpClient.begin(postRegisteredIdApi);
  httpClient.addHeader("Content-Type", "application/json");

  String payload = "{\"userId\":\"" + registerdId + "\"}";
  int httpResponseCode = httpClient.POST(payload);

  if (httpResponseCode > 0 && httpResponseCode < 400) {
    Serial.print("\nHTTP POST Response code: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.print("\nHTTP POST Response: ");
    Serial.println(serverResponse);
    return 1;
  } else {
    Serial.print("\nHTTP POST Error code: ");
    Serial.println(httpResponseCode);
    return 0;
  }

  httpClient.end();
}


//inform server of the verified ID and server returns matric number of verified user
String postVerifiedId(String verifiedId) {
  httpClient.begin(postVerifiedIdApi);
  httpClient.addHeader("Content-Type", "application/json");
  String MatNo = "";
  String payload = "{\"userId\":\"" + verifiedId + "\"}";
  int httpResponseCode = httpClient.POST(payload);

  if (httpResponseCode > 0 && httpResponseCode < 400) {
    Serial.print("\nHTTP POST Response code: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.print("\nHTTP POST Response: ");
    Serial.println(serverResponse);    
    JSONVar myObject = JSON.parse(serverResponse);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing response failed!");
      return "N/A";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar matricNo = dataValue["student_data"]["matric_no"];
    MatNo = JSON.stringify(matricNo);
    return MatNo;
  } else {
    Serial.print("\nHTTP POST Error code: ");
    Serial.println(httpResponseCode);
    return "N/A";
  }

  httpClient.end();
}

