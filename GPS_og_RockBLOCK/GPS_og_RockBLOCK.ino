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

void setup() 
{
  //Start the console serial port
  Serial.begin(115200);
  ss.begin(GPSBaud);

  //Start the serial port connected to the satellite modem
  IridiumSerial.begin(19200);
}

void loop()
{ 
  while (ss.available() > 0)
  gps.encode(ss.read());
    
  if (gps.location.isUpdated() && gps.sentencesWithFix() == 1) //Checks if there is an update to the data, and if the arduino has recived 1 full scentence.
  {
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
    
    Serial.print(gps.location.lat(), 8);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 8);

    Serial.print("Trying to send the message.  This might take several minutes.\r\n");
    err = modem.sendSBDText(gps.location.lat());
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
    }
  }
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
