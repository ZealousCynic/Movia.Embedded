void read_rfid() {
  
  if(!mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("Failed to read MIFARE serial.");
    return;
  }
  Serial.println("Reading MIFARE card");
  
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockaddress, &key, &(mfrc522.uid));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockaddress, mf_buffer, &mf_buf_size);

  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  for(int i = 0; i < 5; i++) {
    charbuf[i] = (char)mf_buffer[i];
  } 
  
  wifiMFRCRoutine(charbuf);
}
