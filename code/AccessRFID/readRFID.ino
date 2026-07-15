void readDataRFID()
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    getData = true;
//    digitalWrite(buzz, LOW);
    if ( errorRFID )
    {
      mfrc522.PCD_Init ();
      errorRFID = false;
    }
    rfid = false;
    UID = "";
    return;
  }

  while (mfrc522.PICC_ReadCardSerial())
  {
    rfid = true;
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    byte block;
    byte len;
    MFRC522::StatusCode status;
    byte buffer2[50];
    block = 1;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      Serial.println("Failed, dan  kayaknya butuh restart deh ");
      return;
    }
    status = mfrc522.MIFARE_Read(block, buffer2, &len);
    if (status != MFRC522::STATUS_OK) {
      for (uint8_t i = 0; i < 16; i++) {
       Serial.write(buffer2[i] );
      char buff = char(buffer2[i]);
    }

      Serial.print(F("Reading failed: "));
      Serial.println(sizeof(buffer2));
      Serial.println(mfrc522.GetStatusCodeName(status));
      Serial.println("Error need to restart");
      errorRFID = true;
      return;
    }
    for (uint8_t i = 0; i < 16; i++) {
      // Serial.write(buffer2[i] );
      char buff = char(buffer2[i]);
    }

    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message :-------");
    content.toUpperCase();
    content = content.substring(1, 12);
    Serial.print(content);
    Serial.println("-------");
    UID = content;
    mfrc522.PICC_HaltA(); // menghentikan pembacaan
    mfrc522.PCD_StopCrypto1();

  }
  //  return ID_Nrp;
}
