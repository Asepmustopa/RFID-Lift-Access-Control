void dis(int x, int y, String text)
{
  display.setTextSize(1);
  display.setCursor(x, y);
  display.setTextColor(WHITE);
  String outputText = text.substring(0, 21);
  display.print(outputText);
  display.display();
}
void dis2 (int x, int y, String text)
{
  display.setTextSize(2);
  display.setCursor(x, y);
  display.setTextColor(WHITE, BLACK);
  String outputText = text.substring(0, 10);
  display.print(outputText);
  Serial.print("text = ");
  Serial.println(text);
  display.display();
}
void dis3 (int x, int y, String text)
{
  display.setTextSize(3);
  display.setCursor(x, y);
  display.setTextColor(WHITE, BLACK);
  String outputText = text.substring(0, 10);
  display.print(outputText);
  Serial.print("text = ");
  Serial.println(text);
  display.display();
}
void disBW(int x, int y, String text)
{
  display.setTextSize(2);
  display.setCursor(x, y);
  display.setTextColor(BLACK, WHITE);
  String outputText = text.substring(0, 10);
  display.print(outputText);
  display.display();
}

void displayName(String nama, bool statCheck)
{
  if ( statCheck == true )
  {
    for ( int i = 1 ; i <= 2; i++)
    {
      Serial.println("Buzzz.....");
      //      digitalWrite(buzz, 1);
      //      delay(50);
      //      digitalWrite(buzz, 0);
      //      delay(50);
    }
    display.fillRect(0, 20, 126, 33, SSD1306_BLACK);
    display.display();

    //    dis2(0, 0, nama);
    int pos = 4;
    int nLength = nama.length();
    if ( nLength < 10)
    {
      pos = 10 - nLength;
      pos = pos * 6;
    }
    delay(10);
    dis2(pos, 30, nama.substring(0, 10));
    prevRead = millis();
    updateData = true;
  }
  else if ( statCheck == false)
  {
    display.fillRect(0, 20, 126, 33, SSD1306_BLACK);
    String noac = " No Access";
    dis2(0, 30, noac.substring(0, 10) );
    //    digitalWrite(buzz, 1);
    //    delay(500);
    //    digitalWrite(buzz, 0);
    //    delay(500);
    prevRead = millis();
    updateData = true;
  }
}
