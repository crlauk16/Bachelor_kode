#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org

#define GPSSerial Serial2
#define GPSBaud 9600
#define DIAGNOSTICS true // Change this to see diagnostics

// Time between transmissions (seconds)
#define BEACON_INTERVAL 3

TinyGPSPlus tinygps;
static const int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);

  // Start the serial ports
  Serial.begin(115200);
  while (!Serial);
  GPSSerial.begin(GPSBaud);
}

void loop()
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

  double outBufferLat = (tinygps.location.lat());
  double outBufferLng = (tinygps.location.lng());

    Serial.print(outBufferLat, 4);
    Serial.print(", ");
    Serial.println(outBufferLng, 4);

    //Serial.print(outLat);
    //Serial.print(", ");
    //Serial.println(outLng);    

  // Sleep
  int elapsedSeconds = (int)((millis() - loopStartTime) / 1000);
  if (elapsedSeconds < BEACON_INTERVAL)
  {
    int delaySeconds = BEACON_INTERVAL - elapsedSeconds;
    delay(1000UL * delaySeconds);
  }
}

void blinkLED()
{
  digitalWrite(ledPin, (millis() / 1000) % 2 == 1 ? HIGH : LOW);
}
