#include <TinyGPS++.h> 
#include <Wire.h>

#define GPSSerial Serial2
#define GPSBaud 9600
#define DIAGNOSTICS false // Change this to see diagnostics

#define BEACON_INTERVAL 30

TinyGPSPlus tinygps;
static const int ledPin = 13;

void setup() {
  Wire.begin(7); // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);
  
  pinMode(ledPin, OUTPUT);

  // Start the serial ports
  while (!Serial);
  GPSSerial.begin(GPSBaud);
}


void loop() {

  unsigned long loopStartTime = millis();

  // Begin listening to the GPS

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
}

void requestEvent() 
{
  // Step 3: Start talking to the RockBLOCK and power it up
  char outBuffer[49]; // Always try to keep message short
  sprintf(outBuffer, "%s%u.%09lu,%s%u.%09lu", 
  tinygps.location.rawLat().negative ? "-" : "",
  tinygps.location.rawLat().deg,
  tinygps.location.rawLat().billionths,
  tinygps.location.rawLng().negative ? "-" : "",
  tinygps.location.rawLng().deg,
  tinygps.location.rawLng().billionths);  
  Wire.write(outBuffer);
}

void blinkLED()
{
  digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
}

bool ISBDCallback()
{
  blinkLED();
  return true;
}

#if DIAGNOSTICS
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}
#endif
