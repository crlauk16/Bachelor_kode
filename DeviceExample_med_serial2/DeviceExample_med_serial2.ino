#include <TinyGPS++.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

#define GPSSerial Serial2
#define GPSBaud 9600

// The TinyGPS++ object
TinyGPSPlus tinygps;

void setup()
{
  Serial.begin(115200);
  GPSSerial.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (GPSSerial.available() > 0)
    if (tinygps.encode(GPSSerial.read()))
      displayInfo();

  if (millis() > 5000 && tinygps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (tinygps.location.isValid())
  {
    Serial.print(tinygps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(tinygps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (tinygps.date.isValid())
  {
    Serial.print(tinygps.date.month());
    Serial.print(F("/"));
    Serial.print(tinygps.date.day());
    Serial.print(F("/"));
    Serial.print(tinygps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (tinygps.time.isValid())
  {
    if (tinygps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(tinygps.time.hour());
    Serial.print(F(":"));
    if (tinygps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(tinygps.time.minute());
    Serial.print(F(":"));
    if (tinygps.time.second() < 10) Serial.print(F("0"));
    Serial.print(tinygps.time.second());
    Serial.print(F("."));
    if (tinygps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(tinygps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
