#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//=====================OLED===============================
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1  // GPIO0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char myBitmap [] PROGMEM = {
  // your company logo  33, 63x33px

};
#define SD_PIN D8

SoftwareSerial ard(D4, D3);

#define RST_PIN         -1
#define SS_PIN          D0
//#define buzz D3
MFRC522 mfrc522(SS_PIN, RST_PIN);
bool errorRFID, getData, Data;
bool updateData = true;
bool rfid = false;
String UID;
String judul = "your lift name";
unsigned long PrevRFID, prevRead;

//======================
String dirFile = "";
void setup()
{
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  //  pinMode(buzz, OUTPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  int x = 10 - judul.length();
  x = x * 12 + 4;
  dis2(x, 0, judul);
  Serial.println();
  Serial.print("Initializing SD card...");
  ard.begin(9600);

  if (!SD.begin(SD_PIN))
  {
    Serial.println("initialization failed!");
    return;
  }
  //  checkData(dirFile, "EB 25 B8 1C");
  Serial.println("initialization done.");


}

void loop()
{

  if (Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    dirFile = in.substring(0, 1);
    dirFile += ".txt";
    //    Serial.print("Dir = ");
    //    Serial.println(dirFile);
    checkData(dirFile,  in);
    dirFile = "";
    rfid = false;
    if ( Data)
    {
      Data = false;
    }
    else
    {

    }
  }
  if ( millis() - PrevRFID > 200)
  {
    mfrc522.PCD_Init();
    readDataRFID();
    PrevRFID = millis();
  }
  if (rfid)
  {
    dirFile = UID.substring(0, 1);
    dirFile += ".txt";
    //    Serial.print("Dir = ");
    //    Serial.println(dirFile);
    checkData(dirFile,  UID);
    dirFile = "";
    rfid = false;
    if ( Data)
    {
      Data = false;
    }
    else
    {

    }
  }
  if ((millis() - prevRead > 3000) && updateData) //stand by
  {
    int x = 10 - judul.length();
    x = x * 12 + 4;
    dis2(x, 0, judul);
    display.fillRect(0, 20, 126, 33, SSD1306_BLACK);
    display.display();
    //    dis3(65, 25, tampilan);
    //    display.drawBitmap(5, 20,  SecImage , 33, 33, 1);
    display.drawBitmap(31, 20,  myBitmap , 63, 33, 1);
    dis(0, 56, "VOKSEL 50th   Lift V1.1");
    display.display();
    updateData = false;
  }
}
