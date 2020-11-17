void getGPSReading() {
  
  while(Serial1.available()) {
    if(gps.encode(Serial1.read())) {
      gps.f_get_position(&lat, &lon);      
    }
  }

  Serial.println(wifiGPSRoutine(lat, lon));
}
