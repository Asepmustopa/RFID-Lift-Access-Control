void readDataMCU()
{
  while ( MCU.available() > 0)
  {
    String in = MCU.readStringUntil('\r');
    Serial.println("------------");
    Serial.println(in);
    String out[10];
    parsing(out, in);
    for ( int i = 0 ; i < 5; i++)
    {
      
      alreadyTouch[i] = 0;
      digitalWrite(PB[i], 0);
      digitalWrite(LED[i], 0);
      stat[i] = 0;
    }
    for (int i = 1; i <= 5; i++)
    {
      Serial.print(i);
      Serial.print(".");
      Serial.println(out[i]);
      if (out[i].toInt() == 1)
      {
        stat[i-1] = 1;
        digitalWrite(PB[i - 1], stat[i-1]);
      }
      Serial.println("Start");
      PBStart = millis();
      //      Serial.println(PBStart);
      bstop = true;

    }
    delay(100);
    Serial.println("END");
  }
}
void readDataSerial()
{
  while ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    Serial.println("------------");
    Serial.println(in); 
    String out[10];
    parsing(out, in);
    for (int i = 1; i <= 5; i++)
    {
      Serial.print(i);
      Serial.print(".");
      Serial.println(out[i]);
      if (out[i].toInt() == 1)
      {
        digitalWrite(PB[i - 1], 1);
      }
      Serial.println("Start");
      PBStart = millis();
      //      Serial.println(PBStart);
      bstop = true;
    }
    delay(100);
    Serial.println("END");
  }
}
void parsing(String *output, String in)
{
  int ind[10];
  ind[0] = 0;
  for ( int i = 1; i <= 6; i++)
  {
    if (i <= 1)
    {
      ind[i] = in.indexOf('|');
    }
    else
    {
      ind[i] = in.indexOf('|', ind[i - 1] + 1);
    }
    //    Serial.print("ind ");
    //    Serial.println(ind[i]);
  }
  for ( int i = 1; i <= 5; i++)
  {
    output[i] = in.substring(ind[i] + 1 , ind[i + 1]);
    //    Serial.print(i);
    //    Serial.print(". ");
    //    Serial.println(output[i]);
    if ( ind[i] == -1)
    {
      return;
    }
  }
}
