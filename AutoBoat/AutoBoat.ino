#include <TinyGPS++.h>
#include <Wire.h>
#include <I2C_Anything.h>
//#include <IridiumSBD.h>

//#define IridiumSerial Serial3
#define GPSSerial Serial2
//#define IridiumBaud 19200
#define GPSBaud 9600
#define DIAGNOSTICS true

//IridiumSBD modem(IridiumSerial);
TinyGPSPlus tinygps;

// Variables that stores GPS position and course
int latHel, latDec1, latDec2, latDec3, lngHel, lngDec1, lngDec2, lngDec3, courseRad, course1, course2;
const float Pi = 3.1416;

// Variables that defines the intervall between RockBLOCK messages
unsigned long previousMillis1 = 0;        // Stores the time when the message last was sendt
const long interval1 = 4500;           // Time between messages

void setup()  
{
  Serial.begin(9600);
  //IridiumSerial.begin(IridiumBaud);
  GPSSerial.begin(GPSBaud);
  Wire.begin(0x48);                       // Defines this Arduino as an I2C slave with address 0x48
  Wire.onRequest(requestEvent);           // When Simulink requests data, requestEvent runs
  
//  // Setup the Iridium modem
//  if (modem.begin() != ISBD_SUCCESS)
//  {
//    Serial.println("Couldn't begin modem operations.");
//    exit(0);
//  }
}

void loop() 
{
  //unsigned long currentMillis1 = millis();
  

  // Sending a message from the RockBLOCK at an one hour interval
//  if (currentMillis1 - previousMillis1 >= interval1) 
//  {
//    sendMessage();
//    previousMillis1 = currentMillis1;
//  }

  // Update the variables which contains position and course
  while (GPSSerial.available() > 0)
  {
    if (tinygps.encode(GPSSerial.read()))
    {
      updateInfo();   
    }
  }


  if (millis() > 5000 && tinygps.charsProcessed() < 10) // uh oh
  {
    Serial.println("ERROR: not getting any GPS data!");
    // dump the stream to Serial
    Serial.println("GPS stream dump:");
    while (true) // infinite loop
      if (GPSSerial.available() > 0) // any data coming in?
        Serial.write(GPSSerial.read());
  }
  // Debugging
  Serial.print("Fix: ");
  Serial.print(tinygps.sentencesWithFix());
  Serial.print(" Failed: ");
  Serial.print(tinygps.failedChecksum());
  Serial.print(" Passed: ");
  Serial.print(tinygps.passedChecksum());
  Serial.print(" Chars: ");
  Serial.println(tinygps.charsProcessed());
}

// requestEvent sends GPS location and course
void requestEvent()
{
  I2C_writeAnything (latHel);
  I2C_writeAnything (latDec1);
  I2C_writeAnything (latDec2);
  I2C_writeAnything (latDec3);
  I2C_writeAnything (lngHel);
  I2C_writeAnything (lngDec1);
  I2C_writeAnything (lngDec2);
  I2C_writeAnything (lngDec3);
  I2C_writeAnything (course1);
  I2C_writeAnything (course2);
}

// updateInfo updates the info which is stored in the position and course variables
void updateInfo()
{
  unsigned long loopStartTime = millis();
  
  // Looking for a GPS signal for a maximum of 7 minutes
  while ((!tinygps.location.isValid() || !tinygps.date.isValid()) && 
    millis() - loopStartTime < 7UL * 60UL * 1000UL)
  {
    if (GPSSerial.available())
      tinygps.encode(GPSSerial.read());
  }

  // Did we get a GPS fix?
  if (!tinygps.location.isValid())
  {
    return;
  }

  // Stores Latitude in a buffer outBufferLat
  char outBufferLat[12];
  sprintf(outBufferLat, "%s%u%09lu",

  tinygps.location.rawLat().negative ? "-" : "",
  tinygps.location.rawLat().deg,
  tinygps.location.rawLat().billionths);

  // Stores Longitude in a buffer outBufferLng
  char outBufferLng[12];
  sprintf(outBufferLng, "%s%u%09lu",

  tinygps.location.rawLng().negative ? "-" : "",
  tinygps.location.rawLng().deg,
  tinygps.location.rawLng().billionths);

  // Recalculates outBufferLat into four ints
  latHel = outBufferLat[0] - 48;
  for (int i = 1; i < 2; i++)
  {
     latHel = latHel * 10 + outBufferLat[i] - 48;
  }
  
  latDec1 = outBufferLat[2] - 48;
  for (int i = 3; i < 4; i++)
  {
     latDec1 = latDec1 * 10 + outBufferLat[i] - 48;
  }
  
  latDec2 = outBufferLat[4] - 48;
  for (int i = 5; i < 6; i++)
  {
     latDec2 = latDec2 * 10 + outBufferLat[i] - 48;
  }
  
  latDec3 = outBufferLat[6] - 48;
  for (int i = 7; i < 8; i++)
  {
     latDec3 = latDec3 * 10 + outBufferLat[i] - 48;
  }


  // Recalculates outBufferLng into four ints
  lngHel = outBufferLng[0] - 48;
  for (int i = 1; i < 1; i++)
  {
     lngHel = lngHel * 10 + outBufferLng[i] - 48;
  }
  
  lngDec1 = outBufferLng[1] - 48;
  for (int i = 2; i < 3; i++)
  {
     lngDec1 = lngDec1 * 10 + outBufferLng[i] - 48;
  }
  
  lngDec2 = outBufferLng[3] - 48;
  for (int i = 4; i < 5; i++)
  {
     lngDec2 = lngDec2 * 10 + outBufferLng[i] - 48;
  }
  
  lngDec3 = outBufferLng[5] - 48;
  for (int i = 6; i < 7; i++)
  {
     lngDec3 = lngDec3 * 10 + outBufferLng[i] - 48;
  }

  // Recalculates the course into one or two ints
  float courseDeg = tinygps.course.deg();
  float courseTempRad = courseDeg * (Pi/180);
  courseTempRad = (courseTempRad * 100) + 0.5;
  courseRad = (int)courseTempRad;

  if (courseRad >= 100)
  {
    course1 =(int)courseRad / 100;
    course2 = courseRad - (course1*100);
  }
  else if (courseRad < 100)
  {
    course1 = 0;
    course2 = courseRad;
  }
  Serial.print(latHel);
  Serial.print(latDec1);
  Serial.print(latDec2);
  Serial.print(latDec3);
  Serial.print(", ");
  Serial.print(lngHel);
  Serial.print(lngDec1);
  Serial.print(lngDec2);
  Serial.println(lngDec3);
}

// sendMessage will send position in longitude and latitude, as well as speed and course
//void sendMessage()
//{
//  char outBuffer[49]; // Keeps the message under 50 bytes
//  sprintf(outBuffer, "%s%u.%09lu,%s%u.%09lu,%lu,%ld", 
//    tinygps.location.rawLat().negative ? "-" : "",
//    tinygps.location.rawLat().deg,
//    tinygps.location.rawLat().billionths,
//    tinygps.location.rawLng().negative ? "-" : "",
//    tinygps.location.rawLng().deg,
//    tinygps.location.rawLng().billionths,
//    tinygps.speed.value() / 100,
//    tinygps.course.value() / 100);
//
//    Serial.print("Transmitting message '");
//    Serial.print(outBuffer);
//    Serial.println("'");
//
//  int err = modem.sendSBDText(outBuffer);
//  if (err != ISBD_SUCCESS)
//  {
//    Serial.print("Transmission failed with error code ");
//    Serial.println(err);
//  }
//}
//
//#if DIAGNOSTICS
//void ISBDConsoleCallback(IridiumSBD *device, char c)
//{
//  Serial.write(c);
//}
//
//void ISBDDiagsCallback(IridiumSBD *device, char c)
//{
//  Serial.write(c);
//}
//#endif
