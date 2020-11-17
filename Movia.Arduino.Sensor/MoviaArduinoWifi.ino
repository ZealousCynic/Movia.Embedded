
String IpAddress2String(const IPAddress& ipAddress) {
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3]) ;
}

void wifiConnect() {

  while (wifiStatus != WL_CONNECTED) {
    Serial.print("Attempting to connecto to: ");
    Serial.println(ssid);
    wifiStatus = WiFi.begin(ssid, password);
  }

  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(IpAddress2String(ip));
}

bool wifiHCSR04Routine(char *request) {
  if (wifiStatus == WL_CONNECTED) {
    
    char buf[50];

     for(int i = 0; i < 50; i++) {
      snprintf(buf, 50, "PUT /passenger/%s HTTP/1.1", request);
     }

    return sendHttpPut(buf);
  }
  else {
    Serial.println("ERROR, NOT CONNECTED");    
  }
  return false;
}

bool checkIsHTTPStatusOK(WiFiClient& client) {
  unsigned long current = millis();

  char data = 0;

  while (data != ' ') { // <--- Check for space character
    if (client.available() > 0) {
      data = client.read();
    }

    if (millis() - current > timeout) {
      Serial.println("\r\nERROR:\t Client Timeout, first");
      return false;
    }

    yield();
  }

  while (client.available() < 3) {
    if (millis() - current > timeout) {
      Serial.println("\r\nERROR:\tClient Timeout, second");
      return false;
    }
    yield();
  }

  char HTTPStatus[4]; // 3 digits + null terminator
  client.read((uint8_t*) HTTPStatus, 3);
  HTTPStatus[3] = '\0';

  if (strcmp(HTTPStatus, "200") != 0) {
    Serial.print("\r\nERROR:\tHTTP Status ");
    Serial.println(HTTPStatus);
    return false;
  }

  return true;
}


bool sendHttpPut(char* request) {

  WiFiClient client;
  if (!client.connect(HOST, 8080)) {
    Serial.println("\r\nERROR, NOT HTTPERROR CODE:\t Connection Failed.");
    return false;
  }

  client.println(request);
  client.println("Host: 192.168.10.1");
  client.println("Content-Type: plain/text");
  client.println("Connection: keep-alive");
  client.println("Content-length: 0");
  client.println();

  client.flush();

  bool isHTTPStatusOK = checkIsHTTPStatusOK(client);

  client.stop();

  return isHTTPStatusOK;
}
