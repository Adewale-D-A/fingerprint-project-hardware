

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
      return "0";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar suggestedId = dataValue["suggested_id"];
    idSuggested = JSON.stringify(suggestedId);
  } else {
    Serial.print("\nHTTP GET Error code: ");
    Serial.println(httpResponseCode);
    return "0";
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
    deleteFingerprint(registerdId.toInt());
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


//retrieve deletable ID from server
String getDeletableID() {
  httpClient.begin(getDeletableIdApi);
  int httpResponseCode = httpClient.GET();

  String deleteableId = "0";
  if (httpResponseCode > 0 && httpResponseCode < 400) {
    Serial.print("HTTP GET Response code: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.println("\nGET Response:");
    Serial.println(serverResponse);

    JSONVar myObject = JSON.parse(serverResponse);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing response failed!");
      return "0";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar receivedIdResponse = dataValue["student_data"]["user_id"];
    deleteableId = JSON.stringify(receivedIdResponse);
  } else {
    Serial.print("\nHTTP GET Error code: ");
    Serial.println(httpResponseCode);
  }

  httpClient.end();
  return deleteableId;
}


//inform server of the deleted ID
String postRemoveId(String deletableId) {
  httpClient.begin(postDeletedIdToServerApi);
  httpClient.addHeader("Content-Type", "application/json");
  String matNo = "";
  String payload = "{\"userId\":\"" + deletableId + "\"}";
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
      return "";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar matricNo = dataValue["student_data"]["matric_no"];
    matNo = JSON.stringify(matricNo);
    return matNo;
  } else {
    Serial.print("\nHTTP POST Error code: ");
    Serial.println(httpResponseCode);
    return "";
  }

  httpClient.end();
}



//get permission to delete all stored data on device
String getSystemPurgePermission() {
  httpClient.begin(getDeletePermissionApi);
  httpClient.addHeader("Content-Type", "application/json");

  String purgeReply = "";
  int httpResponseCode = httpClient.GET();

  if (httpResponseCode > 0 && httpResponseCode < 401) {
    Serial.print("\nStatus coDe response is: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.print("\nDelete permission response gotten from the server is: ");
    Serial.println(serverResponse);
    JSONVar myObject = JSON.parse(serverResponse);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing response failed!");
      return "0";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar reply = dataValue["reply"];
    purgeReply = JSON.stringify(reply);
    return purgeReply;
  } else {
    Serial.print("\nHTTP GET Error code for delete permission: ");
    Serial.println(httpResponseCode);
  }

  httpClient.end();
  return purgeReply;
}

//inform server that hardware's registered data has been purged/clear, so server can
//clear its own registered data too
String postSystemPurgeUpdate(String systemResponse) {
  httpClient.begin(postRecordDeletionApi);
  httpClient.addHeader("Content-Type", "application/json");

  String serverReply = "";
  String payload = "{\"reply\":\"" + systemResponse + "\"}";
  int httpResponseCode = httpClient.POST(payload);

  if (httpResponseCode > 0 && httpResponseCode < 401) {
    Serial.print("\nStatus code response is: ");
    Serial.println(httpResponseCode);
    serverResponse = httpClient.getString();
    Serial.print("\nResponse from informing the server is: ");
    Serial.println(serverResponse);
    JSONVar myObject = JSON.parse(serverResponse);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing response failed!");
      return "";
    }

    JSONVar dataValue = myObject["data"];
    JSONVar reply = dataValue["reply"];
    serverReply = JSON.stringify(reply);
  } else {
    Serial.print("\nHTTP POST for Delete Update Error code: ");
    Serial.println(httpResponseCode);
  }

  httpClient.end();
  return serverReply;
}
