void checkData(String dir, String uid)
{
  String tUID, tNAMA, tLANTAI;
  bool cek = false;
  int mulai = millis();
  if (!SD.begin(SD_PIN))
  {
    Serial.println("initialization failed!");
    return;
  }
  File myFile;
  myFile = SD.open(dir);
  if (myFile)
  {
    //    Serial.println(dir);
    //    Serial.print("mulai = "); Serial.println(mulai);
    int a;
    unsigned int timeOUT = millis();

    while (myFile.available())// && millis() - timeOUT >= 2000)
    {
      //      timeOUT = millis();
      String file = myFile.readStringUntil('\n');
      String out[10];
      //      Serial.println(file);
      //      file+="|";
      parsing(out, file);
      out[1].trim();
      if (out[1] == uid)
      {
        cek = true;
        String datatoArd;
        for ( int i = 4 ; i <= 8; i++)
        {
          datatoArd += "|";
          datatoArd += out[i];
        }
        datatoArd += "|\r";
        delay(10);
        Serial.println(datatoArd);
        if ( rfid)
        {
          ard.print(datatoArd);
        }
        Data = true;
        String L0, L1, L2, L3, L5;
        String pD = "Nama = ";
        pD += out[2];
        pD += "\nUID = ";
        pD += out[1];
        pD += "\nGedung = ";
        pD += out[3];
        pD += "\nL0 = ";
        pD += out[4];
        pD += " L1 = ";
        pD += out[5];
        pD += " L2 = ";
        pD += out[6];
        pD += " L3 = ";
        pD += out[7];
        pD += " L5 = ";
        pD += out[8];
        //        Serial.print("panjang data terakhir = ");
        //        Serial.println(out[8].length());
        int selesai = millis();
        //        Serial.println(pD);

        tUID = out[1];
        tNAMA = out[2];
        tLANTAI = out[3];
        //        Serial.print("UID = "); Serial.println(out[1]);
        //        Serial.print("NAMA = "); Serial.println(out[2]);
        //        Serial.print("LANTAI = "); Serial.println(out[3]);
        //        Serial.print("Selesai = "); Serial.println(selesai);
        Serial.print("waktu = "); Serial.println(selesai - mulai);
        myFile.close();
        break;
      }
    }

    int selesai = millis();
    Serial.print("Selesai = "); Serial.println(selesai);
    Serial.print("waktu = "); Serial.println(selesai - mulai);
    myFile.close();
  }
  else
  {
    Serial.println("error opening");
  }
  displayName(tNAMA, cek);
}


void parsing(String *output, String in)
{
  int ind[10];
  ind[0] = 0;
  for ( int i = 1; i <= 8; i++)
  {
    if (i <= 1)
    {
      ind[i] = in.indexOf('|');
    }
    else
    {
      ind[i] = in.indexOf('|', ind[i - 1] + 1);
    }
  }
  for ( int i = 1; i <= 8; i++)
  {
    output[i] = in.substring(ind[i] + 1 , ind[i + 1]);
    if ( i == 8)
    {
      output[i] = output[i].substring(0, 1);
    }
    if ( ind[i] == -1)
    {
      return;
    }
  }
}
