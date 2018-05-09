#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org
#include <Wire.h>

#define GPSSerial Serial2
#define GPSBaud 9600
#define BEACON_INTERVAL 3

TinyGPSPlus tinygps;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  while (!Serial);
  GPSSerial.begin(GPSBaud);
  
  Wire.begin(8);                // join i2c bus with address #8 
  Wire.onRequest(requestEvent); // register event
}

void loop() {
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
  int16_t latHel = outBufferLat[0] - 48;
  for (int i = 1; i < 3; i++)
  {
     latHel = latHel * 10 + outBufferLat[i] - 48;
  }
  int16_t latDec = outBufferLat[3] - 48;
  for (int i = 4; i < 7; i++)
  {
     latDec = latDec * 10 + outBufferLat[i] - 48;
  }

  //Transfer outBufferLng in to int
  int16_t lngHel = outBufferLng[0] - 48;
  for (int i = 1; i < 3; i++)
  {
     lngHel = lngHel * 10 + outBufferLng[i] - 48;
  }
  int16_t lngDec = outBufferLng[3] - 48;
  for (int i = 4; i < 7; i++)
  {
     lngDec = lngDec * 10 + outBufferLng[i] - 48;
  }
  Serial.print(latHel);
  Serial.println(latDec);
  Serial.print(lngHel);
  Serial.println(lngDec); 

  // Sleep
  int elapsedSeconds = (int)((millis() - loopStartTime) / 1000);
  if (elapsedSeconds < BEACON_INTERVAL)
  {
    int delaySeconds = BEACON_INTERVAL - elapsedSeconds;
    Serial.print(F("Waiting for "));
    Serial.println(delaySeconds);
    Serial.println(F(" seconds"));
    delay(1000UL * delaySeconds);
  }

  // Wake
  Serial.println("Wake up!");
}

void requestEvent() 
{
  Wire.write("hello ");
}
