#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <IridiumSBD.h>

//RX and TX of the GPS to pin 10 and 9.
static const int RXPin = 10, TXPin = 9;
static const uint32_t GPSBaud = 9600;

//The RockBLOCK is connected to serial 3
#define IridiumSerial Serial3
#define DIAGNOSTICS true // Change this to see diagnostics

//Declare the IridiumSBD object and the TinyGPS++ object
IridiumSBD modem(IridiumSerial);
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

int signalQuality = -1;
int err;
int n = 1;

void setup() 
{
  //Start the console serial port
  Serial.begin(115200);
  ss.begin(GPSBaud);

  //Start the serial port connected to the satellite modem
  IridiumSerial.begin(19200);

  // Begin satellite modem operation
  Serial.println("Starting modem...");
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    Serial.print("Begin failed: error ");
    Serial.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      Serial.println("No modem detected: check wiring.");
    return;
  }
  
  //Send the message, vil sende meldingen en gang når jeg vet at jeg har data fra gps.
 
    /*Serial.print("Trying to send the message.  This might take several minutes.\r\n");
    err = modem.sendSBDText("Hello world!");
    if (err != ISBD_SUCCESS)
    {
      Serial.print("sendSBDText failed: error ");
      Serial.println(err);
      if (err == ISBD_SENDRECEIVE_TIMEOUT)
        Serial.println("Try again with a better view of the sky.");
    }
  
    else
    {
      Serial.println("Hey, it worked!");
    }*/
  
}

void loop()
{
   for (n; n>0 && (gps.location.lat(), 8) > 0; n--)
  {
    Serial.println(n);
    Serial.print(gps.location.lat(), 8);

  }
  /*while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();*/
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 8);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 8);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
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
