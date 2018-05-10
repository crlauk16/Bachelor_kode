#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org
#include <Wire.h>
#include <I2C_Anything.h>
#include <IridiumSBD.h>

#define IridiumSerial Serial3
#define GPSSerial Serial2
#define GPSBaud 9600
#define DIAGNOSTICS true

IridiumSBD modem(IridiumSerial);
TinyGPSPlus tinygps;

//Variabler som GPS posisjon og kurs lagres i.
int latHel, latDec1, latDec2, latDec3, lngHel, lngDec1, lngDec2, lngDec3, courseRad, course1, course2;
const float Pi = 3.1416;

//Variabler som bestemmer mellomrom mellom RockBLOCK meldinger
unsigned long previousMillis1 = 0;        // will store last time message was send
const long interval1 = 3600000;           // interval at which to send message

//Variabler som brukes til spenningsmåleren
#define NUM_SAMPLES 25
int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage
unsigned long previousMillis2 = 0;        // will store last time message was send
const long interval2 = 1000;           // interval at which to send message

void setup()  
{
  Serial.begin(9600);
  IridiumSerial.begin(19200);
  GPSSerial.begin(GPSBaud);
  Wire.begin(0x48);
  Wire.onRequest(requestEvent); //Når simulink ber om en posisjon kjøres requestEvent
  
  // Setup the Iridium modem
  if (modem.begin() != ISBD_SUCCESS)
  {
    Serial.println("Couldn't begin modem operations.");
    exit(0);
  }
}

void loop() 
{
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();

  //IF-setning som sender posisjon via RockBLOCK
  if (currentMillis1 - previousMillis1 >= interval1) 
  {
    sendMessage();
    // save the last time a message was sendt
    previousMillis1 = currentMillis1;
  }

  //While-loop som oppdaterer posisjon og kurs før den sendes over I2C
  while (GPSSerial.available() > 0)
  {
    if (tinygps.encode(GPSSerial.read()))
    {
      updateInfo();   
    }
  }

  //Legger sammen de 25 siste målingene for å regne et gjennomsnitt
  while (sample_count < NUM_SAMPLES && currentMillis2 - previousMillis2 >= interval2) 
  {
    sum += analogRead(A2);
    sample_count++;
    previousMillis2 = currentMillis2;
  }
  
  voltage = ((float)sum / (float)NUM_SAMPLES * 5.030) / 1024.0;
  double actualVoltage = voltage * 3.127659574;
  Serial.println(actualVoltage);
  sample_count = 0;
  sum = 0;

  //Sjekker om spenningen er under 12.4V, hvis dette er sant skal RockBLOCK sende en melding
  if (actualVoltage < 12.4)
  {
    lowVoltage();
  }
}

//requestEvent sender GPS-posisjon og kurs over I2C
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

//updateInfo oppdaterer infoen som ligger i posisjon og kurs variablene
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

  //Lagrer Latitude i et buffer outBufferLat
  char outBufferLat[12];
  sprintf(outBufferLat, "%s%u%09lu",

  tinygps.location.rawLat().negative ? "-" : "",
  tinygps.location.rawLat().deg,
  tinygps.location.rawLat().billionths);

  //Lagrer Longitude i et buffer outBufferLng
  char outBufferLng[12];
  sprintf(outBufferLng, "%s%u%09lu",

  tinygps.location.rawLng().negative ? "-" : "",
  tinygps.location.rawLng().deg,
  tinygps.location.rawLng().billionths);

  //Gjør om outBufferLat til fire ints
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


  //Gjør om outBufferLng til fire ints
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

  //Gjør om kursen til 1-2 ints
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
}

// sendMessage vil sende posisjon i Longitude og Latitude, samt fart og kurs
void sendMessage()
{
  char outBuffer[49]; //Sørger for at meldingen som sendes ikke overstiger 50 bytes
  sprintf(outBuffer, "%s%u.%09lu,%s%u.%09lu,%lu,%ld", 
    tinygps.location.rawLat().negative ? "-" : "",
    tinygps.location.rawLat().deg,
    tinygps.location.rawLat().billionths,
    tinygps.location.rawLng().negative ? "-" : "",
    tinygps.location.rawLng().deg,
    tinygps.location.rawLng().billionths,
    tinygps.speed.value() / 100,
    tinygps.course.value() / 100);

    Serial.print("Transmitting message '");
    Serial.print(outBuffer);
    Serial.println("'");

//  int err = modem.sendSBDText(outBuffer);
//  if (err != ISBD_SUCCESS)
//  {
//    Serial.print("Transmission failed with error code ");
//    Serial.println(err);
//  }
}

//Melding som sendes når batterispenningen er under 12.4V
void lowVoltage()
{
  Serial.println("Transmitting message 'Warning, low battery'"); 
//  int err = modem.sendSBDText("Warning, low battery");
//  if (err != ISBD_SUCCESS)
//  {
//    Serial.print("Transmission failed with error code ");
//    Serial.println(err);
//  }
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
