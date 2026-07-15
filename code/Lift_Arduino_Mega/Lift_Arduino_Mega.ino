#include<Servo.h>
#define MCU Serial3
int pos1 = 90;
int pos2 = 120;
//SoftwareSerial MCU (A4, A5);


unsigned long PBStart;
bool bstop;
//int PB[5] = {52, 53, 50, 51, 48};
int PB[5] = {48, 51, 50, 53, 52};
//int IN[5] = {23, 25, 27, 29, 31};
int IN[5] = {31, 29, 27, 25, 23};
// int pinSR[5] = {8, 9, 10, 11, 12};
// int pinSR[5] = {12,9,10,11,8}; 
int pinSR[5] = {10,12,9,11,8};   //10,9,8,11,12 |  10,12,8,11,9 2=5 | 10,9,12,11,8 1=2

//int LED[5] = {33, 35, 37, 39, 41};
int LED[5] = {41, 39, 37, 35, 33};
int alreadyTouch[5] = {0, 0, 0, 0, 0};
int stat[5];
Servo s1, s2, s3, s4, s5;

Servo INSR[] = {s1, s2, s3, s4, s5};

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i <= 4 ; i++)
  {
    //    Servo INSR[i];
    pinMode(IN[i], INPUT);
    pinMode(PB[i], OUTPUT);
    initialServo(INSR[i], pinSR[i]);
  }
  MCU.begin(9600);
  Serial.println("DONE");
}

void loop()
{
  readDataMCU();
  readDataSerial();

  //Tombol G & 3 Standby 
    // digitalWrite(48, HIGH); 
    // digitalWrite(53, HIGH); 
    // int z[2] = {0, 3};
    // for (int i = 0; i < 2; i++) {
    //   int iinPB = digitalRead(IN[z[i]]);  
    //   if (iinPB == 1 && alreadyTouch[1] == 0 ) {  
    //     Serial.println("Tombol Stanby & Servo on ");
    //     alreadyTouch[1] = 1;
    //     onServo(INSR[z[i]], pos2);
    //     delay(500);
    //     onServo(INSR[z[i]], pos1);
    //   }else if (iinPB == 0 && alreadyTouch[1] == 1) {
    //     // Hanya reset jika sebelumnya terdeteksi
    //     delay(100); // Debounce delay
    //     alreadyTouch[1] = 0; // Reset jika tidak terdeteksi
    //   }
    // }

  if ( bstop )
  {
    for (int i = 0; i < 5 ; i++)
    {
      int inPB = digitalRead(IN[i]);
      if ( inPB == 1 && alreadyTouch[i] == 0 && stat[i] == 1)
      {
        Serial.print(i);
        Serial.println(" Servo on ");
        alreadyTouch[i] = 1;
        onServo(INSR[i], pos2);
        delay(500);
        onServo(INSR[i], pos1);
        digitalWrite(LED[i], 1);

      }
    }
  }
  if ( millis() - PBStart >= 10000 && bstop)
  {
    Serial.println("STOP");
    for ( int i = 0; i < 5; i++)
    {
      digitalWrite(PB[i], 0);
      onServo(INSR[i], pos1);
      alreadyTouch[i] = 0;
      digitalWrite(LED[i], 0);
    }
    bstop = false;
  }
}
