#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org

#define ArduinoSerial Serial1
#define GPSSerial Serial2
#define GPSBaud 9600

TinyGPSPlus tinygps;

#define BEACON_INTERVAL 3

int byteRead;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  ArduinoSerial.begin(9600);
  while (!Serial);
  GPSSerial.begin(GPSBaud);
}

void loop() {
  
  unsigned long loopStartTime = millis();

  // Begin listening to the GPS
  Serial.println("Beginning to listen for GPS traffic...");

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
    Serial.println(F("Could not get GPS fix."));
    Serial.print(F("GPS characters seen = "));
    Serial.println(tinygps.charsProcessed());
    Serial.print(F("Checksum errors = "));
    Serial.println(tinygps.failedChecksum());
    return;
  }

  Serial.println(F("A GPS fix was found!"));

  // Step 3: Start talking to the RockBLOCK and power it up
  Serial.println("Beginning to talk to the RockBLOCK...");

  char outBufferLat[24];
  sprintf(outBufferLat, "%s%u.%09lu",

  tinygps.location.rawLat().negative ? "-" : "",
  tinygps.location.rawLat().deg,
  tinygps.location.rawLat().billionths);

  char outBufferLng[24];
  sprintf(outBufferLng, "%s%u.%09lu",

  tinygps.location.rawLng().negative ? "-" : "",
  tinygps.location.rawLng().deg,
  tinygps.location.rawLng().billionths);
  
  Serial.print(outBufferLat);
  Serial.print(", ");
  Serial.println(outBufferLng);

  ArduinoSerial.print(outBufferLat);
  //ArduinoSerial.print(", ");
  //ArduinoSerial.println(outBufferLat);
  

  int elapsedSeconds = (int)((millis() - loopStartTime) / 1000);
  if (elapsedSeconds < BEACON_INTERVAL)
  {
    int delaySeconds = BEACON_INTERVAL - elapsedSeconds;
    Serial.print(F("Waiting for "));
    Serial.print(delaySeconds);
    Serial.println(F(" seconds"));
    delay(1000UL * delaySeconds);
  }

  // Wake
  Serial.println("Wake up!");
}
