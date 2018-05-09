#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org
#include <Wire.h>
#include <I2C_Anything.h>

#define GPSSerial Serial2
#define GPSBaud 9600

int latHel, latDec1, latDec2, latDec3, lngHel, lngDec1, lngDec2, lngDec3;

TinyGPSPlus tinygps;

void setup() 
{                
  GPSSerial.begin(GPSBaud);
  Wire.begin(0x48);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);                
}

void loop() 
{
  while (GPSSerial.available() > 0)
    if (tinygps.encode(GPSSerial.read()))
      updateInfo();
}

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
}

void updateInfo()
{
  unsigned long loopStartTime = millis();
  
  // Look for GPS signal for up to 7 minutes
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

  char outBufferLat[12];
  sprintf(outBufferLat, "%s%u%09lu",

  tinygps.location.rawLat().negative ? "-" : "",
  tinygps.location.rawLat().deg,
  tinygps.location.rawLat().billionths);

  char outBufferLng[12];
  sprintf(outBufferLng, "%s%u%09lu",

  tinygps.location.rawLng().negative ? "-" : "",
  tinygps.location.rawLng().deg,
  tinygps.location.rawLng().billionths);

  //Transfer outBufferLat in to int
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


  //Transfer outBufferLng in to int
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
  
  Serial.print(latHel);
  Serial.print(latDec1);
  Serial.print(latDec2);
  Serial.print(latDec3);
  Serial.print(", ");
  Serial.print(lngHel);
  Serial.print(lngDec1);
  Serial.print(lngDec2);
  Serial.print(lngDec3);
  Serial.print(", Retning: ");
  Serial.println(tinygps.course.deg());
}

